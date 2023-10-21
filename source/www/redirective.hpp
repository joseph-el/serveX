# ifndef __REDIRECTIVE_H__
# define __REDIRECTIVE_H__

# include "server-core.hpp"

class  Redirect {
    private:
        string _host;
        string _path;
        int    _redirect_Code_Status;
        bool   _redirect;
        bool   _local;

    public :
        bool  isRedirectStatus(void) const {
            return _redirect;
        }
        string _getRedirectHost(void) const {
            return _host;
        }
        int getRedirectStatus(void) const {
            return _redirect_Code_Status;
        }
        Redirect(const  string &, const int _CodeStatus = 301, bool local = true);

        void _make_redirect_(server_data *);
        bool redirectStatus(const int &_st);

        Redirect &operator=(const Redirect &other)  {
            if (this != &other) {
                _host = other._host;
                _path = other._path;
                _redirect_Code_Status = other._redirect_Code_Status;
                _redirect = other._redirect;
                _local = other._local;
            }
            return *this;
        }

        Redirect(const Redirect &other) {
            *this = other;
        }

};

# endif