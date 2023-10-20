# include "server-core.hpp"

int Webserv_core(int argc, char *const argv[])
{
    try {
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
            throw errno;
        init_Webserv(argc, argv);
    }
    catch (...) {
        cerr << NAME " : " << strerror(errno);
    }
}