# include "server-core.hpp"

vector<s_client> clients;

stringstream *Readrequest(socket_t _fd)
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

void init_Webserv(int argc, char *const argv[])
{
    Options opt(argc, argv);

    if (!opt.successful() or !MainContext.successful())
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
        if (select(fd_range.second + 1, &(rd_socket_copy), &wr_socket_copy, NULL, 0) == -1)
            logger.notice(string(strerror(errno)));
        
        for (int i = fd_range.first; i < fd_range.second + 1; i++) {
            if (FD_ISSET(i, &(rd_socket_copy))) {
                int idx = is_inSocket(i, _socket);
                if (idx != -1) {
                    socket_t newconnection = _socket[idx].accept();
                    if (newconnection == -1) 
                        logger.notice("Failed to accept connection");
                    clients[clients.size() - 1].set_server_idx(idx, i);
                    FD_SET(newconnection, &(rd_socket));
                    if (newconnection > fd_range.second)
                        fd_range.second = newconnection;
                }
                else {
                    for (int c = 0; c < clients.size(); c++) {
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
            }
            if (FD_ISSET(i, &wr_socket_copy)) {
                for (int c = 0; c < clients.size(); c++) {
                    if (clients[c].get_client_socket() == i) {
                        clients[c].DealwithResponce(SERVER_ADDRESS);
                        if (clients[c].clientDone()) {
                                // if (i == fd_range.second)
                                // {
                                //     fd_range.second = 0;
                                //     for (int s = 0; s < _socket.size(); s++)
                                //     {
                                //         if (_socket[s].getsocket_t() > fd_range.second)
                                //             fd_range.second = _socket[s].getsocket_t();
                                //     }
                                //     for (int j = 0; j < clients.size(); j++)
                                //     {
                                //         if (clients[j].get_client_socket() > fd_range.second)
                                //             fd_range.second = clients[j].get_client_socket();
                                //     }
                                // }
                                logger.notice(clientmsg(i, true));
                                FD_CLR(i, &wr_socket);
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