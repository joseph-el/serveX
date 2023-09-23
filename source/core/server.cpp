# include "server.hpp"
# include "../www/socket.hpp"
# include "../utility/utils.hpp"
# include "../www/client.hpp"

Clients clients;

void init_Webserv(int argc, char *const argv[])
{
    Options opt(argc, argv);

    if (!opt.successful() or !MainContext.successful())
        return ;

    pair<socket_t, socket_t>  fd_range;
    fd_set                    rd_socket, rd_socket_copy;
    vector<Socket>            _socket = init_Socket(MainContext.getServers(), rd_socket, fd_range);

    while (true)
    {
        rd_socket_copy = rd_socket;
        struct timeval timeout = getmstime();
        select(fd_range.second + 1, &(rd_socket_copy), NULL, NULL, &timeout);
    
        for (int i = fd_range.first; i < fd_range.second + 1; i++)
        {
            if (FD_ISSET(i, &(rd_socket_copy)))
            {   
                if (int idx = is_inSocket(i, _socket) and idx != -1)
                {
                    socket_t newconnection = _socket[idx].accept();
                    if (newconnection == -1) {
                        cerr << NAME << " : Failed to accept connection." << endl;
                        goto ExpireConnection;
                    }
                    else {
                        clients[idx] = s_client(newconnection);
                        clients[idx].DealwithRequest();
                        clients[idx].DealwithResponce();
                    }
                    close(newconnection);
                }
            }
            ExpireConnection:
                clients.Expireconnection(); // to handel 
        }
    }
}