# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "Header.hpp"
#include <cstddef>

enum METHODS {
    GET,
    POST ,
    DELETE 
};

class request 
{
    public :
        request() {
            std::cout << "request constructor" << std::endl;
            counte = 0;
        };
        ~request() {
            std::cout << "request destructor" << std::endl;
         };
        void parseRequest(socket_t fd);
        bool isReady() { return ready; };


    private :
        stringstream  *stream;
        std::string   request_string;
        METHODS       httpMethod;
        string        path_;
        string        line_;
        string        query_;
        Header        header_;
        bool          ready;
        int           counte;
        // body
    
};

# endif