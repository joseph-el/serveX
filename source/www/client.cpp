# include "client.hpp"
#include "request.hpp"
#include "socket.hpp"

// s_client::s_client() {}

s_client::s_client(socket_t newconnection)
{
    _fds[0] = _fds[1] = -2;
    _newconnection = newconnection;
    std::cout << "Client constructor" << std::endl;
}

void s_client::set_server_idx(int idx, int server_socket) {
    _server_idx = idx;
    _server_socket = server_socket;
}

socket_t s_client::get_client_socket() {
    return _newconnection;
}

void s_client::DealwithRequest( void ) 
{
    req_.parseRequest(_newconnection);
}


void s_client::DealwithResponce( void ) 
{

    res_.send(_newconnection);
    // handel all by joseph & abdou
}
