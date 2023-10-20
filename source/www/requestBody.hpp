# ifndef __REQUEST_BODY_H__
# define __REQUEST_BODY_H__

# include "server-core.hpp"

# include <algorithm>
# include <sstream>
# include <deque>

# define CR   "\r"
# define LF   "\n"
# define CRLF "\r\n"

# define MULTIPART_BODY        (1 << 1)
# define CHUNKED_BODY          (1 << 2)
# define LENGTH_BODY           (1 << 3)

# define BODY_SUCCESSFUL       (1 << 4)

# define MULTIPART_BEGIN       (1 << 7)
# define MULTIPART_DONE        (1 << 8)
# define MLT_CRLF              (1 << 9)
# define MLT_BOUNDARY          (1 << 10)
# define MLT_HEADERS           (1 << 11)
# define MLT_CONTENT           (1 << 12)
# define MLT_HEADER_DONE       (1 << 13)
# define UNACCEPTABLE_REQUEST  (1 << 6)

# define BN_OK     1   
# define BN_NO     2
# define BN_END    3
# define BN_WAIT   4

# define CRLF_OK   1
# define CRLF_NO   2
# define CRLF_WAIT 3

typedef unsigned short t_stat;

struct ShapeFile {

    public :
        FILE    *file;
        Header  _header;
        string  _openedFILE;
        string  _filename;
        string  name;
};

class requestBody {

    public : 
        FILE                 *bodycontent;
        string                bodyType;
        string                bodyPath;

        size_t                contentLength;
        size_t                chunk_size;
        size_t                content;
        string                chunk_str;

        bool                  _isHeader;
        bool                  chunked_ok;
        bool                 is_the_last_newline;
        mutable t_stat        _status;


        /* 🕸 multipartBody  🕸 */
        #ifndef __MULTIPART__
            # define MULTIPART_STRING "multipart/form-data"
            # define BOUNDARY_STRING  "boundary"
            # define BOUNDARY_BEGIN   "--"
            # define HTTP_VERSION     "HTTP/1.1"
            # define METHODS_LENGHT 4
        # endif

        short                  _idx;
        stringstream            ss;
        pair<bool, string>      boundary;
        map<short, ShapeFile>  _multipart;
        mutable t_stat         _multipartStatus;

        pair<bool, string>  extractBoundary(string &);
        int                 absorbCRLF(stringstream &);
        int                 absorbBoundary(stringstream &, stringstream &);
        void                absorbHeaders(string &);

        void    FindBodyStatus(Header &);
        void    UpdateStatus(t_stat) const ;
        void    absorb_stream(stringstream &);
        void    closebodycontent();
        void    reset();

        /* 🕸  absorb body types (binary , x-form, form-data, raw, none)   🕸 */

        void    multipartBody(stringstream &);
        void    chunkedBody(stringstream &);
        void    lengthedBody(stringstream &);

        /* 🕸 ------------------------------------------------------------ 🕸 */


    requestBody() {
            bodycontent = NULL;
			_idx = 0;
            contentLength = 0;
            content = 0;
            _status = 0;
            _multipartStatus = MULTIPART_BEGIN | MLT_BOUNDARY;
            _isHeader = true;
            chunk_size = 0;
            chunked_ok = true;
            is_the_last_newline = false; 
        }

    requestBody &operator=(const requestBody& other) {
        if (this != &other) {
            bodycontent = other.bodycontent;
            bodyType = other.bodyType;
            bodyPath = other.bodyPath;
            contentLength = other.contentLength;
            chunk_size = other.chunk_size;
            content = other.content;
            chunk_str = other.chunk_str;
            _isHeader = other._isHeader;
            chunked_ok = other.chunked_ok;
            is_the_last_newline = other.is_the_last_newline;
            _status = other._status;
            _idx = other._idx;
            ss.str(other.ss.str()); 
            boundary = other.boundary;
            _multipart = other._multipart;
            _multipartStatus = other._multipartStatus;
        }
        return *this;
    }
    requestBody(const requestBody &copy) {
        *this = copy;
    }
    ~requestBody() {
    }
};

#endif