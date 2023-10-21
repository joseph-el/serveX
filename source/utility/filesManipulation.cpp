# include "server-core.hpp"

int  s_write(FILE *file, stringstream &__DATA_TO_WRITE__) {
	fwrite(__DATA_TO_WRITE__.str().c_str(), 1, __DATA_TO_WRITE__.str().size(), file);
	__DATA_TO_WRITE__.clear();
	__DATA_TO_WRITE__.str("");
    fflush(file);
    return EXIT_SUCCESS;
}

FILE*    s_open(string &_FILE_PATH) {
    FILE *file;
    file = fopen(_FILE_PATH.c_str(), "w+");
    if (!file)
        return NULL;
    return file;
}

int getFileDescriptor(FILE* file) {
    if (file != NULL)
        return fileno(file);
    return -1;
}

int    ft_ftruncate(FILE *file)  {
    if (!file)
        return -1;
    fseek(file, 0, SEEK_END);

    long size = ftell(file);
    if (size >= 2)
        return ftruncate(fileno(file), size - 2);
    return -1;
}

size_t get_ostringstream_size(stringstream &oss) {
    string::size_type StreamSize;
    StreamSize = oss.str().size();
    return StreamSize;
}

size_t get_ifstream_size(ifstream &stream) {
    stream.seekg(0, ios::end);
    streampos fileSize = stream.tellg() < 0 ? (streampos)0 : stream.tellg();
    stream.seekg(0, ios::beg);
    return  static_cast<size_t>(fileSize);
}

void closefiles(int (&fds)[2]) {

    if (fds[1] > 2)
        close (fds[1]);
    if (fds[0] > 2)
        close (fds[0]);
    fds[0] = fds[1] = -1;
}