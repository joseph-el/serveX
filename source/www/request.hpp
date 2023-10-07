# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "../core/config.hpp"
# include "mimeTypes.hpp"
# include "../utility/templates_helper.hpp"
# include "../utility/StringManipulation.hpp"
# include "../core/config.hpp"
# include "socket.hpp"
# include "Header.hpp"
# include <deque>
# include <sstream>
# include "HttpStatusMapping.hpp"
# include <string>
# include "../core/config.hpp"
# include  <algorithm>
# include "mimeTypes.hpp"
# include "../utility/templates_helper.hpp"

extern "C" {
    # include <unistd.h>
	# include <string.h>
	# include <ctype.h>
    # include <fcntl.h>
    # include <stdlib.h>
    # include <sys/time.h>
}

#define CR "\r"
#define LF "\n"
#define CRLF "\r\n"
#define HTTP_VERSION "HTTP/1.1"

# define METHODS_LENGHT 4

# define REQUEST_PARSE_DONE (1 << 1)
# define BODY_DONE (1 << 2)
# define REQUEST_SETUP (1 << 3)
# define REQUEST_LINE (1 << 4)
# define REQUEST_HEADER (1 << 5)
# define REQUEST_BODY (1 << 6)
# define UNACCEPTABLE_REQUEST (1 << 7)
# define HTTP_STATUS (1 << 8)
# define REQUEST_STATUS (1 << 9)
# define RUNTIME_ERROR (1 << 10)

# define MULTIPART_STRING "multipart/form-data"
# define BOUNDARY_STRING "boundary"
# define BOUNDARY_BEGIN "--"

# define MULTIPART_BODY   (1 << 1)
# define CHUNKED_BODY     (1 << 2)
# define LENGTH_BODY      (1 << 3)
# define BINARY_BODY      (1 << 4)
# define BODY_ERROR       (1 << 8)
# define BODY_STATUS      (1 << 6)
# define MULTIPART_STATUS (1 << 7)
# define BODY_SUCCESSFUL  (1 << 5)

// multiple parte macros

# define MULTIPART_BEGIN (1 << 9)
# define MULTIPART_DONE (1 << 8)
# define MLT_CRLF (1 << 10)
# define MLT_BOUNDARY (1 << 11)
# define MLT_HEADERS (1 << 12)
# define MLT_CONTENT (1 << 13)
# define MLT_HEADER_DONE (1 << 14)

# define MLT_BINARY (1 << 15)
# define MLT_VALUE (1 << 16)
// # define MLT_CRLF (1 << 17)

# define BN_OK 1
# define BN_NO 2
# define BN_END 3
# define BN_WAIT 4

# define CRLF_OK 1
# define CRLF_NO 2
# define CRLF_WAIT 3

enum METHODS {
    GET = 1 << 1,
    POST = 1 << 2,
    DELETE = 1 << 3,
    UNKNOWN_MT = 1 << 4
};

using namespace std;

class ShapeFile {

    public :
        FILE    *file;
        Header  _header;
        string  _openedFILE;
        string  _filename;
        string  name;

		void open(string &);
        int write(stringstream &);

};

class Body {
    // private :
    public : // just for test
        FILE                *bodycontent;
        string               bodyPath;
        size_t               contentLength;
	    size_t               chunkedLength;
        size_t               content;

        mutable short       _status;

        mutable short         _multipartStatus;
        pair<bool, string>     boundary;
        map<short, ShapeFile>  _multipart;
        short                  _idx;
        stringstream            ss;


Body &operator=(const Body &rhs) {
	(void)rhs;
	return *this;
}

Body(const Body &copy) {
    (void)copy;
	// *this = copy;
}

~Body() {
        if (bodycontent)
            fclose(bodycontent);
}

        bool    UpdateStatus(short _st) const ;
        void    FindBodyStatus( Header & );
        void    multipartBody(stringstream &);
        // void    chunkedBody(stringstream &);
        void    lengthedBody(stringstream &);
        // void    binaryBody(stringstream &);

        void    absorb_stream(stringstream &);
        // int     absorbBoundary(string &);
        int     absorbBoundary(stringstream &, stringstream &ss);

        void    absorbHeaders(string &_buff, short &gl_mode);
        int    absorbContent(stringstream &, stringstream &);

        void open() {
    
            // bodyPath = "/tmp/.server__" + to_string(time()) + "__.io";
            // bodycontent = fopen(bodyPath.c_str(), "w+");
            // if (!bodycontent)
            //     UpdateStatus (RUNTIME_ERROR | BODY_STATUS);
        }
        
        unsigned long time() {
    		struct timeval _time;
    		gettimeofday(&_time, NULL);
    		return (unsigned long)_time.tv_usec * 10000;
        }

        Body() {
			_idx = 0;
            contentLength = 0;
            chunkedLength = 0;
            content = 0;
            _status = 0;
            _multipartStatus = MULTIPART_BEGIN | MLT_BOUNDARY;
        }
        // Body (Header &_header_)
		// {
		// 	_idx = 0;
        //     contentLength = 0;
        //     chunkedLength = 0;
        //     content = 0;
        //     _status = 0;
        //     _multipartStatus = 0;
        //     _idx = 0;
        //     FindBodyStatus(_header_);
        // }


}; 

class request {
    // private :
    public : // just for test :

        short   _status;
        short   _httpStatus;

        METHODS _method;
        string  _path;
        string  _line;
        string  _query;
        Header  _header;
        Body    _body;
        bool    valid;

        request() : _query(""), _path(""), _line("")
        {
            valid = false;
           _status = REQUEST_SETUP;
           _httpStatus = 0;
           _method = UNKNOWN_MT;
        }
        bool is_valid() {return valid;}
        string normalization(const string &, const char sep = (char)47);
        void UpdateStatus(short _st);
        void interpretRequest( stringstream & );
        void parseReaquestLine(string );
        void parseHeader(string ); 
};



# endif