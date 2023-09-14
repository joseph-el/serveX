# if !defined(_SX_OPTIONEER_HPP_)
# define _SX_OPTIONEER_HPP_

# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <getopt.h>
# include <errno.h>
# include <sys/stat.h>


# define GETOPT_EXIT    -1
# define serveX_NAME    "serveX"
# define serveX_VERSION "1.0.0"

using namespace std;

class sX_config;

typedef int_fast32_t t_options;

extern "C" { 
    # include <unistd.h> 
}

const char* help_options =
                          "Usage: nginx [-?hvtT]\n"
                          "             [-e filename] [-c filename] \n"
                          "Options:\n"
                          "  -?,-h         : this help\n"
                          "  -v            : show version and exit\n"
                          "  -t            : test configuration and exit\n"
                          "  -T            : test configuration, dump it and exit\n"
                          "  -e filename   : set error log file (default: logs/error.log)\n"
                          "  -c filename   : set configuration file (default: conf/serveX.conf)\n";

const char* Sx_options = "hvVTtc:e:";

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

class options {
    
    private :
        string p_conf, p_error;
        bool    is_successful;

    public :

        options();
        void sX_options(int , char *const []);
        void setErrorLogFile() const;
        void setConfigFile() const;
        void testConfigAndDump() const;
        void showVersionAndConfig() const;
        void testConfig() const;
        void showHelp() const;
        void version( void ) const;
        bool successful( void ) const;
};

typedef void (options::*OptionFunction)() const;

 OptionFunction optionFunctions[] = {
        &options::showHelp,
        &options::version,
        &options::setErrorLogFile,
        &options::setConfigFile,
        &options::testConfig,
        &options::testConfigAndDump,
        &options::showVersionAndConfig,
    };

# endif