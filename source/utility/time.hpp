# ifndef __TIME_H__
# define __TIME_H__

extern "C" {
    # include <sys/time.h>
    # include <unistd.h>
}

# include <iostream>

using namespace std;

# define TIMEOUT 7

# define RUN_TIME(b) ( ( time(NULL) - b) >= TIMEOUT )

unsigned long set_time();
string getCurrentGMTTime();
struct timeval getmstime();

# endif