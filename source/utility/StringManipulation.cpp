# include "StringManipulation.hpp"
# include <algorithm>

bool identicalStrings(const std::string &_st1, const std::string &_st2)
{
	string _s1(_st1), _s2(_st2);
    if (_s1.empty() or _s2.empty())
        return false;
    
	for (string::iterator it1 = _s1.begin(); it1 != _s1.end(); it1++ )
		*it1 = toupper(*it1);
	for (string::iterator it2 = _s2.begin(); it2 != _s2.end(); it2++ )
		*it2 = toupper(*it2);
    // for_each(_s1.begin(), _s1.end(), [](char &c) { c = toupper(static_cast<unsigned char>(c)); });
    // for_each(_s2.begin(), _s2.end(), [](char &c) { c = toupper(static_cast<unsigned char>(c)); });
    return (_s1 == _s2);
}

void leftTrim(string &_st, const string &sep) {
	string::iterator it = _st.begin();
	while (it != _st.end() && ::strchr(sep.c_str(), *it))
		it++;
	_st.erase(_st.begin(), it);
}

void rightTrim(string &_st, const string &sep) {
	string::reverse_iterator it = _st.rbegin();
	while (it != _st.rend() && ::strchr(sep.c_str(), *it))
		it++;
	_st.erase(_st.length() - (it - _st.rbegin()));
}

void trim(string &target, const string &sep) {
	leftTrim (target, sep);
	rightTrim(target, sep);
}