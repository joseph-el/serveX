# include "serveX.hpp"
# include "utils/sX_optioneer.hpp"

void serveX::init_serveX( int argc, char *const *argv)
{
    options opt(argc, argv);
    
    char stream[ (1 << 0xA) ];

    signal(SIGPIPE, SIG_IGN);

    if (!opt.successful() ) // or sX_config .syntax
        return ;
    

    // argc & ~required_argument ? throw E2BIG : argv++;

    // Get virtual server

    while (true) {

    }
}