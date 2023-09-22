# include "core/server.hpp"

int Webserv_core(int argc, char *const argv[])
{
    try {
        init_Webserv(argc, argv);
    }
    catch (...) {
        cerr << NAME " : " << strerror(errno);
    }
}