# include "serveX-core.hpp"

int serveX_main(__unused int argc, __unused char *const argv[])
{
    try {
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
            throw errno;
        init_serveX(argc, argv);
    }
    catch (...) {
        cerr << NAME " : " << strerror(errno);
    }
}