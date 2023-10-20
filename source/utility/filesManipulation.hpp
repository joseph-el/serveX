# ifndef __FILES_IO_H__
# define __FILES_IO_H__

extern "C" {
    # include <fcntl.h>
    # include <stdlib.h>
    # include <signal.h>
}

# include <iostream>
# include <sstream>

using namespace std;

FILE*    s_open(string &);
int      ft_ftruncate(FILE *) ;
int      getFileDescriptor(FILE* ); 
int      s_write(FILE *, stringstream &);
void     closefiles(int (&fds)[2]);
size_t   get_ifstream_size(ifstream &);
size_t   get_ostringstream_size(stringstream &);

#endif