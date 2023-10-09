#include "server_data.hpp"

/*  server_data Constructors    */
server_data::server_data() : _maxBodySize(MAX_BODY_SIZE), _port(0), _autoIndex(false) {}

/*  Sx_ServerData Setters   */
void    server_data::setListenPort(int port) {
    this->_port = port;
}
void    server_data::setHost(std::string const& host) {
    this->_host = host;
}
void    server_data::setServerName(std::string const& serverName) {
    _serverName = serverName;
}
void    server_data::setAutoIndex ( bool indexstatus)
{
    _autoIndex = indexstatus;
}
void    server_data::setServerRoot(std::string const& serverRoot) {
    _serverRoot = serverRoot;
}
void    server_data::addLocation(location_data const& locationObj) {
    _locations.push_back(locationObj);
}
void    server_data::addErrorPage(int errorCode, const std::string& errorPage)  {
    _errorPages[errorCode] = errorPage;
}
void    server_data::setRedirection(int status, const std::string& path)  {
    _redirection.first = status;
    _redirection.second = path;
}
void    server_data::setMaxBodySize( unsigned long long sizeInBytes) {
    _maxBodySize = sizeInBytes;
}
void    server_data::setIndex ( std::string const& index )
{
    _serverIndexes.push_back(index);
}

/*   server_data Getters    */
int         server_data::getListenPort() const {
    return _port;
}
bool        server_data::getAutoIndex() const
{
    return _autoIndex;
}
std::string server_data::getServerName() const {
    return _serverName;
}
std::string server_data::getServerRoot() const
{
    return _serverRoot;
}
std::string server_data::getHost() const {
    return _host;
}
const std::vector<location_data>&   server_data::getLocations() const {
    return _locations;
}
const std::vector<std::string>&     server_data::getServerIndexes() const
{
    return _serverIndexes;
}
unsigned long long                  server_data::getMaxBodySize() const {
    return _maxBodySize;
}
const std::map<int, std::string>&   server_data::getErrorPages() const 
{
    return _errorPages;
}
const std::pair<int, std::string>&  server_data::getServerRedirection() const 
{
    return _redirection;
}

/*  server_data Helper Functions   */
bool    server_data::isServerValidAndReady( void )
{
    if (!_port || _host.empty())
        return false;
    return true;
}