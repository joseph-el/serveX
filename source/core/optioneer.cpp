# include "optioneer.hpp"

OptionFunction optionFunctions[] = {
        &Options::showHelp,
        &Options::version,
        &Options::setErrorLogFile,
        &Options::setConfigFile,
        &Options::testConfig,
        &Options::testConfigAndDump,
        &Options::showVersionAndConfig,
};

Options::Options(int argc, char *const argv[]) : p_conf(""), p_error(""), is_successful(false) {
    options(argc, argv);
}

void Options::options(int argc, char *const argv[])
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
        if ( flag & UNKNOWN )
            goto something_else;        
        p_conf = p_error = ( flag & (CONFIG_FILE | ERROR_LOG) ) ? string(optarg) : "";
    }

    if (option ^ EPERM and !flag) 
        return (void)(is_successful = true);

    something_else:

        if (flag & ~( HELP | VERSION | ERROR_LOG | TEST_CONFIG | TEST_CONFIG_DUMP | SHOW_VERSION_CONFIG | CONFIG_FILE ))
        {
            option_name.push_back(optopt);
            cout << NAME << ( (optopt == 'e' or optopt == 'c') ? string(": option \"-") + string(1, optopt) + string("\" requires file name") : option_name) << endl;
        }
        else if ( flag & ~UNKNOWN ) 
            (*this.*optionFunctions[ (int)log2(flag) - 1]) ();
    is_successful = (flag & CONFIG_FILE);
}

/*
    i will handel logs in my serveX ;
*/

void Options::setErrorLogFile() const 
{
    struct stat _st;
    memset(&_st, 0, sizeof _st);
    errno = stat(p_error.c_str(), &_st) != 0 ? ENOENT : S_ISDIR(_st.st_mode) ? EISDIR : 0;

    if ( errno & (ENOENT | EISDIR) )
		cerr << NAME ": \"" << p_error << "\" failed : " << strerror(errno) << endl, is_successful = false;
    // set p_error
}

void Options::setConfigFile() const 
{
    struct stat _st;
    memset(&_st, 0, sizeof _st);
    errno = stat(p_error.c_str(), &_st) != 0 ? ENOENT : S_ISDIR(_st.st_mode) ? EISDIR : 0;

    if ( errno & (ENOENT | EISDIR) )
		cerr << NAME ": \"" << p_conf << "\" failed : " << strerror(errno) << endl, is_successful = false;
    
    MainContext.setPath(p_conf);
}

void Options::testConfigAndDump() const 
{  
    testConfig();
    if (is_successful)
        MainContext.disp();
}

void Options::testConfig() const 
{
    is_successful = MainContext.successful();
    if (is_successful)
        cerr << NAME ": the configuration file " << MainContext._configFileName << " syntax is ok" << endl;
	cerr << NAME ": configuration file \"" << MainContext._configFileName << "\" test is " << (is_successful ? "successful" : "failed") << endl;
}

void Options::version() const {
    cout << (NAME " version:" NAME "/" _VERSION) << endl;
}

void Options::showHelp( void ) const {
    cout << (NAME "/" _VERSION) << endl;
    cout << HELP_OPTIONS << endl;
}

void Options::showVersionAndConfig() const {
    version();
    cout << "built with OpenSSL 3.0.5 5 Jul 2022 (running with OpenSSL 3.0.10 1 Aug 2023)"
            "TLS SNI support enabled" << endl;
}

bool Options::successful( void ) const { return is_successful; }
