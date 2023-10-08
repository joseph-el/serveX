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
        s_client(const s_client &other) {
            // cout << "Client Copy Constructor" << endl;
            *this = other;
        }
        s_client &operator=(const s_client &other) {
            // cout << "Client Assignement Operator" << endl;
            if (this != &other) {
                this->_newconnection = other._newconnection;
                this->_server_socket = other._server_socket;
                this->_server_idx = other._server_idx;
                this->req_ = other.req_;
                this->res_ = other.res_;
            }
            return *this;
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