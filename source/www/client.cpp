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

void s_client::DealwithRequest( stringstream *stream, __unused const server_data *_virtualServer) {
    if (!stream)
        return req.UpdateStatus(REQUEST_PARSE_DONE);
    reset();
    req.interpretRequest(*stream);
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

