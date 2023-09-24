# ifndef _RESPONSES_H_
# define _RESPONSES_H_

# include "socket.hpp"

class response 
{

    // just for test 
    public :

        void send(socket_t fd) {

            const char* response_ =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html;"
            "Content-Length: 127\r\n"
            "\r\n" // The empty line that separates headers from the body
            "<!DOCTYPE html>\r\n"
            "<html>\r\n"
            "<head>\r\n"
            "    <title>Example Page</title>\r\n"
            "</head>\r\n"
            "<body>\r\n"
            "    <h1>Hello, World!</h1>\r\n"
            "</body>\r\n"
            "</html>";
            std::cout << "fd  :  " << fd << std::endl;
            size_t byte = ::send(fd, response_, strlen(response_), 0);
            if (byte <= 0) {
                std::cout << "error in send" << std::endl;
            }
            close(fd);
            // std::cout << "after send " << std::endl;
        }
};

# endif
