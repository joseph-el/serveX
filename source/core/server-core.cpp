# include "server-core.hpp"

vector<s_client> clients;

static stringstream *Readrequest(socket_t _fd)
{
    char stream[MAX_BYTES_RECV]; 
    stringstream *_stream = new stringstream();
    int bytes;
    bytes = recv(_fd, stream, MAX_BYTES_RECV, 0);
    if (!bytes or bytes == -1)
        return __null;
    _stream->write(stream, bytes);
    return _stream;
}

static bool resetRanges(socket_t &maxRange, vector<Socket>& _socket) {
    
    maxRange = 0;
    for (size_t s = 0; s < _socket.size(); s++) {
        (_socket[s].getsocket_t() > maxRange) &&
            (maxRange = _socket[s].getsocket_t());
    }
    for (size_t j = 0; j < clients.size(); j++) {
        (clients[j].get_client_socket() > maxRange) &&
            (maxRange = clients[j].get_client_socket());
    }
    return true;
}

void init_Webserv(__unused int argc, __unused char *const argv[])
{
    // Options opt(argc, argv); 
    // !opt.successful() 
    if (!MainContext.successful())
        return ;

    t_pair fd_range;
    fd_set rd_socket, wr_socket, wr_socket_copy, rd_socket_copy;
    vector<Socket> _socket = init_Socket(MainContext.getServers(), rd_socket, fd_range);
    FD_ZERO(&wr_socket);

    logger.notice("waiting for client");
    
    while (true) {
        FD_ZERO(&rd_socket_copy);
        FD_ZERO(&wr_socket_copy);
        rd_socket_copy = rd_socket;
        wr_socket_copy = wr_socket;
 
        if (select(fd_range.second + 1, &(rd_socket_copy), &wr_socket_copy, 0, 0) == -1)
            logger.notice(string(strerror(errno)));
        
        for (socket_t i = fd_range.first; i < fd_range.second + 1; i++) {
            if (FD_ISSET(i, &(rd_socket_copy))) {
                socket_t idx = is_inSocket(i, _socket);
                if (idx != -1) {
                    socket_t newconnection = _socket[idx].accept();
                    if (newconnection == -1) 
                        logger.notice("Failed to accept connection");
                    clients[clients.size() - 1].set_server_idx(idx, i);
                    FD_SET(newconnection, &(rd_socket));
                    if (newconnection > fd_range.second)
                        fd_range.second = newconnection;
                } else {
                    for (size_t c = 0; c < clients.size(); c++) {
                        if (clients[c].get_client_socket() == i) {
                            stringstream *ss = Readrequest(i);
                            clients[c].DealwithRequest(ss, SERVER_ADDRESS);
                            if (clients[c].request_done()) {
                                logger.notice(clientmsg(i, false));
                                FD_CLR(i, &(rd_socket));
                                FD_SET(i, &wr_socket);
                            }
                            break ;
                        }
                    }
                }
            } if (FD_ISSET(i, &wr_socket_copy)) {
                for (socket_t c = 0; c < (socket_t)clients.size(); c++) {
                    if (clients[c].get_client_socket() == i) {
                        clients[c].DealwithResponce(SERVER_ADDRESS);
                        if (clients[c].clientDone()) {
                                (i == fd_range.second) && (resetRanges(fd_range.second, _socket));
                                logger.notice(clientmsg(i, true));
                                FD_CLR(i, &wr_socket);
                                clients[c].reset();
                                clients.erase(clients.begin() + c);
                                close(i);
                        }
                        break ;
                    }
                }
            }
        }
    }

}