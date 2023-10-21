# include "server-core.hpp"

s_client::s_client(socket_t newconnection) : req(), newconnection(newconnection), res() {}
s_client::s_client() {}
s_client::~s_client() {}

void    s_client::set_server_idx(socket_t idx, socket_t _server_socket) {
    server_idx = idx;
    server_socket = _server_socket;
}

socket_t s_client::get_client_socket() {
    return newconnection;
}

# define INIT_UPLOADING_PAGE 8
# define HANDEL_UPLOADING_PAGE 16

void s_client::DealwithRequest( stringstream *stream, __unused const server_data *_virtualServer) 
{
    // static int remember = INIT_UPLOADING_PAGE;
    if (!stream)
        return req.UpdateStatus(REQUEST_PARSE_DONE);
    reset();
    req.interpretRequest(*stream);

    // if (req.likeness(REQUEST_BODY) && remember & INIT_UPLOADING_PAGE) {
    //     pair<int, string> redirect;
    //     redirect.first = HTTP_MOVED_PERMANENTLY;
    //     redirect.second = "https://tnaceur.github.io/loading/loading.html";
    //     res._setup_redirective_(&redirect, true);
    //         res.set(_virtualServer, req);
    //     res._setup_uploading_page_(req.Uploaded());
    //     res._send_response(newconnection);
    //     remember = HANDEL_UPLOADING_PAGE;
    // } else if (req.likeness(REQUEST_PARSE_DONE)) {
    //     remember = INIT_UPLOADING_PAGE;
    //     res.reset();
    // }

    stream->str("");
    delete stream;
}

void s_client::DealwithResponce(const server_data* VirtualServer) {
    res.set(VirtualServer, req);
    res.interpret_response(newconnection);
}

bool s_client::request_done() const {
    return req.likeness(REQUEST_PARSE_DONE) or req._unacceptable_request_();
}

bool s_client::clientDone() const {
    return res.likeness(RESPONSE_DONE);
}

void s_client::reset() {

    if (res.likeness(RESPONSE_DONE) && req.likeness(REQUEST_PARSE_DONE)) {
        res.killCgi();
        req.reset();
        res.reset();
    }
}

