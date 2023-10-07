# include "client.hpp"

s_client::s_client(socket_t newconnection) : _newconnection(newconnection)
{}

void s_client::set_server_idx(int idx, int server_socket) {
    _server_idx = idx;
    _server_socket = server_socket;
}

socket_t s_client::get_client_socket() {
    return _newconnection;
}

void s_client::DealwithResponce() {
    return ;
}

void s_client::DealwithRequest( stringstream *stream ) 
{
    if (!stream) {
        cout << "Error stream " << endl;
        return ;
    }

    req_.interpretRequest(*stream);
    if (req_._status & REQUEST_PARSE_DONE) {
        cout << "SET VALID TO TRUE " << endl;
        req_.valid=true ;
    }

}