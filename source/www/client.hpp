# ifndef _CLIENT_H_
# define _CLIENT_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "request.hpp"
# include "response.hpp"

class s_client {
    private:
        response res_;
        request  req_;
        socket_t _newconnection; // new client
        socket_t _server_socket; // server socket
        int       _server_idx;   // server index

    
    public:
        s_client() {
            // cout << "Client Constructor" << endl;
        }
        ~s_client() { 
            // cout << "Client Destructor" << endl;
        }
        s_client(socket_t newconnection);

        bool reset() {return req_.is_valid();}
        
        void set_server_idx(int idx, int server_socket);
        socket_t get_client_socket();
        
        void Expireconnection() {
            // exit(EXIT_FAILURE); // hhhhhhh debug about 20 min fuck
            // waiting to remove iterator and close the fd
        }
        void DealwithRequest( stringstream *);
        void DealwithResponce();
};

extern std::vector<s_client> clients;

# endif