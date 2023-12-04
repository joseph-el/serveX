# ifndef _MIME_TYPES_H_
# define _MIME_TYPES_H_

# include <iostream>
# include <string>
# include <map>

#define DEFAULT_TYPE "text/plain"

using namespace std;

class mimeTypes : public map< string, string >
{
    public :

        mimeTypes();
        mapped_type &GetMimeTypeFromExtension(string path) {
            string::size_type idx = path.find_last_of('.');
            if (idx == string::npos)
                return (*this)[""];
            string extension = path.substr(idx + 1);
            return (*this)[extension];
        }

        mapped_type &operator[](const key_type &key) {
            iterator it = find(key);
            if (it != end())
                return map<string, string>::operator[](key);
            return map<string, string>::operator[]("");
        }

        string operator()(const mapped_type &type) {
            iterator it = begin();
            while (it != end()) {
                if (it->second == type)
                    return it->first;
                it ++;
            }
            return "";
        }       
};

extern mimeTypes MimeTypes;

# endif
