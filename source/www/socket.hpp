# ifndef _SOCKET_H_
# define _SOCKET_H_

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <algorithm>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <map>
#include <ratio>
#include <set>
#include <string>
# include <cstdlib>     
# include <cerrno>    
# include <iostream>
# include <sys/types.h> 
# include <arpa/inet.h> 
# include <sys/socket.h>
# include <netinet/in.h>

# include "../core/config.hpp"

# define SOCKET_CREATED 0x0
# define SERVER_BACKLOG 1e1

using namespace std;

struct sockaddr;
struct addrinfo;

typedef int32_t socket_t;

class Socket {

    public :

        Socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);

        // used function 
        void     listen(int _backlog = SERVER_BACKLOG);
        void     bind();
        socket_t accept();
        
        // set 
        void set_server_address(server_data &);
        
        // getters
        sockaddr  getSocketAddr(void ); 
        socklen_t getSocketLen( void );
        socket_t  getsocket_t( void ) const;

        // opr over
        socket_t operator < (const Socket& other) const { // min fd
            return _socketfd < other._socketfd ? _socketfd : other._socketfd;
        }

        socket_t operator > (const Socket& other) const { // max fd
            return _socketfd > other._socketfd ? _socketfd : other._socketfd;
        }

    private :
        socket_t    _socketfd;
        server_data *Address;
};

vector<Socket> init_Socket(vector<server_data> , fd_set &);
int            is_inSocket(socket_t &, const vector<Socket> &);
vector<Socket> init_Socket(vector<server_data> , fd_set &, pair<socket_t, socket_t> &);

# endif