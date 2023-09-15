#include "sX_server_data.hpp"

// Sx_server_data Constructors
Sx_server_data::Sx_server_data() : _maxBodySize(0), _isDefaultServer(false), _port(0) {}

// Sx_ServerData Setters
void Sx_server_data::setListenPort(int port) {
    this->_port = port;
}
void Sx_server_data::setHost(std::string const& host) {
    this->_host = host;
}
void Sx_server_data::setServerName(std::string const& serverName) {
    _serverName = serverName;
}
void Sx_server_data::addLocation(Sx_location_data const& locationObj) {
    _locations.push_back(locationObj);
}
void Sx_server_data::setDefaultServer(bool isDefault) {
    _isDefaultServer = isDefault;
}
void Sx_server_data::addErrorPage(int errorCode, const std::string& errorPage)  {
    _errorPages[errorCode] = errorPage;
}
void Sx_server_data::setMaxBodySize(int sizeInBytes) {
    _maxBodySize = sizeInBytes;
}

// Sx_server_data Getters
int     Sx_server_data::getListenPort() const {
    return _port;
}
int     Sx_server_data::getMaxBodySize() const {
    return _maxBodySize;
}
bool    Sx_server_data::isDefaultServer() const 
{
    return _isDefaultServer;
}
std::string     Sx_server_data::getServerName() const {
    return _serverName;
}
std::string     Sx_server_data::getHost() const {
    return _host;
}
const std::vector<Sx_location_data>&  Sx_server_data::getLocations() const {
    return _locations;
}
const std::map<int, std::string>&   Sx_server_data::getErrorPages() const 
{
    return _errorPages;
}


/*  Sx_server_data Helper Functions   */
bool    Sx_server_data::isServerValidAndReady( void )
{
    if (!_maxBodySize || !_port || _host.empty() || _serverName.empty() || !_locations.size() || !_errorPages.size())
        return false;
    return true;
}