# include <iostream>
using namespace std;

#define CHECK_CONF_EXTENSION(fileName) \
    do { \
        string extension = ".conf"; \
        if (fileName.length() < extension.length() or \
            fileName.substr(fileName.length() - extension.length()) != extension) \
            cerr << "serveX: A Config File Must End With a .conf Extension\n", \
            exit(EXIT_FAILURE); \
    } while (false)


int main()
{
    string ret("dexter.conf");
    CHECK_CONF_EXTENSION(ret);
}