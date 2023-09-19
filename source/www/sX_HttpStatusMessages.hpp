# if !defined(_HttpStatusMessages_H_)
# define _HttpStatusMessages_H_

# include <map>
# include <array>
# include <iterator>
# include <iostream>

using namespace std;

# define HTTP_CONTINUE 100
# define HTTP_SWITCHING_PROTOCOLS 101
# define HTTP_AVAILABLE_METHOD 9

# define HTTP_OK 200
# define HTTP_CREATED 201
# define HTTP_ACCEPTED 202
# define HTTP_NON_AUTHORITATIVE_INFORMATION 203
# define HTTP_NO_CONTENT 204
# define HTTP_RESET_CONTENT 205
# define HTTP_PARTIAL_CONTENT 206
 
# define HTTP_MULTIPLE_CHOICES 300
# define HTTP_MOVED_PERMANENTLY 301
# define HTTP_FOUND 302
# define HTTP_SEE_OTHER 303
# define HTTP_NOT_MODIFIED 304
# define HTTP_USE_PROXY 305
# define HTTP_TEMPORARY_REDIRECT 307
 
# define HTTP_BAD_REQUEST 400
# define HTTP_UNAUTHORIZED 401
# define HTTP_PAYMENT_REQUIRED 402
# define HTTP_FORBIDDEN 403
# define HTTP_NOT_FOUND 404
# define HTTP_METHOD_NOT_ALLOWED 405
# define HTTP_NOT_ACCEPTABLE 406
# define HTTP_PROXY_AUTHENTICATION_REQUIRED 407
# define HTTP_REQUEST_TIMEOUT 408
# define HTTP_CONFLICT 409
# define HTTP_GONE 410
# define HTTP_LENGTH_REQUIRED 411
# define HTTP_PRECONDITION_FAILED 412
# define HTTP_REQUEST_ENTITY_TOO_LARGE 413
# define HTTP_REQUEST_URI_TOO_LONG 414
# define HTTP_UNSUPPORTED_MEDIA_TYPE 415
# define HTTP_REQUESTED_RANGE_NOT_SATISFIABLE 416
# define HTTP_EXPECTATION_FAILED 417

# define HTTP_INTERNAL_SERVER_ERROR 500
# define HTTP_NOT_IMPLEMENTED 501
# define HTTP_BAD_GATEWAY 502
# define HTTP_SERVICE_UNAVAILABLE 503
# define HTTP_GATEWAY_TIMEOUT 504
# define HTTP_HTTP_VERSION_NOT_SUPPORTED 505
 
enum HttpMethod : int32_t {
    GET     = 1 << 1,
    PUT     = 1 << 2,
    POST    = 1 << 3,
    HEAD    = 1 << 4,
    PATCH   = 1 << 5,
    TRACE   = 1 << 6,
    DELETE  = 1 << 7,
    CONNECT = 1 << 8,
    OPTIONS = 1 << 9,
    UNK_METHOD = 1 << 10,
    HTTP_METHOD = GET | PUT | POST | HEAD | PATCH | TRACE | DELETE | CONNECT | OPTIONS
};

class HttpStatusMessages : public map <int32_t, string> {
     public :
         HttpStatusMessages();
};

extern HttpStatusMessages httpstatusmessages;
extern string httpMethods[HTTP_AVAILABLE_METHOD];

# endif