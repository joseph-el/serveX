# ifndef _BODY_H_
# define _BODY_H_

# include "../core/config.hpp"
# include "mimeTypes.hpp"
# include "../utility/templates_helper.hpp"
# include "../utility/StringManipulation.hpp"
# include "../utility/utils.hpp"

# include "../core/config.hpp"
# include "socket.hpp"
# include "Header.hpp"
# include <deque>
# include <sstream>
# include "HttpStatusMapping.hpp"
# include <string>
# include "../core/config.hpp"
# include  <algorithm>
#include <sys/_types/_size_t.h>
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

# define MULTIPART_STRING "multipart/form-data"
# define BOUNDARY_STRING "boundary"
# define BOUNDARY_BEGIN  "--"
# define CR   "\r"
# define LF   "\n"
# define CRLF "\r\n"
# define HTTP_VERSION "HTTP/1.1"

# define METHODS_LENGHT 4

# define REQUEST_PARSE_DONE   (1 << 1)
# define BODY_DONE            (1 << 2)
# define REQUEST_SETUP        (1 << 3)
# define REQUEST_LINE         (1 << 4)
# define REQUEST_HEADER       (1 << 5)
# define REQUEST_BODY         (1 << 6)
# define UNACCEPTABLE_REQUEST (1 << 7)
# define HTTP_STATUS          (1 << 8)
# define REQUEST_STATUS       (1 << 9)
# define RUNTIME_ERROR        (1 << 10)
// body types
# define MULTIPART_BODY   (1 << 1)
# define CHUNKED_BODY     (1 << 11)
# define LENGTH_BODY      (1 << 3)
# define BINARY_BODY      (1 << 4)
# define BODY_ERROR       (1 << 8)
# define BODY_STATUS      (1 << 6)
# define MULTIPART_STATUS (1 << 7)
# define BODY_SUCCESSFUL  (1 << 5)
// multipart macros
# define MULTIPART_BEGIN  (1 << 9)
# define MULTIPART_DONE   (1 << 8)
# define MLT_CRLF         (1 << 10)
# define MLT_BOUNDARY     (1 << 11)
# define MLT_HEADERS      (1 << 12)
# define MLT_CONTENT      (1 << 13)
# define MLT_HEADER_DONE  (1 << 14)
# define BN_OK     1   
# define BN_NO     2
# define BN_END    3
# define BN_WAIT   4
# define CRLF_OK   1
# define CRLF_NO   2
# define CRLF_WAIT 3

struct ShapeFile {

    public :
        FILE    *file;
        Header  _header;
        string  _openedFILE;
        string  _filename;
        string  name;
};

class requestBody {
    // private :
    public : 
        // chunked | binary | x-www-form | raw
        FILE                *bodycontent;
        string               bodyType;
        string               chunk_str;
        string               bodyPath;
        size_t               contentLength;
	    size_t               chunkedLength;
        size_t               content;
        bool                 _isBinary;
        bool                 _isHeader;
        mutable short       _status; // body status
        size_t                chunk_size;
        bool                 chunked_ok;
        bool                is_the_last_newline;

        // multipartBody 
        short                  _idx;
        stringstream            ss;
        pair<bool, string>      boundary;
        map<short, ShapeFile>  _multipart;
        mutable short          _multipartStatus;

        pair<bool, string> extractBoundary(string &);
        int absorbCRLF(stringstream &);

        void    FindBodyStatus( Header & );
        int     absorbBoundary(stringstream &, stringstream &);
        void    absorbHeaders(string &);

        bool    UpdateStatus(short) const ;
        void    absorb_stream(stringstream &);

        // absorb body types (binary , x-form, form-data, raw, none)
        void    multipartBody(stringstream &);
         void    chunkedBody(stringstream &);
        void    lengthedBody(stringstream &);
        
        requestBody(){
            bodycontent = NULL;
			_idx = 0;
            contentLength = 0;
            chunkedLength = 0;
            content = 0;
            _status = 0;
            _isBinary = false;
            _multipartStatus = MULTIPART_BEGIN | MLT_BOUNDARY;
            _isHeader = true;
            chunk_size = 0;
            chunked_ok = true;
            is_the_last_newline = false;
        }
        requestBody &operator=(const requestBody &rhs) {
            if (this != &rhs) {
                bodycontent = rhs.bodycontent;
                bodyType = rhs.bodyType;
                bodyPath = rhs.bodyPath;
                contentLength = rhs.contentLength;
                chunkedLength = rhs.chunkedLength;
                content = rhs.content;
                _status = rhs._status;
                _isBinary = rhs._isBinary;
                _multipartStatus = rhs._multipartStatus;
                _isHeader = rhs._isHeader;
                chunk_size = rhs.chunk_size;
                chunk_str = rhs.chunk_str;
                chunked_ok = rhs.chunked_ok;
                is_the_last_newline = rhs.is_the_last_newline;
            }
            return *this;
        }
        requestBody(const requestBody &copy) {
            *this = copy;
        }
        ~requestBody() {
            // if (bodycontent)
            //     fclose(bodycontent);
        }
}; 




# endif