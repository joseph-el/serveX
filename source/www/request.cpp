# include "request.hpp"

const char *methods[] = { "GET", "POST", "DELETE", "UNKNOWN" };

void request::interpretRequest(stringstream &stream)
{
    string buff;
    char   c;

    while (!stream.get(c).eof() and _status & ~REQUEST_PARSE_DONE)
    {
        buff.push_back(c);
        if (_status & REQUEST_BODY) {
            int seek = stream.tellg();
			stream.seekg(seek - 1);
            _body.absorb_stream(stream);
            if (_body._status & BODY_DONE)
                return (void)(_status = REQUEST_PARSE_DONE);
        }
        if (_status & REQUEST_SETUP and (buff == LF or buff == CR)) // begin empty line
            buff.clear();
        if (_status & REQUEST_SETUP and c == '\n' and buff.length() > 1) 
            UpdateStatus(REQUEST_LINE | REQUEST_STATUS);
        if (_status & REQUEST_HEADER and c != '\n')
            continue;
        switch (_status)
        {
            case REQUEST_LINE :
                parseReaquestLine(buff);
                buff.clear();
                break;
            case REQUEST_HEADER:
                parseHeader(buff);
                buff.clear();
                break;
        }
    }
}

void request::parseHeader(string target) {

    string value, key;
    stringstream stream(target);

    if (target == CRLF or target == LF) {
        short _st = _method & GET ? REQUEST_PARSE_DONE : REQUEST_BODY;
        if (_st & REQUEST_BODY) {
            _body.FindBodyStatus(this->_header);
            cerr << "check body status: " << _body._status << endl;
            if (_body._status & ~MULTIPART_BODY) {
                _body.bodyPath = "/tmp/.serveX__" + to_string(set_time()) + "__.upload";
                _body.bodycontent = s_open(_body.bodyPath);
            }
            _body.content = 0;
            _body._multipartStatus =  (MULTIPART_BEGIN | MLT_BOUNDARY);
        }
        return UpdateStatus(_st | REQUEST_STATUS);
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
        _path += normalization(extractPath);
        if (url.size() > 2048 or httpV != HTTP_VERSION)
            throw (url.size() > 2048) ? HTTP_REQUEST_URI_TOO_LONG : HTTP_VERSION_NOT_SUPPORTED;
        for (int i = 0; i < METHODS_LENGHT ; i++)
            if (methods[i] == method) 
                _method = (METHODS)pow(2, i + 1);
    }
    catch (int _st) {
        UpdateStatus(_st | HTTP_STATUS);
    }
    UpdateStatus(REQUEST_HEADER | REQUEST_STATUS);
}

void request::UpdateStatus(short _st)
{
    if (_st & HTTP_STATUS)
        _httpStatus = _st & ~HTTP_STATUS;
    else
        _status = _st & ~REQUEST_STATUS;
}




























