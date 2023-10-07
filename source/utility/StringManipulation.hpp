# ifndef _STRING_MANIPULATION_H_
# define _STRING_MANIPULATION_H_


# include <iostream>
# include <algorithm>
# include <sstream>

using namespace std;

bool identicalStrings(const std::string &_s1 = "" , const std::string &_s2 = "");

void leftTrim(string &_st, const string &sep = "\t ");
void rightTrim(string &_st, const string &sep = "\t ");
void trim(string &target, const string &sep = "\t ");

# endif