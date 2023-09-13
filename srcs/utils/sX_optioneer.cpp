# include "sX_optioneer.hpp"


void options::sX_options(int argc, char *const argv[])
{
    t_options   option, flag;
    string      option_name(": invalid option: "), path;

    option = flag = opterr = NULL;

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
        path = (flag & CONFIG_FILE | ERROR_LOG) ? optarg : "";
    }
    
    unknown:
    
    if (flag & ~( HELP | VERSION | ERROR_LOG | TEST_CONFIG | TEST_CONFIG_DUMP | SHOW_VERSION_CONFIG ) or optind < argc)
    {
        option_name.push_back(optopt);
        cout << serveX_NAME << ( flag & ~UNKNOWN and optopt & 'c' and !optarg ? ": option \"-c\" requires file name" : option_name ) << endl;
        return ;
    }
    else
        (*this.*optionFunctions[ (int)log2(flag) ]) (), is_successful = true;
    p_conf = p_error = path;
}

void options::setErrorLogFile() const 
{
    errno = !filesystem::exists(p_error) ? ENOENT : filesystem::is_directory(p_error) ? EISDIR : 0;
    if ( errno & (ENOENT | EISDIR) )
		cerr << serveX_NAME ": \"" << p_error << "\" failed : " << strerror(errno) << endl;
}

void options::setConfigFile() const 
{
    errno = !filesystem::exists(p_conf) ? ENOENT : filesystem::is_directory(p_conf) ? EISDIR : 0;
    if ( errno & (ENOENT | EISDIR) )
		cerr << serveX_NAME ": \"" << p_conf << "\" failed : " << strerror(errno) << endl;
}

void options::testConfigAndDump() const 
{
    testConfig();
    // Sx_config.disp();
}

void options::testConfig() const 
{
    bool is_fine = true; // remplace by sX_config.good();
	cerr << serveX_NAME ": configuration file \"" << "path in config" << "\" test is " << (is_fine ? "successful" : "failed") << endl;
}

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

bool options::successful( void ) const { return is_successful; }