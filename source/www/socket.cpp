# include "server-core.hpp"

void Socket::listen(int _backlog)  {
    if (::listen(_socketfd, _backlog) != 0) {
        cerr << NAME << ": listen " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
}

void *getAddr(struct sockaddr *sa)  {
	return &(((struct sockaddr_in *)sa)->sin_addr);
}

struct addrinfo* Socket::getSocketAddr( void )
{
    struct addrinfo *addr;
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    // ai_family = AF_UNSPEC : IPv4 or IPv6
    hint.ai_family = AF_UNSPEC;
    // ai_socktype = SOCK_STREAM : TCP
    hint.ai_socktype = SOCK_STREAM;
    // ai_flags = AI_PASSIVE : Bind
    hint.ai_flags = AI_PASSIVE;

    if (getaddrinfo(Address.getHost().c_str(), to_string(Address.getListenPort()).c_str(), &hint, &addr) < 0) {
            cerr << NAME ": Invalid address" << endl;
            exit(EXIT_FAILURE);
    }
    return addr;
}

socklen_t Socket::getSocketLen() 
{
    return sizeof(sockaddr_in);
}

void Socket::set_server_address(server_data &_address) {
    Address = _address;
}

void Socket::bind()  {
    struct addrinfo *addr = getSocketAddr();
    int error = 0, tmp_socket;
    for (struct addrinfo *tmp = addr; tmp; tmp = tmp->ai_next)
    {
        tmp_socket = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
        int optval = 1;
	    setsockopt(tmp_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        error = ::bind(tmp_socket, tmp->ai_addr, tmp->ai_addrlen);
        if (error != -1)
            break ;
        close(tmp_socket);
    }
    freeaddrinfo(addr);
    if (error == -1)
            return perror("socket fail: "), close(tmp_socket), exit(1);
    _socketfd = tmp_socket;
}

socket_t Socket::getsocket_t( void ) const 
    {  return _socketfd; }


int is_inSocket(socket_t &fdsocket, const vector<Socket> &_socket) {
    vector<Socket>::const_iterator it = _socket.begin();

    for (; it != _socket.end(); it++)
        if (it->getsocket_t() == fdsocket)
            return distance(_socket.begin(), it);

    return -1;
}

socket_t Socket::accept(void) {
    socket_t newconnection;

    newconnection = ::accept(_socketfd, NULL, NULL);
    if (newconnection < 0) {
        cerr << NAME << ": " << strerror(errno) << endl;
        return -1;
    }
    clients.push_back(newconnection);
    return newconnection;
}


const server_data& Socket::get_server_address( void ) const {
    return Address;
}


vector<Socket> init_Socket(vector<server_data> servers, fd_set &rd_socket, t_pair &fd_range) 
{
    vector<server_data>::iterator it = servers.begin();
    socket_t min_fd, max_fd;
    vector<Socket> _socket;

    FD_ZERO(&rd_socket);

    for (; it != servers.end(); it++) {
        Socket new_socket;
        
        // setting server address which contain all information about the server
        new_socket.set_server_address(*it);

        new_socket.bind();
        new_socket.listen();
        _socket.push_back(new_socket);

        FD_SET(new_socket.getsocket_t(), &rd_socket);
        max_fd = _socket.front() > *--_socket.end();
        min_fd = _socket.front() < *--_socket.end();
        // cout << "min " <<  min_fd << " max : " << max_fd << endl;
    }
    return fd_range = make_pair(min_fd, max_fd), _socket;
}