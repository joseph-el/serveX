# include "serveX.hpp"

int serveX_core(int argc, char *const argv[])
{   
    try {

        system("script/init-serveX.sh"); // beta test !
        
        serveX::init_serveX(argc, argv);
    
    }
    catch (...) {
        std::cerr << "serveX : " << strerror(errno);
    }

    exit (EXIT_SUCCESS);
}