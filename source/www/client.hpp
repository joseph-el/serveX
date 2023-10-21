# ifndef __CLIENT_H__
# define __CLIENT_H__

# include "server-core.hpp"
class s_client {

    private :
        request  req;      
        socket_t newconnection;
        socket_t server_socket;

    public :

        socket_t    server_idx;
        response    res;
        # ifndef __ADDRESS__
            # define SERVER_ADDRESS (&_socket[clients[c].server_idx].get_server_address())
            # define MAX_BYTES_RECV 2048
        # endif
        void DealwithRequest( stringstream *,const server_data *);
        void DealwithResponce(const server_data *_vts = __null);

        void     set_server_idx(socket_t, socket_t);
        socket_t get_client_socket();

        void reset ();
        bool clientDone() const;
        bool request_done() const;
        s_client();
       ~s_client();
        s_client(socket_t);


    s_client &operator=(const s_client &other) {
        if (this != &other) {
            this->req = other.req;
            this->newconnection = other.newconnection;
            this->server_socket = other.server_socket;
            this->server_idx = other.server_idx;
            this->res = other.res;
        }
        return *this;
    }

    s_client(const s_client& other) {
        *this = other;
    }


};

extern vector<s_client> clients;

# endif