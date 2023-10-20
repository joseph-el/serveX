# include "server-core.hpp"

bool Header::Search(const string &key) {
    return find(key) == end() ? false : true;
}

void Header::adding(string key, string value) {
    (*this)[key] = value;
}

void Header::Disp()
{
    HeaderIt it = begin();

    cout << "----------HEADERS----------" << endl;

    for (; it != end(); it++)
        cout << it->first << " = " << it->second << endl;
    
    cout << "------------END----------" << endl;
} 

string Header::get(string key) {

    HeaderIt it = find(key);
    if (it == end()) {
        // cerr << "Webserv: " << key + ": " << "Header not found !\n";
        return "";
    }
    return it->second;
}