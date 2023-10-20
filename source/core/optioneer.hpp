# ifndef _OPTIONEER_H_
# define _OPTIONEER_H_

# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <getopt.h>
# include <errno.h>
# include <sys/stat.h>

# include "server-core.hpp"

# define  GETOPT_EXIT    -1
# define  NAME    "Webserv"
# define _VERSION "1.0.0"

using namespace std;

typedef int_fast32_t t_options;

extern "C" { 
    # include <unistd.h> 
}

# define HELP_OPTIONS \
                        "Usage: Webserv [-?hvtT]\n" \
                        "             [-e filename] [-c filename] \n" \
                        "Options:\n" \
                        "  -?,-h         : this help\n" \
                        "  -v            : show version and exit\n" \
                        "  -t            : test configuration and exit\n" \
                        "  -T            : test configuration, dump it and exit\n" \
                        "  -e filename   : set error log file (default: logs/error.log)\n" \
                        "  -c filename   : set configuration file (default: conf/serveX.conf)"

# define Sx_options "hvVTtc:e:"

enum options_flags {

    HELP = ( 1 << 1),
    VERSION = ( 1 << 2),
    UNKNOWN = ( 1 << 8 ),
    ERROR_LOG = ( 1 << 3),
    CONFIG_FILE = ( 1 << 4),
    TEST_CONFIG = ( 1 << 5),
    TEST_CONFIG_DUMP = ( 1 << 6),
    SHOW_VERSION_CONFIG = ( 1 << 7 )

};

class Options {
    
    private :
        string p_conf, p_error;
        mutable bool    is_successful;

    public :
        Options(int , char *const []);
        void options(int , char *const []);
        void setErrorLogFile() const;
        void setConfigFile() const;
        void testConfigAndDump() const;
        void showVersionAndConfig() const;
        void testConfig() const;
        void showHelp() const;
        void version( void ) const;
        bool successful( void ) const;
};

typedef void (Options::*OptionFunction)() const;

extern OptionFunction optionFunctions[];

# endif