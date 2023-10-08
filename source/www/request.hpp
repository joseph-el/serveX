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
        ~request() {}
        request(const request &other) {
            *this = other;
        }
        request &operator=(const request &other) {
            if (this != &other) {
                this->_status = other._status;
                this->_httpStatus = other._httpStatus;
                this->_method = other._method;
                this->_path = other._path;
                this->_line = other._line;
                this->_query = other._query;
                this->_header = other._header;
                this->_body = other._body;
            }
            return *this;
        }
        bool is_valid() { return  _status & REQUEST_PARSE_DONE; }
        string normalization(const string &, const char sep = (char)47);
        void UpdateStatus(short _st);
        void interpretRequest( stringstream & );
        void parseReaquestLine(string );
        void parseHeader(string ); 
};

# endif