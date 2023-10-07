
# include "utils.hpp"

# define TIMEOUT 17

struct timeval getmstime(void) 
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT;
	return (tv);
}

int    ft_ftruncate(FILE *file)  {
    fseek(file, 0, SEEK_END);

    long size = ftell(file);
    if (size >= 2) {
        return ftruncate(fileno(file), size - 2);
    }
    return -1;
}

bool contest(const char _c, char &target, stringstream &ss) {
    return _c == target && !ss.eof();
}

unsigned long set_time() {
    struct timeval _time;
	gettimeofday(&_time, NULL);
	return (unsigned long)_time.tv_usec * 10000;
}

int  s_write(FILE *file, stringstream &__DATA_TO_WRITE__) {
        // cout << "data to write : " << endl << __DATA_TO_WRITE__ << endl;
	if (fwrite(__DATA_TO_WRITE__.str().c_str(), 1, __DATA_TO_WRITE__.str().size(), file) == -1)
        return -1;
	__DATA_TO_WRITE__.clear();
	__DATA_TO_WRITE__.str("");
    fflush(file);
    return EXIT_SUCCESS;
}

FILE*    s_open(string &_FILE_PATH) {
    // cout << "check files : " << endl;
    FILE *file;
    file = fopen(_FILE_PATH.c_str(), "w+");
    if (!file)
        return NULL;
    return file;
}