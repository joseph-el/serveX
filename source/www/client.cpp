# include "client.hpp"

s_client::s_client() {}

s_client::s_client(socket_t newconnection)
{
    _fds[0] = _fds[1] = -2;
    _newconnection = newconnection;
}

void s_client::DealwithRequest( void ) 
{
    // this is just for test the new version 

    req_.parseRequest(_newconnection);
    // handel all by taha naceur
}


void s_client::DealwithResponce( void ) 
{

    res_.send(_newconnection);
    // handel all by joseph & abdou
}
