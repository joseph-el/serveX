# include "serveX.hpp"

int serveX_core(int argc, char *const argv[])
{   
    
    try {
        serveX::init_serveX(argc, argv);
    }
    catch (...) {
        std::cerr << strerror(errno);
    }

    exit (EXIT_SUCCESS);
}