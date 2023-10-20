# include "server-core.hpp"

string joinPath(const string &CrrPath, const string &Secound) {
	if (CrrPath.empty()  or Secound.empty())
		return CrrPath + Secound;
	string path(CrrPath);
	if (CrrPath.back() != '/' && Secound.front() != '/')
		path += "/";
	else if (CrrPath.back() == '/' and Secound.front() == '/')
		return CrrPath.substr(0, CrrPath.length() - 1) + Secound;
	return path + Secound;
}

size_t  hex_to_dec(std::string s)
{
    std::stringstream ss;
    ss << std::hex << s;
    size_t result;
    ss >> result;
    if (ss.fail() || ss.bad())
        return -1;
    return result;
}

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

string::size_type commonPrefix(const string &s1, const string &s2) {
    string::size_type ret = 0;
	while (s1[ret] && s2[ret] && s1[ret] == s2[ret])
		ret++;
	return ret;
}

bool contest(const char _c, char &target, stringstream &ss) {
    return _c == target && !ss.eof();
}

string	clientmsg(socket_t idx, bool mode) {
    string msg;

    msg = "client [" + to_string(idx) + "]: " + " has finished sending the request\n";
    if (mode)
        msg = "client [" + to_string(idx) + "]: " + " has finished receiving the response\n";
    return msg;
}