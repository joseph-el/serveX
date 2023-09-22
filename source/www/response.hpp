# ifndef _RESPONSES_H_
# define _RESPONSES_H_

# include "socket.hpp"

class response 
{

    // just for test 
    public :

        void send(socket_t fd) {

            const char * response_ = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 12\r\n"
                        "\r\n"
                        "Hello, World!";


            ::send(fd, response_, strlen(response_), 0);
        }
};

# endif
