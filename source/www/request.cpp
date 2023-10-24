# include "server-core.hpp"

const char *methods[] = { "GET", "POST", "DELETE", "UNKNOWN" };

void request::interpretRequest(stringstream &stream) {
    string buff;
    char   c;

    while (!stream.get(c).eof() and _stat & ~(REQUEST_PARSE_DONE | UNACCEPTABLE_REQUEST) )
    {
        buff.push_back(c);
        if (_stat & REQUEST_BODY) {
            int seek = stream.tellg();
			stream.seekg(seek - 1);
            _body.absorb_stream(stream);

            _stat = (_body._status & BODY_SUCCESSFUL) ? REQUEST_PARSE_DONE : _stat;
            _stat = (_body._status & UNACCEPTABLE_REQUEST) ? UNACCEPTABLE_REQUEST : _stat;

            return ;
        }
        if (_stat & REQUEST_SETUP and (buff == LF or buff == CR)) // begin empty line
            buff.clear();
        if (_stat & REQUEST_SETUP and c == '\n' and buff.length() > 1) 
            UpdateStatus(REQUEST_LINE);
        if (_stat & REQUEST_HEADER and c != '\n')
            continue;
        switch (_stat) {
            case REQUEST_LINE :
                parseReaquestLine(buff);
                buff.clear();
                break;
            case REQUEST_HEADER:
                parseHeader(buff);
                if (_body._status & BODY_SUCCESSFUL)
                    _stat = REQUEST_PARSE_DONE;
                buff.clear();
                break;
        }
    }
}

void request::parseHeader(string target) {

    string value, key;
    stringstream stream(target);

    if (target == CRLF or target == LF) {
        short _st = _method & (GET|DELETE) ? REQUEST_PARSE_DONE : REQUEST_BODY;

        if (_st & REQUEST_BODY) {
            _body.FindBodyStatus(this->_header);
            _type = _body._status & (MULTIPART_BODY | CHUNKED_BODY | LENGTH_BODY | BODY_SUCCESSFUL) ? _body._status : 0;
            if (_body._status & ~MULTIPART_BODY) {
                _body.bodyPath = "/tmp/.serveX__" + to_string(set_time()) + "__.upload";
                _body.bodycontent = s_open(_body.bodyPath);
            }
        }
        _isChunked = (!_header.get("Transfer-Encoding").empty());
        return UpdateStatus(_body._status & UNACCEPTABLE_REQUEST ? UNACCEPTABLE_REQUEST : _st);
    }
    getline(stream, key, ':');
    getline(stream, value, (char)0);
    trim(key, "\r\n \t");    
    trim(value, "\r\n \t");
    if (key.empty() or value.empty())
        return ;
    return _header.adding(key, value);
}

string request::normalization(const string &path, const char sep)
{
    deque<string> components;
    string        component;
    string        normPath = (path[0] == sep) ? "/" : "", buff;
    stringstream  stream(path);

    getline(stream, buff , sep);
    while (getline(stream, buff, sep))
    {
        string::size_type idx = buff.find_first_not_of(" \t\n\r\f\v");
        if (buff == "." or buff.empty() or idx == string::npos)
            continue;
        buff = buff.substr(idx);
        if (buff == "..")
            components.empty() ? throw UNACCEPTABLE_REQUEST : components.pop_back();
        else
            components.push_back(buff);
    }
    deque<string>::iterator it = components.begin();
    while (it != components.end())
        normPath.append(it != components.begin() ? "/" : ""), normPath.append(*it), it ++;
    transform(normPath.begin(), normPath.end(), normPath.begin(), ::tolower);
    if (path.length() and path[path.length() - 1]  == '/')
        normPath = joinPath(normPath);
    return (components.clear(), normPath);
}

void request::parseReaquestLine(string req_line)
{
    stringstream _stream(req_line);
    string method, url, httpV, extractPath;

    _stream >> method >> url >> httpV;
    try {
        string::size_type idx;
        idx = url.find_first_of('?');
        _query += (idx == string::npos) ? "" : url.substr(idx + 1);
        extractPath = url.substr(0, idx);
        _path = normalization(extractPath);
        if (url.size() > 2048 or httpV != HTTP_VERSION)
            throw (url.size() > 2048) ? HTTP_REQUEST_URI_TOO_LONG : HTTP_VERSION_NOT_SUPPORTED;        
        for (int i = 0; i < METHODS_LENGHT ; i++)
            if (methods[i] == method)
                _method = (METHODS)pow(2, i + 1);
        if (_method & UNKNOWN_MT)
            throw HTTP_METHOD_NOT_ALLOWED;

    }
    catch (int _st) {
        _httpCodeSatus  = _st;
        UpdateStatus(UNACCEPTABLE_REQUEST);
    }
    UpdateStatus(REQUEST_HEADER);
}

bool  request::TooLarge(const t_size &Maxbytes) {

    string contentlenght;
    contentlenght = _header.get("Content-Length");

    trim(contentlenght);
    if (contentlenght.empty() or !every(contentlenght.begin(), contentlenght.end(), ::isdigit))
        return false;
    const t_size resvbytes = stol(contentlenght);
    return resvbytes > Maxbytes;
}

void request::UpdateStatus(short _st)
{
    _stat = _st;
}



short request::_unacceptable_request_( void ) const {
    if (_httpCodeSatus)
        return _httpCodeSatus;
    if (_stat & (UNACCEPTABLE_REQUEST) )
        return  (_httpCodeSatus = _stat), true;
    return false;
}

bool request::_request_is_done_( void ) const {
     return  _stat & REQUEST_PARSE_DONE; 
}

short  request::_get_request_stat_( void ) const {
    return _stat;
}

short  request::_get_http_code_status_( void ) const {
    return _httpCodeSatus;
}

bool  request::_requestChunked_(void) const {
    return _isChunked;
}

bool request::likeness(short _st) const {
    return _stat & _st;
}

bool request::likeness_(short _st) const{
    return _type & _st;
}

size_t request::Uploaded(void) const {
    return _body._multipart.size();
}

void request::reset() {

    _stat = REQUEST_SETUP;
    _httpCodeSatus = 0;
    _method = UNKNOWN_MT;
    _type = 0;
    _isChunked = false;
    _path  = "";
    _query = "" ;
    _header.clear();
    _body.reset();   

}