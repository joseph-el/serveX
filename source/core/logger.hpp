# ifndef __LOGGER_H__
# define __LOGGER_H__

# include <iostream>
# include <fstream>
# include <sstream>

# include "server-core.hpp"

using namespace std;

class Logger {
    public :
        ofstream logfile;
        void notice(const string &);
        string timer();
        bool run;
        bool running(void) const;
        Logger(string const &server = SERVER_PATH);
       ~Logger();
};

extern Logger logger;
    
# endif