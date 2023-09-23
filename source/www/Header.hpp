# ifndef _HEADER_H_
# define _HEADER_H_

# include <iostream>
# include <iterator>
# include <map>

using namespace std;

class Header : public map<string, string>
{
    public :

        bool     Search(const string &);
        void     adding(string, string );
        void     Disp();
        string   get(string key);
};

typedef Header::iterator HeaderIt;

# endif