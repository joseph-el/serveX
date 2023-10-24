# include "server-core.hpp"

/*  CGI Constructors    */
cgi::cgi    ( server_data const& server, location_data const& location, string const& _path )
{
    _script = _path; 
    _cgiBinPath = location.getCgiPath();
    errorMsg = "unknown Error";
    _pid = -1;
    _envp = NULL;
    outputCGIFile = stderrCGIFile =  -1;
    _initServerEnvVariables(server);
}

cgi::cgi    ( void ) {}

cgi::~cgi   ( void ) {
    if (_envp) {
        for (size_t i = 0; _envp[i]; ++i)
            delete[] _envp[i];
        delete[] _envp; 
        _envp = NULL;
    }
}

bool    cgi::executeCgi( request& req) {
    struct stat _stat;
    bzero(&_stat, sizeof _stat);

    stat(_cgiBinPath.c_str(), &_stat);
    if (S_ISDIR(_stat.st_mode)) 
        return errorMsg = string(strerror(EISDIR)), false;
    else {
        if (access(_cgiBinPath.c_str(), F_OK | X_OK) != 0)
            return errorMsg = string(strerror(errno)), false;
    }
    if (!_setupCgiEnvs(req) || !_initOutputFile() || !_executeCgiScript(req._body.bodycontent, req))
        return false;
    return true;
}

bool    cgi::_setupCgiEnvs( request& req) {

    _initRequestEnvVariables(req);

    std::map<std::string, std::string>::const_iterator it;
    
    for (it = _cgiEnvVars.begin(); it != _cgiEnvVars.end(); ++it)
        _tmpEnvs.push_back(it->first + "=" + it->second);

    _envp = new char*[_tmpEnvs.size() + 1];
    if (!_envp) {
        errorMsg = "Failed To Allocate Memory For execve() ENVS";
        return false;
    }
    _envp[_tmpEnvs.size()] = NULL;
    for (size_t i = 0; i < _tmpEnvs.size(); i++) {
        _envp[i] = new char[_tmpEnvs[i].size() + 1];
        if (!_envp[i]) {
            errorMsg = "Failed To Allocate Memory For execve() ENV";
            return false;
        }
        strcpy(_envp[i], _tmpEnvs[i].c_str());
    }
    return true;
}

bool    cgi::_initOutputFile( void) {  
    
    FILE* Cgi_stderr, *Cgi_stdout;

    Cgi_stderr = tmpfile();
    Cgi_stdout = tmpfile();

    if (!Cgi_stderr || !Cgi_stdout) {
        errorMsg = string(strerror(errno));
        return false;
    }
    outputCGIFile = fileno(Cgi_stdout);
    stderrCGIFile = fileno(Cgi_stderr);
    return true;
}

bool    cgi::_executeCgiScript( FILE *body, request& req ) {

    _pid = fork();
    if (_pid < 0) {
        errorMsg = string(strerror(errno));
        return false;
    }
    if (!_pid) {
        if (req._method & POST) {
            if (!body)
                _exit(EXIT_FAILURE);
            rewind(body);
            if (dup2(fileno(body), STDIN_FILENO) < 0)
                _exit(EXIT_FAILURE);
        }
        if (dup2(outputCGIFile, STDOUT_FILENO) < 0)
            _exit(EXIT_FAILURE);
        if (dup2(stderrCGIFile, STDERR_FILENO) < 0)
            _exit(EXIT_FAILURE);
        close (outputCGIFile);
        close (stderrCGIFile);
        char* args[3];
        args[0] = const_cast<char*>(_cgiBinPath.c_str());
        args[1] = const_cast<char*>(_script.c_str());
        args[2] = NULL;
        execve(args[0], args, _envp);
        _exit(EXIT_FAILURE);
    }
    return true;
}

// const char *httpmethods[] = { "GET", "POST", "DELETE", "UNKNOWN" };


void    cgi::_initServerEnvVariables( server_data const& server ) {
    _cgiEnvVars["SERVER_SOFTWARE"] = NAME "/" _VERSION;
    _cgiEnvVars["SERVER_NAME"] = server.getServerName();
    _cgiEnvVars["GATEWAY_INTERFACE"] = "CGI/1.1";
    _cgiEnvVars["SERVER_PORT"] = to_string(server.getListenPort());
    _cgiEnvVars["SERVER_PROTOCOL"] = HTTP_VERSION;
}

// initialize envirenement variables releated to the request
void    cgi::_initRequestEnvVariables( request & req ) {

    try {
        string::size_type idx = _script.find(SERVER_PATH);
        idx += sizeof(SERVER_PATH);
        _cgiEnvVars["SCRIPT_NAME"] = _script.substr(idx);
    } catch (...) {}
    _cgiEnvVars["SCRIPT_FILENAME"] = _script;
    _cgiEnvVars["DOCUMENT_ROOT"] = SERVER_PATH;
    if (req._method & GET)
        _cgiEnvVars["REQUEST_METHOD"] = "GET";
    else if (req._method & POST)
        _cgiEnvVars["REQUEST_METHOD"] = "POST";
    else
        _cgiEnvVars["REQUEST_METHOD"] = "DELETE";
    _cgiEnvVars["QUERY_STRING"] = req._query;
    _cgiEnvVars["CONTENT_TYPE"] = req._body.bodyType; 
    _cgiEnvVars["CONTENT_LENGTH"] = to_string(req._body.contentLength);
    _cgiEnvVars["HTTP_COOKIE"] = req._header.get("Cookie");
    _cgiEnvVars["REDIRECT_STATUS"] = "200";
}