#include <stdio.h>
tmp


bool response::_build_cgi_body() {

    off_t   filesize;
    ssize_t nbyte;

    lseek(_fdCgi, 0, SEEK_SET);
    _set_http_code_status_(HTTP_OK);
    _set_connection_(false);
    _init_headers_();

    if (_pathFile.substr(_pathFile.find_last_of('.')) == ".php")
        return true;
    
    filesize = lseek(_fdCgi, 0, SEEK_END);
    lseek(_fdCgi, 0, SEEK_SET);
     
    char *buff = new char[filesize];
    nbyte = read(_fdCgi, buff, filesize);
    if (nbyte == -1) {
        delete[] buff;
        return false;
    }
    string content(buff, nbyte);
    string headerValue;
    delete[] buff;
    size_t found = content.find("Content-Type");
    if (found != string::npos) {
        size_t end = content.find("\r\n", found);
        if (end != string::npos) {
            string headerLine = content.substr(found, end - found);
            size_t pos = headerLine.find(":");
            if (pos != string::npos) {
                string headerKey = headerLine.substr(0, pos);
                headerValue = headerLine.substr(pos + 2);
                content.erase(found, end - found + 2); 
            } else
                return false;
        } else
            return false;
    } else
        return false;
    lseek(_fdCgi, 0, SEEK_SET);
    ftruncate(_fdCgi, 0);
    nbyte = write(_fdCgi, content.c_str(), content.size());
    if (nbyte == -1) {
        close(_fdCgi);
        return false;
    } 
    _headers.adding("Content-Type", headerValue);
    _headers.adding("Content-Lenght", to_string(content.size()));
    return true;
}


int main() {
    printf("Hello, World!\n");
    return 0;
}

  off_t filesize = lseek(_fdCgi, 0, SEEK_END);
    lseek(_fdCgi, 0, SEEK_SET);
     
    char *buff = new char[filesize];
    ssize_t nbyte = read(_fdCgi, buff, filesize);
    if (nbyte == -1){
        delete[] buff;
        return false;
    }
    string content(buff, nbyte);
    string headerValue;
    delete[] buff;
    size_t found = content.find("Content-Type:");
    if (found != string::npos) {
        size_t end = content.find("\r\n", found);
        if (end != string::npos) {
            string headerLine = content.substr(found, end - found);
            size_t pos = headerLine.find(":");
            if (pos != string::npos) {
                string headerKey = headerLine.substr(0, pos);
                headerValue = headerLine.substr(pos + 2);
                content.erase(found, end - found + 2); 
            } else
                return false;
        } else
            return false;
    } else
        return false;
    lseek(_fdCgi, 0, SEEK_SET);
    ftruncate(_fdCgi, 0);
    nbyte = write(_fdCgi, content.c_str(), content.size());
    if (nbyte == -1) {
        close(_fdCgi);
        return false;
    } 