#ifndef __CGI_EXC__
#define __CGI_EXC__

# include <map>
# include <iostream>

# include "server-core.hpp"

# define CGI_SUCCESS (1 << 1)
# define CGI_TIMEOUT (1 << 2)
# define CGI_WAITING (1 << 3)

using namespace std;

class supported_extension : map<string, string> {
    public :
        supported_extension();
        bool FindFileByExtension(const string &);
};

short WaitCgi(pid_t, time_t);

extern supported_extension cgiExtension;

# endif