# include "sX_optioneer.hpp"

options::options(int argc, char *const argv[]) : p_conf(""), p_error(""), is_successful(false) {
    sX_options(argc, argv);
}

void options::sX_options(int argc, char *const argv[])
{
    t_options   option, flag;
    string      option_name(": invalid option: ");

    option = flag = opterr = false;

    for (; option != GETOPT_EXIT; option = getopt(argc, argv, Sx_options)) 
    {   
        flag |= (option == 'h') * HELP;
        flag |= (option == 'v') * VERSION;
        flag |= (option == 'e') * ERROR_LOG;
        flag |= (option == 't') * TEST_CONFIG;
        flag |= (option == 'c') * CONFIG_FILE;
        flag |= (option == 'T') * TEST_CONFIG_DUMP;
        flag |= (option == 'V') * SHOW_VERSION_CONFIG;
        flag  = (option == '?') ? UNKNOWN : flag;
        if (flag & UNKNOWN )
            goto something_else;        
        p_conf = p_error = ( flag & (CONFIG_FILE | ERROR_LOG) ) ? string(optarg) : "";
    }

    if (option ^ EPERM and !flag) 
        return (void)(is_successful = true);

    something_else:

        if (flag & ~( HELP | VERSION | ERROR_LOG | TEST_CONFIG | TEST_CONFIG_DUMP | SHOW_VERSION_CONFIG | CONFIG_FILE ))
        {
            option_name.push_back(optopt);
            cout << serveX_NAME << ( (optopt == 'e' or optopt == 'c') ? string(": option \"-") + string(1, optopt) + string("\" requires file name") : option_name) << endl;
        }
        else if ( flag & ~UNKNOWN ) 
            is_successful = true, (*this.*optionFunctions[ (int)log2(flag) - 1]) ();
}

void options::setErrorLogFile() const 
{
    struct stat _st;
    memset(&_st, 0, sizeof _st);
    errno = stat(p_error.c_str(), &_st) != 0 ? ENOENT : S_ISDIR(_st.st_mode) ? EISDIR : 0;

    if ( errno & (ENOENT | EISDIR) )
		cerr << serveX_NAME ": \"" << p_error << "\" failed : " << strerror(errno) << endl, is_successful = false;
    // set p_error
}

void options::setConfigFile() const 
{
    struct stat _st;
    memset(&_st, 0, sizeof _st);
    errno = stat(p_error.c_str(), &_st) != 0 ? ENOENT : S_ISDIR(_st.st_mode) ? EISDIR : 0;

    if ( errno & (ENOENT | EISDIR) )
		cerr << serveX_NAME ": \"" << p_conf << "\" failed : " << strerror(errno) << endl, is_successful = false;
        
    // set p_conf
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
    cout << (serveX_NAME " version:" serveX_NAME "/" serveX_VERSION) << endl;
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


// int main(int ac, char *const av[])
// {
//     options ret;

//     ret.sX_options(ac, av);

//     cout << (ret.successful() ? "yes option good" : "error in option ") << endl;
// }