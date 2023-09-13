# if !defined(_SX_OPTIONEER_HPP_)
# define _SX_OPTIONEER_HPP_

# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <getopt.h>

# define serveX_NAME    "serveX"
# define serveX_VERSION "1.0.0"
# define GETOPT_EXIT -1
using namespace std;

class sX_config;

typedef int_fast32_t t_options;

extern "C" { 
    # include <unistd.h> 
}

extern const char* help_options =
                          "Usage: nginx [-?hvtT]\n"
                          "             [-e filename] [-c filename] \n"
                          "Options:\n"
                          "  -?,-h         : this help\n"
                          "  -v            : show version and exit\n"
                          "  -t            : test configuration and exit\n"
                          "  -T            : test configuration, dump it and exit\n"
                          "  -e filename   : set error log file (default: logs/error.log)\n"
                          "  -c filename   : set configuration file (default: conf/serveX.conf)\n";

extern const char* Sx_options = "?hvVTtce:";

enum options_flags {

    HELP = ( 1 << 1),
    VERSION = ( 1 << 2),
    UNKNOWN = ( 1 << 3),
    ERROR_LOG = ( 1 << 4),
    CONFIG_FILE = ( 1 << 5),
    TEST_CONFIG = ( 1 << 6),
    TEST_CONFIG_DUMP = ( 1 << 7),
    SHOW_VERSION_CONFIG = ( 1 << 8)

};

class options {
 
    public :
        options();
        void sX_options(int , char *const []);
        void setErrorLogFile(const string &) const;
        void setConfigFile(const string &) const;
        void testConfigAndDump() const;
        void showVersionAndConfig() const;
        void testConfig() const;
        void showHelp() const;
        void version( void ) const;
};

# endif