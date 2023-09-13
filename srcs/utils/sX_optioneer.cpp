# include "sX_optioneer.hpp"

void options::version() const {
    cout << (serveX_NAME "serveX version:" serveX_NAME "/" serveX_VERSION) << endl;
}

void options::showHelp( void ) const {
    cout << (serveX_NAME "/" serveX_VERSION) << endl;
    cout << help_options;
}

void options::showVersionAndConfig() const {
    version();
    cout << "built with OpenSSL 3.0.5 5 Jul 2022 (running with OpenSSL 3.0.10 1 Aug 2023)"
            "TLS SNI support enabled" << endl;
}

void options::sX_options(int argc, char *const argv[])
{
    t_options   option, flag;
    string      option_name;

    option = flag = NULL;

    for (; option != GETOPT_EXIT; option = getopt(argc, argv, Sx_options)) 
    {   
        flag |= (option == 'h') * HELP;
        flag |= (option == 'v') * VERSION;
        flag |= (option == '?') * UNKNOWN;
        flag |= (option == 'e') * ERROR_LOG;
        flag |= (option == 't') * TEST_CONFIG;
        flag |= (option == 'c') * CONFIG_FILE;
        flag |= (option == 'T') * TEST_CONFIG_DUMP;
        flag |= (option == 'V') * SHOW_VERSION_CONFIG;
        if (flag & UNKNOWN)
            goto unknown;
    }
    
    unknown:

    

}