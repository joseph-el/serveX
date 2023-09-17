# if !defined(sX_logger_hpp)
# define sX_logger_hpp

#include <ifaddrs.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <limits>
#include <set>

using namespace std;

# define DEFAULT_ERROR  "/Users/joseph/Desktop/serveX/logs/error.conf"
# define DEFAULT_ACCESS "/Users/joseph/Desktop/serveX/logs/access.conf"

class sX_logger {

    public :
        string      _errorFileName;
        string      _accessFileName;
        ifstream    _errorFile;
        ifstream    _accessFile;

        sX_logger(const string& _errorFileName = DEFAULT_ERROR, const string& _accessFileName = DEFAULT_ACCESS);
        void error_log(const string &);
        void access_log(const string &);
    private :
        useconds_t Time() const;
};


# endif