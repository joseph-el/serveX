# include "server-core.hpp"

short response::absorbSatus(string &path) {
    struct stat _file;
    bool  _cgi = false;

    path = REQ._path;
    if (_vts->ServerIsRedirective())
        return (1 << 1);
    if (!_location)
        return (1 << 3);
    if (LOCATION.LocationIsRedirective())
        return (1 << 2);
    if (LOCATION.NotallowMethod(REQ._method)) 
        return (1 << 4);
    if (REQ.TooLarge(_vts->getMaxBodySize()))
        return (1 << 10);

    _cgi = (!LOCATION.getCgiPath().empty());

    if (LOCATION.getIsUpload() && REQ._method & POST && !_cgi)
        return (1 << 8);

    path = LOCATION.getRoot() +  path ;

    path = REQ.normalization(path); // norm path

    bzero(&_file, sizeof _file);
    if (stat(path.c_str(), &_file) != EXIT_SUCCESS)
        return (1 << 6); 

    if (S_ISDIR(_file.st_mode)) // check if the path is directory
        return  (1 << 7) | (_cgi ? (1 << 9) : 0); // append to cgi
    if (S_ISREG(_file.st_mode))
        return (1 << 5) | (_cgi ? (1 << 9) : 0);
    return 0;
}

void response::interpret_response(socket_t &fd) {

    string requestPATH;
    short  _st = INIT_SWITCH_STATUS;
    if (_stat & RESPONSE_INIT && REQ._unacceptable_request_()) {
        ErrPage(REQ._get_http_code_status_(), VTS.getErrorPages());
        goto  sendResponse;
    }
    (_stat & RESPONSE_INIT) && (_st = absorbSatus(requestPATH));

    switch (_st) {
        case LOCATION_UPLOAD      : Upload;
            goto sendResponse;
        case PATH_NOT_FOUND       : ErrPage(HTTP_NOT_FOUND, VTS.getErrorPages()); 
            goto sendResponse;
        case METHOD_NOT_ALLOW     : ErrPage(HTTP_METHOD_NOT_ALLOWED, VTS.getErrorPages());
             goto sendResponse;
        case LOCATION_NOT_FOUND   : ErrPage(LOCATION_NOT_FOUND, VTS.getErrorPages()); 
            goto sendResponse;
        case RECV_BYTES_TOO_LARGE : ErrPage(HTTP_REQUEST_ENTITY_TOO_LARGE, VTS.getErrorPages());
            goto sendResponse;
        case REDIRECTIVE_SERVER   : NewUrl(VTS.getServerRedirection() );
            goto sendResponse;
        case REDIRECTIVE_LOCATION : NewUrl(LCT.getlocationRedirections());
            goto sendResponse;
        case (PATH_IS_DIRECTORY | LOCATION_CGI):
            goto handelDirectory;
        case (NORMAL_FILE_PATH | LOCATION_CGI):
            goto  handelFiles;
        case PATH_IS_DIRECTORY : {
            handelDirectory:
                string::size_type idx = REQ._path.length();
                if (REQ._path.length() > 0 && REQ._path[idx - 1] != '/') {
                    pair<int, string> redirect;
                    redirect.first = HTTP_MOVED_PERMANENTLY;
                    redirect.second = joinPath(REQ._path);
                    _setup_redirective_(&redirect, false);
                    goto sendResponse;
                }
                v_t it = LOCATION.getIndexes().begin();
                string FILE_PATH;
                while (it != LOCATION.getIndexes().end()) {
                    FILE_PATH = joinPath(requestPATH, *it) ;
                    if (access(FILE_PATH.c_str(), F_OK) == 0) {
                        if (REQ._method & DELETE)
                            goto deleteFILE;
                        else if (_st & LOCATION_CGI && cgiExtension.FindFileByExtension(FILE_PATH)) {
                            RunCgi(FILE_PATH);
                            goto setupCgi;
                        }
                        file = new ifstream(FILE_PATH, ios::in);
                        if (!file or !file->is_open() or !file->good())
                            goto FileNotGood;
                        _setup_lenghted_type_(FILE_PATH, REQ._requestChunked_());
                        goto sendResponse;
                    }
                    it ++;
                }
                if (LOCATION.getAutoIndex() && REQ._method & GET) {
                    _build_directory_listing_(requestPATH);
                    goto sendResponse;
                }
                deleteFILE:
                    if (REQ._method & DELETE) {
                        revokeItem(FILE_PATH, (it == LOCATION.getIndexes().end()));
                        goto sendResponse;
                    }
            errno = ENOENT;
            goto FileNotGood;
        }
        case NORMAL_FILE_PATH: {
            handelFiles:

                if (access(requestPATH.c_str(), F_OK) == 0) {
                    if (REQ._method & DELETE) {
                        revokeItem(requestPATH, false);
                        goto sendResponse;
                    }  else if (_st & LOCATION_CGI && cgiExtension.FindFileByExtension(requestPATH)) {
                        RunCgi(requestPATH); // setup time
                        goto setupCgi;
                    }
                    file = new ifstream(requestPATH, ios::in);
                    if (!file or !file->is_open() or !file->good() )
                        goto FileNotGood;
                    _setup_lenghted_type_(requestPATH, REQ._requestChunked_());
                    goto sendResponse;
                } else {
                    FileNotGood:
                        if (file)
                            (delete file, file = 0x0);
                        ErrPage(errno & ENOENT ? HTTP_NOT_FOUND : HTTP_FORBIDDEN, VTS.getErrorPages());
                        goto sendResponse;
                }
            }
    }
    setupCgi:
        cgi_supervisor();
    sendResponse:
        _send(fd);

}

bool response::cgi_stderr() {
    off_t fileSize;
    fileSize = lseek(_fdCgi[CGI_ERR], 0, SEEK_END);
    if (fileSize) {
        lseek(_fdCgi[CGI_ERR], 0, SEEK_SET);
        ErrCgi("Cgi script syntax error");
        return false;
    }
    return true;
}

void response::cgi_supervisor() {

    if (_cgi == -1 || _stat & RESPONSE_CGI_BODY)
        return ;
    switch (WaitCgi(_cgi, _time)) {
        case CGI_WAITING:
            break;
    
        case CGI_TIMEOUT:
             closefiles(_fdCgi);
            _setup_error_pages(504, VTS.getErrorPages());
            break;

        case CGI_SUCCESS:
            if (!_build_cgi_body() || !cgi_stderr())
                return closefiles(_fdCgi) ;
            _set_stat_(RESPONSE_CGI_BODY | RESPONSE_HEADERS);
        break;
    }
}

long long response::found(string const& _Body, string const& toSearch) {
    string headerValue;
    size_t found;

    found = _Body.find(toSearch);
    if (found != string::npos) {
        size_t end = _Body.find("\r\n", found);
        if (end != string::npos) {
            string headerLine = _Body.substr(found, end - found);
            size_t pos = headerLine.find(":");
            if (pos != string::npos) {
                headerValue = headerLine.substr(pos + 2);
                trim(headerValue);
                if (headerValue.empty() && toSearch == "Content-Type") {
                    _headers.adding("Content-Type", MimeTypes["html"]);
                    return 0;
                }
            } else
                return -1;

        } else 
            return -1;
    } else {
        if (toSearch == "Content-Type")
              return _headers.adding("Content-Type", MimeTypes["html"]), 0;
        return -1;
    }
    if (toSearch == "Content-Lenght") 
        return every(headerValue.begin(), headerValue.end(), ::isdigit) ? atoi(headerValue.c_str()) : -2;
    return EXIT_SUCCESS;
}



bool response::_build_cgi_body() {

    ssize_t   nbyte;
    off_t     filesize;
    long long lenghtSize;
    
    _set_http_code_status_(HTTP_OK);
    _set_connection_(false);
    _init_headers_();

    lseek(*_fdCgi, 0, SEEK_SET);
    filesize = lseek(*_fdCgi, 0, SEEK_END);
    lseek(*_fdCgi, 0, SEEK_SET);

    char *buff = new char[filesize];
    nbyte = read(*_fdCgi, buff, filesize);
    if (nbyte == -1) {
        ErrCgi("Cgi Headers missing !");
        return  ( delete[] buff, false);
    }
    string content(buff, nbyte);
    delete[] buff;

    lenghtSize = found(content, "Content-Lenght");
    lenghtSize = (lenghtSize == -1) ? filesize : lenghtSize;
    found(content, "Content-Type");
    if (lenghtSize == -2 || lenghtSize > (LLONG_MAX - (1 << 0xA)) || lenghtSize > filesize) {
        ErrCgi("unvalid headers syntax");
        return false;
    }
    ftruncate(*_fdCgi, lenghtSize);
    lseek(*_fdCgi, 0, SEEK_SET);
    return true;
}

void response::_build_upload_response_page() {

    string      locationUpload;
    string      UploadPath;
    bool        findUploadPath = false;
    struct stat fileStat;

    _build_alert_user_messages_(N_INIT);
    bzero(&fileStat, sizeof fileStat);

    locationUpload = _location->getUploadPath();
    if (stat(locationUpload.c_str(), &fileStat) == 0) {
        if (S_ISDIR(fileStat.st_mode)) {
            UploadPath = locationUpload;
            findUploadPath = true;
        } else if (S_ISREG(fileStat.st_mode))
            goto undefinedUploadPath;
    }
    else  {
        undefinedUploadPath:
            findUploadPath = false;
            UploadPath = "/tmp";
    }
    if (REQ.likeness_(CHUNKED_BODY | LENGTH_BODY | BODY_SUCCESSFUL)) 
        _setup_normal_upload_(UploadPath, findUploadPath);
    else if (REQ.likeness_(MULTIPART_BODY)) 
        _setup_multipart_upload_(UploadPath, findUploadPath); 
    else 
         _build_alert_user_messages_(N_DONE);
    
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
}

void response::_build_response_page_(const int &_http_status, const string &msg) { // Just for build Error pages
    ifstream       css(string(SERVER_PATH) + "/dist/serverX-default-errors.html");
    string         cssCode;

    _pages << "<meta charset=\"UTF-8\"><div class=\"container\"><div class=\"error\"><h1>" << _http_status << "</h1><h2>error</h2><p>" << (msg.empty() ? WebStatusMap[_http_status] : msg) <<
              "</p><p class=\"subtitle\">Looks like you're lost</p>";
    getline(css, cssCode, (char)0);
    (_pages) << cssCode;
}

void response::_build_alert_user_messages_(short _mode, const string &msg) {
    if (_mode & N_INIT) {
        ifstream csspath(string(SERVER_PATH) + "/dist/alert_user_message.html");
        string css;
        getline(csspath, css, (char)0);
        _pages << css;
    }
    if (_mode & N_DONE) {
        _pages <<  "      <div class=\"col-sm-12\">\n        <div class=\"alert fade alert-simple alert-success alert-dismissible text-left"
                   " font__family-montserrat font__size-16 font__weight-light brk-library-rendered rendered show\">\n"
                   "          <button type=\"button\" class=\"close font__size-18\" data-dismiss=\"alert\">\n            <span aria-hidden=\"true\"><a>\n"
                   "              <i class=\"fa fa-times greencross\"></i>\n              </a></span>\n            <span class=\"sr-only\">Close</span>\n"
                   "          </button>\n          <i class=\"start-icon far fa-check-circle faa-tada animated\"></i>\n          <strong class=\"font__weight-semibold"
                   "\">Well done! </strong>" << (msg.empty() ? "You successfullyread this important." : msg) << "\n        </div>\n      </div>";

    } else if (_mode & N_WARNING) {

        _pages <<  "      <div class=\"col-sm-12\"><div class=\"alert fade alert-simple alert-warning alert-dismissible text-left font__family-montserrat font__size-16"
                   " font__weight-light brk-library-rendered rendered show\" role=\"alert\" data-brk-library=\"component__alert\"><button type=\"button\" class=\"close "
                   "font__size-18\" data-dismiss=\"alert\"><span aria-hidden=\"true\"><i class=\"fa fa-times warning\"></i></span><span class=\"sr-only\">Close</span></button><i "
                   "class=\"start-icon fa fa-exclamation-triangle faa-flash animated\"></i><strong class=\"font__weight-semibold\">Warning! </strong>" << \
                   (msg.empty() ? "Better check yourself, you're not looking too good." : msg) << "</div></div>";
                   
    } else if (_mode & N_FAILED) {

        _pages <<  "      <div class=\"col-sm-12\"><div class=\"alert fade alert-simple alert-danger alert-dismissible text-left font__family-montserrat font__size-16"
                   " font__weight-light brk-library-rendered rendered show\" role=\"alert\" data-brk-library=\"component__alert\"><button type=\"button\" class=\"close font__size-18"
                   "\" data-dismiss=\"alert\"><span aria-hidden=\"true\"><i class=\"fa fa-times danger \"></i></span><span class=\"sr-only\">Close </span></button><i class=\"start-icon"
                   " far fa-times-circle faa-pulse animated\"></i><strong class=\"font__weight-semibold\">Oh snap!</strong> " << \
                   (msg.empty() ? "Change a few things up and try submitting again." : msg) << "</div></div>";
    }
}

void response::_build_uploading_page_(__unused size_t uploaded_data) {
    string css;

    // waiting to add uploading data;
    ifstream cssPaht(string(SERVER_PATH) + "/dist/serveX-uploading.html");
    getline(cssPaht, css, (char)0);
    _pages << css;
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
}

void response::_buid_redirective_page_(const int &_http_status, const string &msg) {
    _pages <<  "<html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\""
               "width=device-width, initial-scale=1.0\"><title>" << _http_status << "</title><link rel=\"stylesheet\" href=\"https://error-pages.fabian.lol/assets/css/style.min.css\""
               "><link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.15.4/css/all.css\" integrity=\"sha384-DyZ88mC6Up2uqS4h/KRgHuoeGwBcD4Ng9SiP4dIRy0EXTlnuz47vAwmeGwVChigm\""
               " crossorigin=\"anonymous\"></head><body><div class=\"container\"><h1><span class=\"text\"> " << _http_status << " </span><span class=\"normal\"> " << WebStatusMap[_http_status] << " </span></h1><p><script>document.write"
               "(window.location.hostname)</script>&nbsp;" << (msg.empty() ? WebStatusMap[_http_status] : msg) << "</p><a onclick=\"window.history.back();\" class=\""
               "btn-big btn-primary\"><i class=\"fas fa-hand-point-left\"></i> go back</a></div><script src=\"https://error-pages.fabian.lol/assets/js/app.min.js\"></script></body></html>";
    _headers.adding("Content-Type", MimeTypes["html"]);
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
}

void response::_build_directory_listing_(const string& _path) {
    DIR *dir;
    struct dirent *ent;
    struct stat fileStat;
    stringstream tmp;

    _set_http_code_status_(HTTP_OK);
    _set_connection_(true);
    _init_headers_();


    if ((dir = opendir (_path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string path = _path;
            path += ent->d_name;
            if (stat(path.c_str(), &fileStat) < 0) {
                continue;
            }

            if (S_ISREG(fileStat.st_mode)) {
                tmp << "        <li style=\"list-style-type: symbolss;\"><a href=\"" << ent->d_name << "\">" << ent->d_name << "</a></li>\r\n";
            } else if (S_ISDIR(fileStat.st_mode)) {
                tmp << "        <li style=\"list-style-type: symbols;\"><a href=\"" << string(ent->d_name).append("/") << "\">" << ent->d_name << "/" << "</a></li>\r\n";
            }
        }
        closedir (dir);
        tmp << "    </ul>\r\n"
               "</div>\r\n"
               "</body>\r\n"
               "</html>";
    }
    _pages << string(AUTOINDEX_PAGE) + tmp.str();
    _headers.adding("Content-Type", MimeTypes["html"]);
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
    _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
}



void response::_setup_cgi_response_(const string &path) {

    if (access(path.c_str(), F_OK | R_OK) != 0) {
        ErrPage(HTTP_FORBIDDEN, VTS.getErrorPages());
        return;
    }
    cgi cgiHandler(*_vts, *_location, path);
    _time = time(NULL);
    if (!cgiHandler.executeCgi(*req)) {
         closefiles(_fdCgi);
        _setup_error_pages(HTTP_INTERNAL_SERVER_ERROR, NULL, cgiHandler.errorMsg);
        _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
        return;
    }
    _fdCgi[CGI_OUT] = cgiHandler.outputCGIFile;
    _fdCgi[CGI_ERR] = cgiHandler.stderrCGIFile;
    _cgi = cgiHandler._pid;
    _set_stat_(RESPONSE_BODY);
}

void response::_setup_response_message_() {
    map<string, string>::iterator it;

    _stream.clear(), _stream.str("");
    _stream << HTTP_VERSION << " " <<  _httpCodeSatus << " " << WebStatusMap[_httpCodeSatus] << CRLF;
    it = _headers.begin();
    while (it != _headers.end()) {
        _stream << it->first << ": " << it->second << CRLF;
        it++;
    }
    if (_cgi == -1)
        _stream << CRLF;
    _headers.clear();
}

void response::_setup_multipart_upload_(const string &UploadPath, bool findUploadPath) {
    bool        status = false;
    string      msgSatus;

    map<short, ShapeFile>* uploadFiles = &(*req)._body._multipart;
    map<short, ShapeFile>::iterator it = uploadFiles->begin();
    ShapeFile* ret                     = __null;

    while (it != uploadFiles->end()) {

        ret = &it->second;
        string oldPath, newPath;
        if(!ret->_filename.empty()) {
            oldPath = ret->_openedFILE;
            newPath = joinPath(UploadPath, ret->_filename);
            if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
                msgSatus = " " + ret->_filename +  " has been uploaded successfully " + (!findUploadPath ? "but in /tmp" : "");
                _build_alert_user_messages_(findUploadPath ? N_DONE : N_WARNING , " " + msgSatus);
            } else {
                msgSatus = " an error during upload " + ret->_filename + " " + strerror(errno);
                _build_alert_user_messages_(N_FAILED, " " + msgSatus);              
            }
        } else if (!ret->name .empty() && ret->_header.size() == 1) {
             oldPath = ret->_openedFILE;
             newPath = joinPath(UploadPath, ret->name + ".key");
             msgSatus = " " + ret->name;
             status = (rename(oldPath.c_str(), newPath.c_str()) == 0);
             msgSatus += status ? " value has been uploaded successfully " : string(strerror(errno));
            _build_alert_user_messages_(status ? N_DONE : N_FAILED, " " + msgSatus);
        } else {
            oldPath = ret->_openedFILE;
             newPath = to_string(set_time()) + ".key";
             msgSatus = " " + newPath;
             newPath = joinPath(UploadPath, newPath);
             status = (rename(oldPath.c_str(), newPath.c_str()) == 0);
             msgSatus += status ? " has been uploaded successfully !" : string(strerror(errno));
            _build_alert_user_messages_(status ? N_DONE : N_FAILED , " " + msgSatus);
        }
        it ++;
    }
}

void response::_setup_normal_upload_(const string &UploadPath, bool findUploadPath) {

    string oldPath, newPath, extension = ".", msgSatus, filename;
    requestBody    *ret = &REQ._body;
    
    oldPath = ret->bodyPath;
    extension += MimeTypes(ret->bodyType);
    if (extension == ".")
        extension += "upload";
    filename = "serveX_" + to_string(set_time()) + extension;
    newPath = joinPath(UploadPath, filename);
    if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
        msgSatus = " " + filename +  " has been uploaded successfully " + (!findUploadPath ? "but in /tmp" : "");
        _build_alert_user_messages_(findUploadPath ? N_DONE : N_WARNING , msgSatus);
    } else {
         msgSatus = " an error during upload " + filename + " " + strerror(errno);
        _build_alert_user_messages_(N_FAILED, msgSatus);              
    }
}

void response::_setup_error_pages(const int &_CodeStatus, const ErrorPages *Err, const string &msg) {
    _cgi = -1;
    _set_connection_(false);
    _set_http_code_status_(_CodeStatus);
    _init_headers_();
    if (msg.empty())
        _find_error_pages_(Err);
    else {
        _headers.adding("Content-Type", MimeTypes["html"]);
        _build_response_page_(_httpCodeSatus, msg);
    }
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
    _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
}

void response::_setup_redirective_(const pair<int, string> *_redirective, bool local) { 
    Redirect redirect(_redirective->second, _redirective->first, local);
    _set_connection_(false);
    _set_http_code_status_(redirect.getRedirectStatus());
    _init_headers_();

    if (!redirect.isRedirectStatus()) {
        _buid_redirective_page_(HTTP_NOT_FOUND, "redirect not found !");
        _set_http_code_status_(HTTP_NOT_FOUND);
        goto sendRedirect;
    }

    redirect._make_redirect_(_vts);
    _headers.adding("Location", redirect._getRedirectHost());
    _buid_redirective_page_(redirect.getRedirectStatus());
    sendRedirect:
        _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
}

void response::_setup_delete_response_page(short mode, const string &msg) {
    _set_connection_(true);
    _set_http_code_status_( errno == EPERM ? HTTP_FORBIDDEN : HTTP_OK);
    _init_headers_();
    _headers.adding("Content-Type", MimeTypes["html"]);

    _build_alert_user_messages_(N_INIT | mode, msg);
    
    _headers.adding("Content-Lenght", to_string(get_ostringstream_size(_pages)));
    _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
}

void response::_setup_lenghted_response_(const string &path) {
    _set_connection_(true);
    _set_http_code_status_(HTTP_OK);
    _init_headers_();
     
    _headers.adding("Content-Type", MimeTypes.GetMimeTypeFromExtension(path));
    _headers.adding("Content-Lenght", to_string(get_ifstream_size(*file)));
    _set_stat_(RESPONSE_HEADERS | RESPONSE_LENGHTED_BODY);
}

void response::_setup_chunked_response_( const string &path ) {
    _set_connection_(true);
    _set_http_code_status_(HTTP_OK);
    _init_headers_();
    _headers.adding("Content-Type", MimeTypes.GetMimeTypeFromExtension(path));
    _headers.adding("Content-Lenght", to_string(get_ifstream_size(*file)));
    _headers.adding("Transfer-Encoding", "Chunked");
    _set_stat_(RESPONSE_HEADERS | RESPONSE_CHUNKED_BODY);
}

void response::_setup_upload_response_(void) {
    _set_http_code_status_(HTTP_CREATED);
    _set_connection_(true);
    _init_headers_();
    
    _build_upload_response_page();

    _headers.adding("Content-Type", MimeTypes["html"]);
    _set_stat_(PAGES_SEND_DONE | RESPONSE_DONE);
}

void response::_setup_uploading_page_(__unused size_t uploaded_data) {

    _set_http_code_status_(HTTP_OK);
    _set_connection_(true);
    _init_headers_();
    _build_uploading_page_(uploaded_data);
    _headers.adding("Content-Type", MimeTypes["html"]);
    _set_stat_(PAGES_SEND_DONE);

}

void response::_setup_lenghted_type_(const string &path, bool type) {
    if(!type) {
        _setup_lenghted_response_(path);
    } else {
        _setup_chunked_response_(path);
    }
}



bool response::send(__unused socket_t &fd, const char *__buffer, const size_t &__size) {
    
    bool done = (::send(fd, __buffer, __size, 0) < 1);
    if (done) {
        closefiles(_fdCgi);
        closeStreamFile();
        _pages.clear(), _pages.str("");
        _set_stat_(RESPONSE_DONE);
    }
    return done;
}

void response::_send_response(__unused socket_t fd) {
    if (_stat & (PAGES_SEND_DONE | RESPONSE_HEADERS)) {
        _setup_response_message_();

        if (send(fd, _stream.str().c_str(), _stream.str().size()))
            return;

        if (_stat & PAGES_SEND_DONE) {
            if (send(fd, _pages.str().c_str(), _pages.str().size())) 
                return ;
            _pages.clear(), _pages.str("");
            _stat &= ~PAGES_SEND_DONE;
            _set_stat_( _stat & RESPONSE_DONE ? RESPONSE_DONE : _stat);
            return ;
        }
        _stat &= ~RESPONSE_HEADERS;
        _set_stat_(_stat);
    }
    switch (_stat) {
        case RESPONSE_CGI_BODY:
            _send_cgi_body_(fd);
            break;
        case RESPONSE_CHUNKED_BODY:
            _send_chunked_body_(fd);
            break;
        case RESPONSE_LENGHTED_BODY:
            _send_lenghted_body_(fd);
            break;
    }
}

void response::_send_chunked_body_(__unused socket_t fd) {
    char buffer[(1 << 10)] = {0};
    size_t offset = 0;
    size_t chunkSize = (1 << 10);
    stringstream ss;

    file->read(buffer, (1 << 10));
    string tmp(buffer);
    size_t dataSize = tmp.size();
    while (offset < dataSize) {
        size_t remainingData = dataSize - offset;
        size_t currentChunkSize = (remainingData > chunkSize) ? chunkSize : remainingData;
        ss << hex << currentChunkSize << CRLF;
        ss << tmp.substr(offset, currentChunkSize) << CRLF;
        if (send(fd, buffer, file->gcount()))
            return ss.clear(), ss.str("");
        ss.clear(), ss.str("");
        offset += currentChunkSize;
    }
    if (file->eof())
        ss << "0" CRLF CRLF, _set_stat_(RESPONSE_DONE);
}

void response::_send_lenghted_body_(__unused socket_t fd) {
    char buffer[1024] = {0};
    file->read(buffer, 1024);

     if (send(fd, buffer, file->gcount()))
        return ;
    _set_stat_(file->eof() ? RESPONSE_DONE : _stat);
}

void response::_send_cgi_body_(__unused socket_t fd) {
    char buffer[(1 << 10)] = {0};
    int nbyte;

    nbyte = read(_fdCgi[CGI_OUT], buffer, (1 << 10));
    
    if (nbyte <= 0) {
         send(fd, buffer, nbyte);
         closefiles(_fdCgi);
        _set_stat_(RESPONSE_DONE);
        return ;
    }
    if (send(fd, buffer, nbyte))
        return ;
}


void response::killCgi() {
    if (_cgi == -1)
        return ;
    kill(_cgi, SIGKILL);
    waitpid(_cgi, 0, 0);
}

void response::_init_headers_( void ) {
    _headers.clear();
    _headers.adding("server", NAME "/" _VERSION);
    _headers.adding("Date", getCurrentGMTTime());
    _headers.adding("Last-Modified", getCurrentGMTTime());
    _headers.adding("Connection", !_keepAlive ? "Closed" : "keep-alive" );
    if (_keepAlive)
        _headers.adding("Keep-Alive" , "timeout=15");
}

void response::_find_error_pages_(const ErrorPages* Err) {

    ErrorPages::const_iterator it = Err->begin();
    for (; it != Err->end(); it++) {
        if (it->first == _httpCodeSatus) {
            ifstream ErrorPage(it->second);
            if (!ErrorPage.is_open()) {
	            _headers.adding("Content-Type", MimeTypes["html"]);
                if (errno & ENOENT)
                    return _build_response_page_(HTTP_NOT_FOUND, " PAGE ERROR PATH NOT FOUND ");
                else
                    return _build_response_page_(HTTP_FORBIDDEN, " PAGE ERROR FORBIDDEN "); // wait for edit
            }
            string _ErrorPage;
            getline(ErrorPage, _ErrorPage, (char)0);
            (_pages) << _ErrorPage;
	        _headers.adding("Content-Type", MimeTypes.GetMimeTypeFromExtension(it->second));
            return ;
        }
    }
	_headers.adding("Content-Type", MimeTypes["html"]);
    _build_response_page_(_httpCodeSatus);
}

void response::revokeItem(string _FILE_PATH_, bool mode) {
    string title;
    string::size_type idx = _FILE_PATH_.find_last_of('/');
    title = _FILE_PATH_;
    if (idx != string::npos)
        title = _FILE_PATH_.substr(idx);
    if (mode) {
        title = " " + REQ._path;
        _setup_delete_response_page(N_WARNING, title + " : is a directory !");
        return ;
    }
    bool access_file = (access(_FILE_PATH_.c_str(), W_OK) == 0);
    if (access_file && remove(_FILE_PATH_.c_str()) == 0) {
        _setup_delete_response_page(N_DONE, " You successfully Delete " + title ); 
    } else {
        errno = (!access_file) ? EPERM : errno;
        _setup_delete_response_page(N_FAILED, title + " " + strerror(errno)); 
    }
}

bool response::likeness( const int _st ) const {
    return  (_stat & _st);
}

void response::closeStreamFile() {
    if (file) {
        file->close();
        delete file;
        file = NULL;
    }
}

void response::set(const server_data* Virtualserver, request &Request) {
    if (_stat & ~RESPONSE_INIT) 
        return ;
    _vts = (server_data*)Virtualserver;
    req = &Request;
    _location = _vts->matchLocation(Request._path);
    
}

void response::_set_http_code_status_(const short _st) {
    _httpCodeSatus = _st;
}

void response::_set_stat_(const short _st) {
    _stat = _st;   
}

void response::_set_connection_(const bool _st) {
    _keepAlive = _st;
}

response::response() {
    _stat = RESPONSE_INIT;
    _httpCodeSatus = HTTP_BAD_REQUEST;
    _keepAlive = true;
    _location = __null;
    req = __null;
    file = __null;
    _vts = __null;
    _location = __null;
    _cgi = -1;
    _fdCgi[CGI_OUT] = _fdCgi[CGI_ERR] = -1;
    _time = 0;
}

void response::reset() {
    _stat = RESPONSE_INIT;
    _httpCodeSatus = HTTP_BAD_REQUEST;
    _headers.clear();
    req = NULL;
    _vts = NULL;
    _location = __null;
    _stream.clear();
    _stream.str("");
    _keepAlive = true;
    _pages.clear();
    _pages.str("");
    _cgi = -1;
    _time = 0;
    _fdCgi[0] = _fdCgi[1] = -1;

    closeStreamFile();
}

response::~response() {}



