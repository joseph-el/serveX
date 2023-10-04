# include "request.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <strings.h>
#include <sys/_types/_off_t.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// stringstream *  dd = new stringstream;

void request::parseRequest(socket_t fd)
{
    struct stat fileStat;

    char buffer[1024];
    if (counte == 0)
        stream = new stringstream;
    
    unsigned long f;
    bzero(buffer, 1024);
    f = recv(fd, buffer, 1024, 0);
    counte++;
    if (f < 0)
    {
        perror("read");
        return ;
    }
    stream->write(buffer, f);
    
    fstat(fd, &fileStat);
    if (counte == 1)
        request_string = buffer;
    
    if (counte == 1 && request_string.find("POST") == std::string::npos)
    {
        ready = true;
        return ;
    }

    if (fileStat.st_size == 0) {
        cout << counte << endl;
        counte = 0;
        ready = true;
        ofstream uu("hello", std::ios::trunc);
        uu << stream->str();
        delete stream;
    }
}