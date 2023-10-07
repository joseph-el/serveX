# include "requestBody.hpp"
#include <cstdlib>
#include <sstream>

pair<bool, string> requestBody::extractBoundary(string &line)
{
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

bool    requestBody::UpdateStatus(short _st) const
{
    if (_st & BODY_STATUS)
        return  _status = _st & ~BODY_STATUS, true;
    return _multipartStatus = _st & ~MULTIPART_STATUS, true;
}

void    requestBody::FindBodyStatus( Header &_header ) {
    string line;
    string buff;

    if (!(line = _header.get("Content-Length")).empty()) { // get Length 
		trim(line);
	    if (line.length() > 0 and (line[0] >= '1' and line[0] <= '9') and every(line.begin(), line.end(), ::isdigit))
			contentLength = atoi(line.c_str());
	}
    bodyType = _header.get("Content-Type"), trim(bodyType); // get like (text/plain) externsion
    if (bodyType.find(MULTIPART_STRING) != string::npos) { // emm check if the body as multiple part
        boundary = extractBoundary(bodyType);
        return (void)UpdateStatus(!boundary.first ? (BODY_STATUS | BODY_ERROR) : (BODY_STATUS | MULTIPART_BODY) );
    }
    line = _header.get("Transfer-Encoding"); // check if chunked
    stringstream ss(line);
    while (getline(ss, buff, ',')) {
        trim(buff);
        if (identicalStrings(buff, "chunked"))
            return (void)UpdateStatus(CHUNKED_BODY | BODY_STATUS);
    }
    if ( !MimeTypes(bodyType).empty()) // check if the extension found at mimeTypes for rename it after 😎
       _isBinary = true;
    if (contentLength > 0) // else the body  is just a lenghted body
         UpdateStatus(LENGTH_BODY | BODY_STATUS);
    else
        UpdateStatus(BODY_SUCCESSFUL | BODY_STATUS); // body done
}

void    requestBody::absorbHeaders(string &_buff)
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
        string tmp = "/tmp/.serveX__" + to_string(set_time()) + "__.upload";
        if (!filename.empty())
            tmp = "/tmp/" + filename; // just for test
        _multipart[_idx]._openedFILE = tmp;
        _multipart[_idx].file = s_open(tmp);
        UpdateStatus (MULTIPART_STATUS | MLT_HEADER_DONE | MLT_CONTENT | MULTIPART_BEGIN);
}

int     requestBody::absorbCRLF(stringstream &ss) {

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
                        absorbHeaders(buff);
                    break;
            }
            if (_multipartStatus & MLT_HEADER_DONE)
                _multipartStatus &= ~(MULTIPART_BEGIN | MLT_HEADER_DONE);
        }  else if (_multipartStatus & MLT_CONTENT) {
            _st = absorbBoundary(stream, ss);
            switch (_st) {
                case BN_OK:
                    stream.get(_c); // TODO: check if stream is empty
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

    stringstream ss;
	char         buff[(1 << 10)] = {0};

    stream.read(buff, contentLength - content);
    content += stream.gcount();    
    ss << buff;
    s_write(bodycontent, ss);
    if (contentLength == content) 
		UpdateStatus(BODY_STATUS | BODY_DONE);
}

void    requestBody::absorb_stream(stringstream &stream)
{
    // cout << "check status: " << _status << endl;
    switch (_status) {

        case MULTIPART_BODY:

            multipartBody(stream);
            if (_multipartStatus & MULTIPART_DONE)
                UpdateStatus(BODY_STATUS | BODY_DONE);
            break;
        
        case CHUNKED_BODY:
            chunkedBody(stream);

            cout << "waiting for tnaceur" << endl;
            exit(EXIT_FAILURE);

            break;
        case LENGTH_BODY:
            lengthedBody(stream);
            break;
    
    }
}



// ===========================================================================================================================================================================



void    requestBody::chunkedBody(stringstream &stream) {


    stringstream ss;

    string jj = "HELLE DJEJDEJDEKDNKASNKDASKJDASKASJKJKDSAN DAKJDJKNDJKFJD ";
    ss << jj;


    s_write(bodycontent, ss);

    cout << "chunkedBody" << endl;
    
    exit(4);


} 
