# include "serveX.hpp"

void serveX::init_serveX( int argc, char *const *argv)
{
    char stream[(1 << 0xA)];
    
    signal(SIGPIPE, SIG_IGN);

    argc & ~required_argument ? throw E2BIG : argv++;

    serveX::sX_config(*argv);

    // Get virtual server

    while (true) {

    }
}