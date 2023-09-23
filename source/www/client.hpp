# ifndef _CLIENT_H_
# define _CLIENT_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "request.hpp"
# include "response.hpp"

class response ; // waitng for creat
class request  ; // waiting for creat

class s_client
{
    private :
        response res_;
        request  req_;
    
        pid_t     _pid; // for cgi
        int       _fds[2]; // for cgi
        socket_t _newconnection; // new client


    public :
        s_client();

        s_client(socket_t newconnection);
        
        void DealwithRequest(  void );
        void DealwithResponce( void );
};

class Clients : public map<socket_t , s_client>
{
    public :
        Clients() {}

    void Expireconnection() {
        // exit(EXIT_FAILURE); // hhhhhhh debug about 20 min fuck
        // waiting to remove iterator and close the fd
    }
};

extern Clients clients;

# endif