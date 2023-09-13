# if !defined(serveX_HPP)
# define serveX_HPP

# include <iostream>
# include <execution>
# include <errno.h>

# define serveX_core main
# define required_argument 2

namespace serveX {

    class sX_config;

    void init_serveX( int , char *const *);

};

# endif