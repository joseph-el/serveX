# include "request.hpp"

HeaderIt Header::find(const string &key)
{
    HeaderIt it = begin();

    for (; it != end(); it++)
        if (it->first == key)
            return it;
    return it;
}

void Header::adding(string key, string value)
{
    insert( make_pair(key, value) );
}

void Header::Disp()
{
    HeaderIt it = begin();

    cout << "disp headers : \n";
    for (; it != end();it++)
        cout << it->first << " = " << it->second << endl;
    cout << "end Disp Header\n";
}

string Header::get(string key) {
    HeaderIt it = find(key);
    if (it == end()) {
        cerr << NAME << " : " << "Header not found !\n";
        return "";
    }
    return it->first;
}