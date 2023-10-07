# include "server.hpp"
# include "../www/socket.hpp"
# include "../utility/utils.hpp"
# include "../www/client.hpp"
#include <cstdio>
#include <sys/select.h>


std::vector<s_client> clients;

int x = 0;

stringstream *Readrequest(socket_t _fd)
{
    // cout << "----Get <" << ++x << "> rcleaequest ----" << endl;
    char stream[(1 << 0xA)];
    stringstream *_stream = new stringstream();
    int bytes;

    bytes = recv(_fd, stream, (1 << 0xA), 0);
    if (!bytes or bytes == -1)
        return nullptr;
    _stream->write(stream, bytes);
    return _stream;
}

void init_Webserv(int argc, char *const argv[])
{
    Options opt(argc, argv);

    if (!opt.successful() or !MainContext.successful())
        return ;
    
    cout << "webser waiting for clients : " << endl;

    pair<socket_t, socket_t>  fd_range;
    fd_set                    rd_socket, wr_socket, wr_socket_copy, rd_socket_copy;
    vector<Socket>            _socket = init_Socket(MainContext.getServers(), rd_socket, fd_range);
    FD_ZERO(&wr_socket);
    while (true)
    {
        FD_ZERO(&rd_socket_copy);
        FD_ZERO(&wr_socket_copy);
        rd_socket_copy = rd_socket;
        wr_socket_copy = wr_socket;
        // select function wait for any event in the socket
        if (select(fd_range.second + 1, &(rd_socket_copy), &wr_socket_copy, NULL, 0) == -1)
            perror("select");
    
        for (int i = fd_range.first; i < fd_range.second + 1; i++)
        {
            // FD_ISSET check if the socket is ready to read or write
            if (FD_ISSET(i, &(rd_socket_copy)))
            {   int idx = is_inSocket(i, _socket);
                if (idx != -1)
                {
                    socket_t newconnection = _socket[idx].accept();
                    if (newconnection == -1)
                    {
                        cerr << NAME << " : Failed to accept connection." << endl;
                        goto ExpireConnection;
                    }
                    clients[clients.size() - 1].set_server_idx(idx, i);
                    FD_SET(newconnection, &(rd_socket));
                    if (newconnection > fd_range.second)
                        fd_range.second = newconnection;
                }
                else
                {
                    for (int c = 0; c < clients.size(); c++) {
                        if (clients[c].get_client_socket() == i) {
                            
                            stringstream *ss = Readrequest(i);
                            // cout << "the request < " <<  i << " > : "  << endl << ss->str() << endl;
                            clients[c].DealwithRequest(ss);
                            // cout << "-------------end of rq-------------" << endl;
                            ss->str("");
                            delete ss;
           
                            if (clients[c].reset()) {
                                FD_CLR(i, &(rd_socket));
                                FD_SET(i, &wr_socket);
                                cout << "reset settings " << endl;
                            }

                            break ;
                        }
                    }
                }
            }
            if (FD_ISSET(i, &wr_socket_copy))
            {
                for (int c = 0; c < clients.size(); c++) {
                    if (clients[c].get_client_socket() == i) {
                        clients[c].DealwithResponce();
                        send(i, "hello world", sizeof("hello world"), 0);
                        // yoel-idr use your flag to check if you have done sending the response before this tree lines
                        FD_CLR(i, &wr_socket);
                        // std::cout << "client " << c << " will be deleted" << std::endl;
                        clients.erase(clients.begin() + c);
                        close(i);
                        break ;
                    }
                }
            }
            ExpireConnection:
                clients[0].Expireconnection(); // to handel 
        }
    }
}