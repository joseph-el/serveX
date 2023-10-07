# ifndef _UTILS_H_
# define _UTILS_H_

extern "C" {
        # include <sys/time.h>
        # include <unistd.h>
        # include <string.h>
        # include <ctype.h>
        # include <fcntl.h>
        # include <stdlib.h>
        # include <sys/time.h>
}

# include <iostream>
# include <sstream>

using namespace std;

struct timeval  getmstime(void) ;
unsigned long   set_time();
FILE*           s_open(string &_FILE_PATH);
int             ft_ftruncate(FILE *file);
int             s_write(FILE *file, stringstream &__DATA_TO_WRITE__);
bool            contest(const char _c, char &target, stringstream &ss);

# endif