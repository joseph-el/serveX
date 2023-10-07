# include "request.hpp"

pair<bool, string> extractBoundary(string &line)
{
    // Content-Type: multipart/form-data; boundary=---------------------------1234567890
    stringstream ss(line);
    string multipartSting, boundary_;
    ss >> multipartSting >> boundary_;

    if (boundary_.empty())
        return make_pair(false, "");
    string::size_type idx;
    idx = boundary_.find_first_of('=');
    if (idx == string::npos)
        return make_pair(false, "");
    boundary_ = boundary_.substr(idx + 1);
    if (!boundary_.empty()) {
        boundary_ = "--" + boundary_;
    }
    // cout << "boundary :|" << boundary_  << "|" << endl;

    return make_pair(boundary_.empty() ? false : true, boundary_);
}

void request::interpretRequest(stringstream &stream)
{
    string buff;
    char c;
    while (!stream.get(c).eof() and _status & ~REQUEST_PARSE_DONE)
    {
        buff.push_back(c);
        if (_status & REQUEST_BODY) {
            int seek = stream.tellg();
			stream.seekg(seek - 1);
            _body.absorb_stream(stream);
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
            _body.open();
            _body.FindBodyStatus(this->_header);
            _body._multipartStatus =  (MULTIPART_BEGIN | MLT_BOUNDARY);
        }
        _st = _body._status & RUNTIME_ERROR ? RUNTIME_ERROR : _st;
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

const char *methods[] = { "GET", "POST", "DELETE", "UNKNOWN" };

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

bool Body::UpdateStatus(short _st) const
{
    if (_st & BODY_STATUS)
        return  _status = _st & ~BODY_STATUS, true;
    return _multipartStatus = _st & ~MULTIPART_STATUS, true;
}

int    ft_ftruncate(FILE *file)  {

    fseek(file, 0, SEEK_END);

    long size = ftell(file);
    if (size >= 2) {
        return ftruncate(fileno(file), size - 2);
    }
    return -1;
}

int    ShapeFile::write(stringstream &__DATA_TO_WRITE__) {
        // cout << "data to write : " << endl << __DATA_TO_WRITE__ << endl;
	fwrite(__DATA_TO_WRITE__.str().c_str(), 1, __DATA_TO_WRITE__.str().size(), file);
	__DATA_TO_WRITE__.clear();
	__DATA_TO_WRITE__.str("");
    return fflush(file);
}

void   ShapeFile::open(string &_FILE_PATH) {
    // cout << "check files : " << endl;
    file = fopen(_FILE_PATH.c_str(), "w+");
    if (!file)
        throw BODY_ERROR;
}

void   Body::FindBodyStatus( Header &_header ) {
    string line;
    string buff;

    if (!(line = _header.get("Content-Length")).empty()) {
		trim(line);
	    if (line.length() > 0 and (line[0] >= '1' and line[0] <= '9') and every(line.begin(), line.end(), ::isdigit))
			contentLength = atoi(line.c_str());
	}
    line = _header.get("Content-Type"), trim(line);
    if ( line.find( MimeTypes(line) ) )
       return (void)UpdateStatus(BINARY_BODY | BODY_STATUS);
    if (line.find(MULTIPART_STRING) != string::npos) {
        boundary = extractBoundary(line);
        return (void)UpdateStatus(!boundary.first ? (BODY_STATUS | BODY_ERROR) : (BODY_STATUS | MULTIPART_BODY) );
    }
    line = _header.get("Transfer-Encoding");
    for (stringstream ss(line); !ss.eof() and !line.empty(); getline(ss, buff, ',')) {
        trim(buff);
        if (identicalStrings(buff, "chunked"))
            return (void)UpdateStatus(CHUNKED_BODY | BODY_STATUS);
    }
    if (contentLength > 0)
         UpdateStatus(LENGTH_BODY | BODY_STATUS);
    else
        UpdateStatus(BODY_SUCCESSFUL | BODY_STATUS);
}

void   Body::lengthedBody(stringstream &stream) {

	char buff[(1 << 10)] = {0};
	stream.read(buff, contentLength - content);
	content += stream.gcount();
	fwrite(buff, 1, stream.gcount(), bodycontent);
	if (contentLength == content)
		 _status |= BODY_DONE;
}

void   Body::absorbHeaders(string &_buff, short &gl_mode)
{
    string buff;
    string _s1, name, filename;

    if (_buff == CRLF) 
        goto _setup;
    else if (_buff != CRLF or _buff != LF) {
        stringstream ss(_buff);
        string       value, key;
        getline(ss, key, ':');
        getline(ss, value , (char)0);
        _buff.clear();
        return _multipart[_idx]._header.adding(key, value);
    }
    _setup :
        buff = _multipart[_idx]._header.get("Content-Disposition");
        string::size_type idx = buff.find("name=\"");
        buff = buff.substr(idx + 6);
        idx = (buff.find("\"; ") == string::npos) ? buff.find("\"") : buff.find("\"; ");
        name = buff.substr(0, idx);
        idx = buff.find("filename=\"");
        if (idx != string::npos) { 
            buff = buff.substr(idx + 10);
            filename = buff.substr(0, buff.find_last_of('\"'));
        }
        _multipart[_idx].name = name;
        _multipart[_idx]._filename = filename;
        string tmp = "/tmp/.server__" + to_string(time()) + "__.server";
        if (!filename.empty())
            tmp = "/tmp/" + filename;
        _multipart[_idx]._openedFILE = tmp;
        _multipart[_idx].open(tmp);
        UpdateStatus (MULTIPART_STATUS | MLT_HEADER_DONE | MLT_CONTENT | MULTIPART_BEGIN);
}

void   Body::absorb_stream(stringstream &stream)
{
    // cout << "iam here " << endl;
    switch (_status) {
        case MULTIPART_BODY:
            // cout << "the stream : \n" << stream.str() << endl;

            multipartBody(stream);
            break;
        case CHUNKED_BODY:
            // chunkedBody(stream);
            break;
        case LENGTH_BODY:
            // lengthedBody(stream);
            break;
        case BINARY_BODY:
            // binaryBody(stream);
            break;
    }
    // if (stream.eof())
    //     cout << "the stream return empty " << endl;

    if (_multipartStatus & MULTIPART_DONE) {
    //     map<short, ShapeFile>::iterator it = _multipart.begin();
    //     while (it != _multipart.end()) {
    //         cout << "filename of <" << it->first << "> : " << it->second._filename << endl;
    //         cout << "name of <" << it->first << "> : " << it->second.name << endl;
    //         cout << "opendfile of <" << it->first << "> :" << it->second._openedFILE << endl;
    //         cout << endl << endl;
    //         it ++;
    //     }
        // rename(_multipart[_idx]._openedFILE.c_str(), "/tmp/new.png");
        cout << "multipart done 👏🏻" << endl;
        exit(0);
    }
    else  {
        // _multipart[_idx]._header.Disp();
        // cout << "the request is done by nothing " << endl;
    }
}

int absorbCRLF(stringstream &ss) {
    static string::size_type idx = 0;
    int                      seek = ss.tellg();
    char                     _c;

    while (!ss.eof() and idx < 2) {
		ss.get(_c);
		if (CRLF[idx] != _c && !ss.eof()) 
			return idx = 0, ss.seekg(seek), CRLF_NO;
		if (!ss.eof())
			idx++;
	}
    if (idx == 2)
        return idx = 0, CRLF_OK;
    return CRLF_WAIT;
}

int Body::absorbBoundary(stringstream &stream, stringstream &ss) {

    static string::size_type idx = 0;
    streampos                seek;
    string                   buff;
    char                     _c;

    while (!stream.eof() && idx < boundary.second.length()) {
        stream.get(_c);
        (!stream.eof()) && (ss << _c);
        if (boundary.second[idx] != _c && !stream.eof())
            return idx = 0, BN_NO;
        if (!stream.eof())
            idx ++;
    }
    if (idx == boundary.second.length())
        return ss.clear(), ss.str(""), idx = 0, BN_OK;
    return BN_WAIT;
}

bool match(const char _c, char &target, stringstream &ss) {
    return _c == target && !ss.eof();
}

void Body::multipartBody(stringstream &stream)
{
    string       buff;
    short        _st;
    char         _c;

    while (!stream.eof() && _multipartStatus & ~MULTIPART_DONE) {
        if (_multipartStatus & MULTIPART_BEGIN) {
            _st = _multipartStatus & ~MULTIPART_BEGIN;
            switch (_st) {

                case MLT_BOUNDARY:
                    (absorbBoundary(stream, ss)) &&
                        UpdateStatus(MULTIPART_STATUS | MLT_CRLF | MULTIPART_BEGIN);
                    break;
                case MLT_CRLF:
                     (absorbCRLF(stream) == CRLF_OK) &&
                        (UpdateStatus(MULTIPART_STATUS | MLT_HEADERS | MULTIPART_BEGIN));
                    buff.clear();
                    break;
                case MLT_HEADERS:
                    stream.get(_c);
                    buff += _c;
                    if (buff.find(CRLF) != string::npos) 
                        absorbHeaders(buff, _st);
                    break;
            }
            if (_multipartStatus & MLT_HEADER_DONE)
                _multipartStatus &= ~(MULTIPART_BEGIN | MLT_HEADER_DONE);
        }  else if (_multipartStatus & MLT_CONTENT) {
            _st = absorbBoundary(stream, ss);
            switch (_st) {
                case BN_OK:
                    stream.get(_c);
                    if (match('-', _c, stream)) {
                        _multipartStatus = MULTIPART_DONE;
                        break;
                    } else {
                        int seek = stream.tellg();
                        stream.seekg(seek - 1);
                    }
                    _multipartStatus = (MULTIPART_BEGIN | MLT_CRLF);
                    ft_ftruncate(_multipart[_idx].file);
                    _idx ++;
                    ss.clear(), ss.str("");
                    break;

                case BN_END:
                    ft_ftruncate(_multipart[_idx].file);
                    _multipartStatus = MULTIPART_DONE;
                    ss.clear(), ss.str("");
                    break;

                case BN_NO:
                    _multipart[_idx].write(ss);
                    break;
            }
        }
    }
}


























