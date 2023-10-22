# include "server-core.hpp"

pair<bool, string> requestBody::extractBoundary(string &line) {
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
        boundary_ = BOUNDARY_BEGIN + boundary_;
    }
    return make_pair(boundary_.empty() ? false : true, boundary_);
}

void    requestBody::UpdateStatus(t_stat _st) const {
    _status = _st;
}

void    requestBody::FindBodyStatus( Header &_header ) {
    string line;
    string buff;
    stringstream ss;

    if (!(line = _header.get("Content-Length")).empty()) { // get Length 
		trim(line);
	    if (line.length() > 0 and (line[0] >= '1' and line[0] <= '9') and every(line.begin(), line.end(), ::isdigit))
			contentLength = atoi(line.c_str());
        if (!contentLength)
            goto other;
	}
    bodyType = _header.get("Content-Type"), trim(bodyType); // get like (text/plain) externsion
    if (bodyType.find(MULTIPART_STRING) != string::npos) { // emm check if the body as multiple part
        boundary = extractBoundary(bodyType);
        return UpdateStatus(!boundary.first ? UNACCEPTABLE_REQUEST:MULTIPART_BODY);
    }
    line = _header.get("Transfer-Encoding"); // check if chunked
    ss.clear(); ss << line;
    while (getline(ss, buff, ',')) {
        trim(buff);
        if (identicalStrings(buff, "chunked"))
            return UpdateStatus(CHUNKED_BODY);
    }
    other:
       if (contentLength > 0) // else the body  is just a lenghted body
           UpdateStatus(LENGTH_BODY);
       else
           UpdateStatus(BODY_SUCCESSFUL); // body done
}

void    requestBody::absorbHeaders(string &_buff) {
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
        try {
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
            string tmp = "/tmp/.serveX__" + to_string(set_time()) + "__.upload";    
            if (_multipart[_idx]._header.size() == 1) // i added this for setup key
                tmp = "/tmp/.serveX_" + to_string(set_time()) + "__.key", _multipart[_idx]._filename = "";
            _multipart[_idx]._openedFILE = tmp;
            _multipart[_idx].file = s_open(tmp);
            _multipartStatus = (MLT_HEADER_DONE | MLT_CONTENT | MULTIPART_BEGIN);
        } catch (...) {}
}

int     absorbCRL(stringstream &stream, stringstream &ss) {

    static string::size_type idx = 0;
    char                     _c;

    while (!stream.eof() and idx < 2) {
		stream.get(_c);
        (!stream.eof()) && (ss << _c);
		if (CRLF[idx] != _c && !stream.eof()) 
			return idx = 0,  CRLF_NO;
		if (!ss.eof())
			idx++;
	}
    if (idx == 2)
        return  ss.clear(), ss.str(""), idx = 0, CRLF_OK;
    return CRLF_WAIT;
}

int     requestBody::absorbBoundary(stringstream &stream, stringstream &ss) {

    static string::size_type idx = 0;
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

void    requestBody::multipartBody(stringstream &stream)
{
    string       buff;
    t_stat       _st;
    char         _c;


    while (!stream.eof() && _multipartStatus & ~MULTIPART_DONE) {
        
        if (_multipartStatus & MULTIPART_BEGIN) {

            _st = _multipartStatus & ~MULTIPART_BEGIN;
            switch (_st) {
                case MLT_BOUNDARY:
                    (absorbBoundary(stream, ss)) &&
                        (_multipartStatus = (MLT_CRLF | MULTIPART_BEGIN));
                    break;
                case MLT_CRLF:
                     (absorbCRL(stream, ss) == CRLF_OK) &&
                        (_multipartStatus = (MLT_HEADERS | MULTIPART_BEGIN));
                    buff.clear();
                    break;
                case MLT_HEADERS:
                    stream.get(_c);
                    buff += _c;
                    if (buff.find(CRLF) != string::npos) 
                        absorbHeaders(buff);
                    break;
            }
            if (_multipartStatus & MLT_HEADER_DONE)
                _multipartStatus &= ~(MULTIPART_BEGIN | MLT_HEADER_DONE);
        }  else if (_multipartStatus & MLT_CONTENT) {

            _st = absorbBoundary(stream, ss);
            switch (_st) {
                case BN_OK:
                    stream.get(_c); // check if stream is empty
                    if (contest('-', _c, stream)) {
                        _multipartStatus = MULTIPART_DONE;
                        return ;
                    } else {
                        int seek = stream.tellg();
                        stream.seekg(seek - 1);
                    }
                    _multipartStatus = (MULTIPART_BEGIN | MLT_CRLF);
                    ft_ftruncate(_multipart[_idx].file);
                    ss.clear(), ss.str(""), _idx ++;
                    break;
                case BN_NO:
                    s_write(_multipart[_idx].file, ss);
                    break;
            }
        
        }
    }
}

void    requestBody::lengthedBody(stringstream &stream) {

	char buff[MAX_BYTES_RECV] = {0};

    stream.read(buff, contentLength - content);
    content += stream.gcount();    
    fwrite(buff, 1, stream.gcount(), bodycontent);
    if (contentLength == content)
		UpdateStatus(BODY_SUCCESSFUL);
}

void    requestBody::absorb_stream(stringstream &stream)
{
    switch (_status) {

        case MULTIPART_BODY:
            
            multipartBody(stream);
            if (_multipartStatus & MULTIPART_DONE)
                UpdateStatus(BODY_SUCCESSFUL);

            break;
        
        case CHUNKED_BODY:
            chunkedBody(stream);
            break;
        
        case LENGTH_BODY:
            lengthedBody(stream);
            break;
    }
    
}

void    requestBody::chunkedBody(stringstream &stream) {
    try {
        if (_isHeader) {
            size_t f = stream.str().find("\r\n\r\n");
            if (f != string::npos) {
                stream.str(stream.str().substr(f + 4));
                chunk_size = hex_to_dec(stream.str());
                for (size_t x = 0; x < stream.str().length(); x++) {
                    if (x + 1 != stream.str().length() && stream.str().c_str()[x] == '\r' && stream.str().c_str()[x + 1] == '\n') {
                        stream.str(stream.str().substr(x + 2));
                        break;
                    }
                }
                _isHeader = false;
            }
        }
        if (!chunked_ok) {
            if (chunk_str.length() == 1 && chunk_str[0] == '\r')
                chunk_str.clear();
            chunk_str += stream.str().substr(0, stream.str().find("\r\n"));
            chunk_size = hex_to_dec(chunk_str);
            if (chunk_size == 0)
                return UpdateStatus(BODY_SUCCESSFUL);
            if (is_the_last_newline) {
                stream.str(stream.str().substr(1));
                is_the_last_newline = false;
            }
            else
                stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
            chunk_str.clear();
            chunked_ok = true;
        }
        if (!_isHeader && chunk_size < stream.str().length()) {
            std::stringstream tmp;
            tmp.str(stream.str().substr(0, chunk_size));
            s_write(bodycontent, tmp);
            stream.str(stream.str().substr(chunk_size));
            if (stream.str().length()) {
                if (stream.str().length() == 1) {
                    chunk_str += '\r';
                    stream.clear();
                    stream.str("");
                    chunked_ok = false;
                    return ;
                }
                stream.str(stream.str().substr(2));
                if (stream.str().find("\r\n") == std::string::npos) {
                    size_t pos = stream.str().find("\r");
                    if (pos != std::string::npos && pos < stream.str().length()) {
                        stream.str(stream.str().substr(0, pos));
                        is_the_last_newline = true;
                    }
                    chunk_str += stream.str();
                    stream.clear();
                    stream.str("");
                    chunked_ok = false;
                    return ;
                }
            }
            chunk_size = hex_to_dec(stream.str());
            if (chunk_size == 0)
                return UpdateStatus(BODY_SUCCESSFUL);
            if (stream.str().find("\r\n") != string::npos)
                stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
            else {
                chunked_ok = false;
                chunk_str = stream.str();
                return ;
            }
        }
        if (!_isHeader && chunk_size >= stream.str().length()) {
            chunk_size -= stream.str().length();
            s_write(bodycontent, stream);
        }
    }
    catch (...) {
        UpdateStatus(UNACCEPTABLE_REQUEST);
    }
}

void requestBody::closebodycontent() {
    if (bodycontent) {
        fclose(bodycontent);
        bodycontent = NULL;
    }
}

void requestBody::reset() {
    closebodycontent();
	_idx = 0;
    contentLength = 0;
    content = 0;
    _status = 0;
    ss.clear();
    ss.str("");
    _idx = 0;
    _multipartStatus = MULTIPART_BEGIN | MLT_BOUNDARY;
    map<short, ShapeFile>::iterator it = _multipart.begin();
    while (it != _multipart.end()) {
        it->second._header.clear();
        fclose(it->second.file);
        it++;
    }
    _multipart.clear();
}