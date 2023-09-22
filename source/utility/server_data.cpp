#include "server_data.hpp"

// server_data Constructors
server_data::server_data() : _maxBodySize(0), _isDefaultServer(false), _port(0) {}

server_data::server_data( const server_data& other )
{
        *this = other; 
};

server_data &server_data::operator=( const server_data& other)
{
    if (this != &other)
    {
        this->_maxBodySize = other._maxBodySize;
        this->_isDefaultServer = other._isDefaultServer;
        this->_port = other._port;
        this->_host = other._host;
        this->_serverName = other._serverName;
        this->_errorPages = other._errorPages;
        this->_locations = other._locations;
    }
    return *this;
}

// Sx_ServerData Setters
void server_data::setListenPort(int port) {
    this->_port = port;
}
void server_data::setHost(std::string const& host) {
    this->_host = host;
}
void server_data::setServerName(std::string const& serverName) {
    _serverName = serverName;
}
void server_data::addLocation(location_data const& locationObj) {
    _locations.push_back(locationObj);
}
void server_data::setDefaultServer(bool isDefault) {
    _isDefaultServer = isDefault;
}
void server_data::addErrorPage(int errorCode, const std::string& errorPage)  {
    _errorPages[errorCode] = errorPage;
}
void server_data::setMaxBodySize(int sizeInBytes) {
    _maxBodySize = sizeInBytes;
}

// server_data Getters
int     server_data::getListenPort() const {
    return _port;
}
int     server_data::getMaxBodySize() const {
    return _maxBodySize;
}
bool    server_data::isDefaultServer() const 
{
    return _isDefaultServer;
}
std::string     server_data::getServerName() const {
    return _serverName;
}
std::string     server_data::getHost() const {
    return _host;
}
const std::vector<location_data>&  server_data::getLocations() const {
    return _locations;
}
const std::map<int, std::string>&   server_data::getErrorPages() const 
{
    return _errorPages;
}


/*  server_data Helper Functions   */
bool    server_data::isServerValidAndReady( void )
{
    if (!_maxBodySize || !_port || _host.empty() || _serverName.empty() || !_locations.size() || !_errorPages.size())
        return false;
    return true;
}