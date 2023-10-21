# ifndef __RESPONSES_H__
# define __RESPONSES_H__

# include <dirent.h>
# include <errno.h>

# include "server-core.hpp"

# define LOCATION_CGI         (1 << 9)
# define PATH_NOT_FOUND       (1 << 6)
# define LOCATION_UPLOAD      (1 << 8)
# define METHOD_NOT_ALLOW     (1 << 4)
# define NORMAL_FILE_PATH     (1 << 5)
# define PATH_IS_DIRECTORY    (1 << 7)
# define REDIRECTIVE_SERVER   (1 << 1)
# define LOCATION_NOT_FOUND   (1 << 3)
# define REDIRECTIVE_LOCATION (1 << 2)
# define RECV_BYTES_TOO_LARGE (1 << 10)

# define HTTP_RESPONSE_ERROR    (PATH_NOT_FOUND | METHOD_NOT_ALLOW | LOCATION_NOT_FOUND | RECV_BYTES_TOO_LARGE)

# define RESPONSE_INIT          (1 << 1)
# define RESPONSE_BODY          (1 << 2)
# define RESPONSE_DONE          (1 << 3)
# define RESPONSE_HEADERS       (1 << 4)

# define PAGES_SEND_DONE        (1 << 5)
# define RESPONSE_CGI_BODY      (1 << 6)
# define RESPONSE_CHUNKED_BODY  (1 << 7)
# define RESPONSE_LENGHTED_BODY (1 << 8)

# define ErrPage(_stat, _vts) _setup_error_pages((_stat), (_vts))
# define NewUrl(_directive)   _setup_redirective_((_directive))
# define Upload               _setup_upload_response_()
# define RunCgi(_p)           _setup_cgi_response_((_p))
# define _send(fd)            _send_response((fd))

# define  REQ (*req)
# define  VTS &(*_vts)
# define  LCT &(*_location)
# define  LOCATION (*_location)

# define INIT_SWITCH_STATUS -1


# define N_INIT      (1 << 1)
# define N_DONE      (1 << 2)       
# define N_FAILED    (1 << 3)
# define N_WARNING   (1 << 4)

typedef map<int, string> ErrorPages;
typedef vector<string>::const_iterator v_t;

class response {

    private :

        short          _stat;
        short          _httpCodeSatus;
        bool           _keepAlive;

        pid_t          _cgi;
        time_t         _time;
        string         _pathFile;
        int            _fdCgi[CGI_FDS]; // [0] for Cgi_stdout [1] for Cgi_stderr
        Header         _headers;

        request       *req;
        ifstream      *file;
        server_data   *_vts;
        stringstream   _pages;
        stringstream   _stream;
        location_data *_location;
    
    public :
        void interpret_response(socket_t &); // mainFunction
        short absorbSatus(string&);
        void cgi_supervisor(void);
        bool likeness(const int) const;
        bool cgi_stderr();
        long long found(string const&, string const& );
        
        bool _build_cgi_body();
        void _build_upload_response_page();
        void _build_directory_listing_(const string&);
        void _build_uploading_page_(size_t);
        void _build_alert_user_messages_(short, const string &msg = "");
        void _build_response_page_(const int &, const string &msg = "");
        void _buid_redirective_page_(const int &, const string &msg = "");
        
        void _setup_response_message_();
        void _setup_upload_response_(void);
        void _setup_uploading_page_(size_t);
        void _setup_cgi_response_(const string &);
        void _setup_chunked_response_(const string &);
        void _setup_lenghted_response_(const string &);
        void _setup_lenghted_type_(const string &, bool);
        void _setup_normal_upload_(const string &, bool);
        void _setup_multipart_upload_(const string &, bool);
        void _setup_redirective_(const pair<int, string> *, bool local = true);
        void _setup_delete_response_page(short, const string &);
        void _setup_error_pages(const int &, const ErrorPages *, const string &msg = "");


        void _init_headers_(void);
        void  revokeItem(string, bool); 
        void _find_error_pages_(const ErrorPages*);

        bool  send(socket_t &, const char *, const size_t &);
        void _send_response(socket_t);
        void _send_chunked_body_(socket_t);
        void _send_lenghted_body_(socket_t);
        void _send_cgi_body_(socket_t);

        void _set_stat_(const short);
        void _set_connection_(const bool);
        void _set_http_code_status_(const short);
        void set(const server_data*, request &);
    
    
        void reset();
        void killCgi();
        void closeStreamFile();
        response();
       ~response();
        response &operator=(const response &other) {
	        if (this != &other) {
                _stat = other._stat;
                _httpCodeSatus = other._httpCodeSatus;
                _keepAlive = other._keepAlive;
                _cgi = other._cgi;
                _time = other._time;
                _fdCgi[CGI_OUT] = other._fdCgi[CGI_OUT];
                _fdCgi[CGI_ERR] = other._fdCgi[CGI_ERR];
                _headers = other._headers;
                req = other.req;
                file = other.file;
                _vts = other._vts;
                _pages.str(other._pages.str());
                _stream.str(other._stream.str());
                _location = other._location;
            }
	        return *this;
        }
        response(const response &copy) {
            *this = copy;
        }
};


# endif