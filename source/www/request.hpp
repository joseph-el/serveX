# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "requestBody.hpp"

enum METHODS {
    GET = 1 << 1,
    POST = 1 << 2,
    DELETE = 1 << 3,
    UNKNOWN_MT = 1 << 4
};

class request {
    // private :
    public :

        short   _status;
        short   _httpStatus;

        METHODS _method;
        string  _path;
        string  _line;
        string  _query;
        Header  _header;
        requestBody    _body;

        request() : _query(""), _path(""), _line("")
        {
           _status = REQUEST_SETUP;
           _httpStatus = 0;
           _method = UNKNOWN_MT;
        }
        bool is_valid() { return  _status & REQUEST_PARSE_DONE; }
        string normalization(const string &, const char sep = (char)47);
        void UpdateStatus(short _st);
        void interpretRequest( stringstream & );
        void parseReaquestLine(string );
        void parseHeader(string ); 
};

# endif