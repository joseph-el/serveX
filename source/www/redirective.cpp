# include "server-core.hpp"

bool Redirect::redirectStatus(const int &_st) {
    
    return   _st == HTTP_FOUND             or \
             _st == HTTP_USE_PROXY         or \
             _st == HTTP_SEE_OTHER         or \
             _st == HTTP_NOT_MODIFIED      or \
             _st == HTTP_MULTIPLE_CHOICES  or \
             _st == HTTP_MOVED_PERMANENTLY or \
             _st == HTTP_TEMPORARY_REDIRECT; 
}


Redirect::Redirect(const string &path, const int _CodeStatus, bool local ) {
    _host = "";
    _path = path;
    _redirect_Code_Status = _CodeStatus;
    _redirect = redirectStatus(_CodeStatus);
    _local = local;
}

void Redirect::_make_redirect_(server_data *_vts) {
    if (!_redirect)
        return ;

    string host = _vts->getHost();
    int port = _vts->getListenPort();
    _host = "http://" + _host + ":" + to_string(port);
    if (_path.length() and _path[0] != '/' and !_local)
        _host = joinPath(_host, _path);
    else {
        // _path = "http://" + _path;
        _host = _path;
    }
}