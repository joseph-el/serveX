# if !defined(SX_SOCKET_HPP)
# define SX_SOCKET_HPP

#include <cstdlib>     
#include <cerrno>    
#include <iostream>
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <netinet/in.h>

typedef int IOsocket;
using namespace std;

class sX_socket
{
    public :
        sX_socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = false);
        IOsocket getSocketID( void ) const;
    

        ~sX_socket( void );
    private :
        IOsocket fdsocket;

};

# endif