# include "serveX.hpp"
# include "sX_optioneer.hpp"
# include "../www/sX_socket.hpp"
# include <deque>
#include <vector>
#include <sys/poll.h>

typedef int32_t IOsocket;
using namespace std;

# define SOCKET_CREATED 0x0
# define SERVER_BACKLOG 1e1

class sX_socket {

    sX_socket() 
    {
        int socketfd  = socket( AF_INET, SOCK_STREAM , false);
        if (socketfd & ~SOCKET_CREATED) {
            cerr << serveX_NAME << ": " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }
        fdsocket |= socketfd;
    }

    IOsocket getSocketID( void ) const {
        return fdsocket;
    }

    private :
        IOsocket fdsocket;
};


void initGateway( vector<Sx_server_data> &address, set<int> &sockets)
{
    vector<Sx_server_data>::iterator it = address.begin();
    for (; it != address.end() ; it ++)
    {

    }



}



void init_serveX( int argc, char *const *argv)
{
    options opt(argc, argv);

    char stream[ (1 << 0xA) ];

    // signal(SIGPIPE, SIG_IGN);
    if (!opt.successful() or !sX_config.successful()) // or sX_config .syntax
        return ;

    // vector<Sx_server_data> servers = sX_config.getServers();
    // initGateway();


    while (true) { cout << "serve running\n"; }
}

int main (int argc, char *const argv[])
{

    init_serveX(argc, argv);

    std::vector<Sx_server_data> address = sX_config.getServers();
    std::set<int> sockets;
    initGateway(address, sockets);
 
 
    // puts(""); puts(""); puts(""); puts("");
    // cout << "all is good\n";
    return EXIT_SUCCESS;
}