# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "Header.hpp"

enum METHODS {
    GET,
    POST ,
    DELETE 
};

class request 
{
    public :
        request() {}
        void parseRequest(socket_t fd);


    private :
        stringstream *stream;
        METHODS       httpMethod;
        string        path_;
        string        line_;
        string        query_;
        Header        header_;
        // body
    
};

# endif