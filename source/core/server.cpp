# include "server.hpp"
# include "../www/socket.hpp"
# include "../utility/utils.hpp"
# include "../www/client.hpp"

// Clients clients;

std::vector<s_client> clients;

void init_Webserv(int argc, char *const argv[])
{
    Options opt(argc, argv);

    if (!opt.successful() or !MainContext.successful())
        return ;

    pair<socket_t, socket_t>  fd_range;
    fd_set                    rd_socket, wr_socket, wr_socket_copy, rd_socket_copy;
    vector<Socket>            _socket = init_Socket(MainContext.getServers(), rd_socket, fd_range);

    while (true)
    {
        rd_socket_copy = rd_socket;
        struct timeval timeout = getmstime();
        select(fd_range.second + 1, &(rd_socket_copy), NULL, NULL, &timeout);
    
        for (int i = fd_range.first; i < fd_range.second + 1; i++)
        {
            if (FD_ISSET(i, &(rd_socket_copy)))
            {   int idx = is_inSocket(i, _socket);
                if (idx != -1)
                {
                    socket_t newconnection = _socket[idx].accept();
                    if (newconnection == -1) {
                        cerr << NAME << " : Failed to accept connection." << endl;
                        goto ExpireConnection;
                    }
                    clients.back().set_server_idx(idx, i);
                    FD_SET(newconnection, &(rd_socket));
                    if (newconnection > fd_range.second)
                        fd_range.second = newconnection;
                }
                else
                {
                    for (int c = 0; c < clients.size(); c++) {
                        std::cout << c << "   here" << std::endl;
                        if (clients[c].get_client_socket() == i) {
                            clients[c].DealwithRequest();
                            clients[c].DealwithResponce();
                            FD_CLR(i, &(rd_socket));
                            FD_ZERO(&rd_socket_copy);
                            clients.erase(clients.begin() + c);
                            break ;
                        }
                    }
                }
            }
            ExpireConnection:
                clients[0].Expireconnection(); // to handel 
        }
    }
}