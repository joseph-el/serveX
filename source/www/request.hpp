# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "../core/config.hpp"
# include "socket.hpp"

enum METHODS {
    GET,
    POST ,
    DELETE 
};

typedef set< pair<string ,string> >::iterator HeaderIt;

class Header : set< pair<string ,string> > 
{
    public :

        HeaderIt find(const string &key);
        void     adding(string, string );
        void     Disp();
        string get(string key);

};

class request 
{
    public :
        request() {
            
        }

        void parseRequest(socket_t fd) {
            
            // just for test
            char buffer[1024];
            unsigned long f;
            f = read(fd, buffer, 1024);
            buffer[f] = '\0';
            std::string req = buffer;
            cout << "the request form <" << fd << ">" << "is : " << endl << endl << req << endl;
            cout << endl;
        }


    private :
        stringstream *stream;
        
        METHODS httpMethod;
        string  path_;
        string  line_;
        string  query_;
        Header  header_;
    
};

# endif