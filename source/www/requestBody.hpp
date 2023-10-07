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
# define CHUNKED_BODY     (1 << 2)
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

class ShapeFile {

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
        string               bodyPath;
        size_t               contentLength;
	    size_t               chunkedLength;
        size_t               content;

        mutable short       _status; // body status

        // multipartBody 
        short                  _idx;
        stringstream            ss;
        pair<bool, string>      boundary;
        map<short, ShapeFile>  _multipart;
        mutable short          _multipartStatus;
        
        pair<bool, string> extractBoundary(string &);
        int absorbCRLF(stringstream &);

        void    FindBodyStatus( Header & );
        void    lengthedBody(stringstream &);
        int     absorbBoundary(stringstream &, stringstream &);
        void    absorbHeaders(string &);

        bool    UpdateStatus(short) const ;
        void    absorb_stream(stringstream &);

        // absorb body types
        void    multipartBody(stringstream &);
        // void    chunkedBody(stringstream &);
        // void    lengthedBody(stringstream &);
        // void    binaryBody(stringstream &);
        
        requestBody(){
            bodycontent = NULL;
			_idx = 0;
            contentLength = 0;
            chunkedLength = 0;
            content = 0;
            _status = 0;
            _multipartStatus = MULTIPART_BEGIN | MLT_BOUNDARY;
        }
        requestBody &operator=(const requestBody &rhs) {
	        (void)rhs;
	        return *this;
        }
        requestBody(const requestBody &copy) {
            (void)copy;
        }
        ~requestBody() {
            // if (bodycontent)
            //     fclose(bodycontent);
        }
}; 




# endif