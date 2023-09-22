
# include "utils.hpp"

# define TIMEOUT 17

struct timeval getmstime(void) 
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT;
	return (tv);
}