# include "request.hpp"

void request::parseRequest(socket_t fd)
{
    // just for test
    char buffer[1024];
    unsigned long f;
    f = read(fd, buffer, 1024);
    buffer[f] = '\0';
    std::string req = buffer;
    cout << "the request form <" << fd << ">" << "is : " << endl << endl << req << endl;
    cout << endl;
}