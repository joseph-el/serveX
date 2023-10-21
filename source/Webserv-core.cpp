# include "server-core.hpp"

int Webserv_core(int argc, char *const argv[])
{
    if (argc != 2) {
        cerr << strerror(EINVAL) << endl;
        exit(EXIT_FAILURE);
    }
    argv++;
    string p_conf(*argv);
    struct stat _st;
    bzero(&_st, sizeof _st);
    errno = stat(p_conf.c_str(), &_st) != 0 ? ENOENT : S_ISDIR(_st.st_mode) ? EISDIR : 0;
    if ( errno & (ENOENT | EISDIR) ) {
		cerr << NAME ": \"" << p_conf << "\" failed : " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    MainContext.setPath(p_conf);
    try {
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
            throw errno;
        init_Webserv(argc, argv);
    }
    catch (...) {
        cerr << NAME " : " << strerror(errno);
    }
    return EXIT_SUCCESS;
}