# include "socket.hpp"

Socket::Socket(int domain , int type, int protocol)
{
    socket_t socketfd = socket( domain, type , protocol);
    if (socketfd == -1) {
        cerr << NAME << ": socket " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    _socketfd = socketfd;
    int optval = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void Socket::listen(int _backlog) 
{
    if (::listen(_socketfd, _backlog) != 0)
    {
        cerr << NAME << ": bind " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
}

void *getAddr(struct sockaddr *sa) 
{
	return &(((struct sockaddr_in *)sa)->sin_addr);
}

sockaddr Socket::getSocketAddr( void )
{
    sockaddr saddr;
	bzero(&saddr, sizeof(sockaddr));
	saddr.sa_family = AF_INET;
	saddr.sa_len = getSocketLen();

    ((sockaddr_in *)&saddr)->sin_port = htons(Address->getListenPort());

	if (inet_pton(saddr.sa_family, Address->getHost().c_str(), getAddr(&saddr)) <= 0)
        goto invalid_Address;

    return saddr;

    invalid_Address:
        cerr << NAME << ": " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
}

socklen_t Socket::getSocketLen() 
{
    return sizeof(sockaddr_in);
}

void Socket::set_server_address(server_data &_address) {
    Address = &_address;
}

void Socket::bind() 
{
    sockaddr saddr = getSocketAddr();
    if (::bind(_socketfd, &saddr, getSocketLen()) != 0)
    {
        cerr << NAME << ": bind " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
}

socket_t Socket::getsocket_t( void ) const 
    {  return _socketfd; }


int is_inSocket(socket_t &fdsocket, const vector<Socket> &_socket)
{
    vector<Socket>::const_iterator it = _socket.begin();

    for (; it != _socket.end(); it++)
        if (it->getsocket_t() == fdsocket)
            return distance(_socket.begin(), it);
    
    return -1;
}

socket_t Socket::accept(void)
{
    socket_t newconnection;

    newconnection = ::accept(_socketfd, NULL, NULL);
    if (newconnection < 0) {
        cerr << NAME << ": " << strerror(errno) << endl;
        return -1;
    }

    return newconnection;
}

vector<Socket> init_Socket(vector<server_data> servers, fd_set &rd_socket, pair<socket_t, socket_t> &fd_range)
{
    vector<server_data>::iterator it = servers.begin();
    socket_t min_fd, max_fd;
    vector<Socket> _socket;

    FD_ZERO(&rd_socket);

    for (; it != servers.end(); it++)
    {
        Socket new_socket;
        
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