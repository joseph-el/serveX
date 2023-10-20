#ifndef __CGI_H__
#define __CGI_H__

# include <iostream>
# include <vector>
# include <map>
# include <cstring>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>

# include "server-core.hpp"

# define ErrCgi(msg) _setup_error_pages(500, VTS.getErrorPages(), (msg));
# define CGI_OUT 0
# define CGI_ERR 1
# define CGI_FDS 2

class request;
class   cgi {

public:

    cgi             ( server_data const& , location_data const&, string const&);
    ~cgi            ( void );
    bool            executeCgi( request& );
    string          errorMsg;
    int             _pid;
    int             outputCGIFile;
    int             stderrCGIFile;
    string         _cgiOutputPath;
    void            closefiles();

private:

    cgi                             ( void );
    string                         _script;
    char**                         _envp;
    vector<string>                 _tmpEnvs;
    string                         _cgiBinPath;
    map<string, string>            _cgiEnvVars;

    /*  Helper Private Functions */
    void            _initServerEnvVariables( server_data const& );
    void            _initRequestEnvVariables( request& );
    bool            _initOutputFile( void );
    bool            _setupCgiEnvs( request& );
    bool            _executeCgiScript( FILE *body, request& );
    std::string     _intToString( int );
    unsigned long   _initTime( void );




};
#endif