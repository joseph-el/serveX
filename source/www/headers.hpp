# ifndef __HEADER_H__
# define __HEADER_H__

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
        void     Reestablish() {
                 clear();
        };
        string   get(string key);
};

typedef Header::iterator HeaderIt;

# endif