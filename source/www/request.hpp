# ifndef __REQUEST_H__
# define __REQUEST_H__

# include "server-core.hpp"

# define REQUEST_LINE          (1 << 1)
# define REQUEST_BODY          (1 << 2)
# define REQUEST_SETUP         (1 << 3)
# define REQUEST_HEADER        (1 << 4)
# define REQUEST_PARSE_DONE    (1 << 5)

typedef unsigned long long t_size;

class requestBody;
class request {

    private :
        mutable short   _stat;
        mutable short   _httpCodeSatus;
        mutable bool    _isChunked;
        mutable short   _type;

    public   :

        METHODS        _method;
        string         _path;
        string         _line;
        string         _query;
        Header         _header;
        requestBody    _body;

        void   reset();
        short  _get_request_stat_(void) const;
        short  _get_http_code_status_(void) const;
        short  _unacceptable_request_(void) const;

        bool  _request_is_done_(void) const;
        bool  _requestChunked_(void) const;
        bool  likeness(short) const;
        bool  likeness_(short) const;
        bool  TooLarge(const t_size &);

        size_t Uploaded(void) const ;

        string normalization(const string &, const char sep = (char)47);
        void UpdateStatus(short);
        void interpretRequest( stringstream & );
        void parseReaquestLine(string );
        void parseHeader(string ); 

        request() : _path("") , _line(""), _query("") {
           _stat = REQUEST_SETUP;
           _httpCodeSatus = 0;
           _method = UNKNOWN_MT;
           _isChunked = false;
        }

        request(const request &other) {
            *this = other;
        }

        request &operator=(const request &other) {
            if (this != &other) {
                _stat = other._stat;
                _httpCodeSatus = other._httpCodeSatus;
                _method = other._method;
                _path = other._path;
                _isChunked = other._isChunked;
                _type = other._type;
                _line = other._line;
                _query = other._query;
                _header = other._header;
                _body = other._body;
            }
            return *this;
        }

};

extern const char *methods[];

# endif