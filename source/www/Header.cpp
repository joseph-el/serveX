# include "Header.hpp"

bool Header::Search(const string &key)
{
    return find(key) == end() ? false : true;
}

void Header::adding(string key, string value)
{
    (*this)[key] = value;
}

void Header::Disp()
{
    HeaderIt it = begin();

    cout << "disp headers : \n";

    for (; it != end(); it++)
        cout << it->first << " = " << it->second << endl;
    
    cout << "end Disp Header\n";
}

string Header::get(string key) {
    HeaderIt it = find(key);
    if (it == end()) {
        cerr << "NAME" << " : " << "Header not found !\n";
        return "";
    }
    return it->first;
}