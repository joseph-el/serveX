# include "serveX-core.hpp"

struct timeval getmstime(void) 
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT;
	return (tv);
}

unsigned long set_time() {
    struct timeval _time;
	gettimeofday(&_time, nullptr);
	return (unsigned long)_time.tv_usec * 10000;
}


string getCurrentGMTTime() {
    time_t currentTime = time(nullptr);
    char buffer[50]; 

   strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&currentTime));
   return  string(buffer);
}
