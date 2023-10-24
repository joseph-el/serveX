# include "server-core.hpp"

supported_extension::supported_extension() { // cgi supported extension 20
    
    insert(make_pair(".py", "python")); 
    insert(make_pair(".js", "JavaScript"));
    insert(make_pair(".rb", "Ruby"));
    insert(make_pair(".php", "PHP"));
    insert(make_pair(".pl", "Perl"));
    insert(make_pair(".sh", "Shell Scripting"));
    insert(make_pair(".R", "R"));
    insert(make_pair(".lua", "Lua"));
    insert(make_pair(".lisp", "Lisp"));
    insert(make_pair(".tcl", "Tcl"));
    insert(make_pair(".scm", "Scheme"));
    insert(make_pair(".groovy", "Groovy"));
    insert(make_pair(".swift", "Swift"));
    insert(make_pair(".hs", "Haskell"));
    insert(make_pair(".ts", "TypeScript"));
    insert(make_pair(".erl", "Erlang"));
    insert(make_pair(".kt", "Kotlin"));
    insert(make_pair(".clj", "Clojure"));

}

bool supported_extension::FindFileByExtension(const string &_filePath) {
    string::size_type idx = _filePath.find_last_of('.');
    if (idx == string::npos)
        return false;
    string exc = _filePath.substr(idx);
    if (find(exc) != end())
        return true;
    return false;
}

short WaitCgi(pid_t _pid, time_t BeginTime) {
	int status;
	int process;
    
    process = waitpid(_pid, &status, WNOHANG);
    if (process == _pid && (WIFSIGNALED(status) || WIFEXITED(status)))
        return CGI_SUCCESS;
    if (RUN_TIME(BeginTime)) {
        kill(_pid, SIGKILL);
        waitpid(_pid, 0, 0);
        return CGI_TIMEOUT;
    }
	return CGI_WAITING;
}

supported_extension cgiExtension;