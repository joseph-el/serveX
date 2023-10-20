
# include "server-core.hpp"

HttpStatusMapping::HttpStatusMapping( void ) 
{
    (*this)[HTTP_CONTINUE] = "Continue";
    (*this)[HTTP_SWITCHING_PROTOCOLS] = "Switching Protocols";

    (*this)[HTTP_OK] = "OK";
    (*this)[HTTP_CREATED] = "Created";
    (*this)[HTTP_ACCEPTED] = "Accepted";
    (*this)[HTTP_NON_AUTHORITATIVE_INFORMATION] = "Non - Authoritative Information";
    (*this)[HTTP_NO_CONTENT] = "No Content";
    (*this)[HTTP_RESET_CONTENT] = "Reset Content";
    (*this)[HTTP_PARTIAL_CONTENT] = "Partial Content";

    (*this)[HTTP_MULTIPLE_CHOICES] = "Multiple Choices";
    (*this)[HTTP_MOVED_PERMANENTLY] = "Moved Permanently";
    (*this)[HTTP_FOUND] = "Found";
    (*this)[HTTP_SEE_OTHER] = "See Other";
    (*this)[HTTP_NOT_MODIFIED] = "Not Modified";
    (*this)[HTTP_USE_PROXY] = "Use Proxy";
    (*this)[HTTP_TEMPORARY_REDIRECT] = "Temporary Redirect";
    // my exit codes

    (*this)[UNACCEPTABLE_REQUEST] = "Unacceptable Request !";
    
    (*this)[HTTP_BAD_REQUEST] = "Bad Request";
    (*this)[HTTP_UNAUTHORIZED] = "Unauthorized";
    (*this)[HTTP_PAYMENT_REQUIRED] = "Payment Required";
    (*this)[HTTP_FORBIDDEN] = "Forbidden";
    (*this)[HTTP_NOT_FOUND] = "Not Found";
    (*this)[HTTP_METHOD_NOT_ALLOWED] = "Method Not Allowed";
    (*this)[HTTP_NOT_ACCEPTABLE] = "Not Acceptable";
    (*this)[HTTP_PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
    (*this)[HTTP_REQUEST_TIMEOUT] = "Request Timeout";
    (*this)[HTTP_CONFLICT] = "Conflict";
    (*this)[HTTP_GONE] = "Gone";
    (*this)[HTTP_LENGTH_REQUIRED] = "Length Required";
    (*this)[HTTP_PRECONDITION_FAILED] = "Precondition Failed";
    (*this)[HTTP_REQUEST_ENTITY_TOO_LARGE] = "Request Entity Too Large";
    (*this)[HTTP_REQUEST_URI_TOO_LONG] = "Request-URI Too Long";
    (*this)[HTTP_UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
    (*this)[HTTP_REQUESTED_RANGE_NOT_SATISFIABLE] = "Requested Range Not Satisfiable";
    (*this)[HTTP_EXPECTATION_FAILED] = "Expectation Failed";

    (*this)[HTTP_INTERNAL_SERVER_ERROR] = "Internal Server Error";
    (*this)[HTTP_NOT_IMPLEMENTED] = "Not Implemented";
    (*this)[HTTP_BAD_GATEWAY] = "Bad Gateway";
    (*this)[HTTP_SERVICE_UNAVAILABLE] = "Service Unavailable";
    (*this)[HTTP_GATEWAY_TIMEOUT] = "Gateway Timeout";
    (*this)[HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";
}

HttpStatusMapping WebStatusMap;
