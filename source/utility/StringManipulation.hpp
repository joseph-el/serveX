# ifndef __STRING_MANIPULATION_H__
# define __STRING_MANIPULATION_H__

# include <iostream>
# include <algorithm>
# include <sstream>

# include "server-core.hpp"

using namespace std;

size_t            hex_to_dec(string);
void              leftTrim(string &_st, const string &sep = "\t ");
void              rightTrim(string &_st, const string &sep = "\t ");
void              trim(string &target, const string &sep = "\t ");
bool              identicalStrings(const string &_s1 = "" , const string &_s2 = "");
bool              contest(const char , char &, stringstream &);
string::size_type commonPrefix(const string &s1, const string &s2 = "");
string            joinPath(const string &, const string &Secound = "/") ;
string            clientmsg(socket_t, bool);

#endif