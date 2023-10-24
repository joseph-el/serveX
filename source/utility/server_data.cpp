# include "server-core.hpp"
 
/*  server_data Constructors    */
server_data::server_data() : _maxBodySize(MAX_BODY_SIZE), _port(0), _autoIndex(false) {}
server_data::server_data( const server_data& other )
{
        *this = other; 
};


server_data &server_data::operator=( const server_data& other)
{
    if (this != &other)
    {
        this->_maxBodySize = other._maxBodySize;
        this->_port = other._port;
        this->_autoIndex = other._autoIndex;
        this->_host = other._host;
        this->_serverName = other._serverName;
        this->_serverRoot = other._serverRoot;
        this->_serverIndexes = other._serverIndexes;
        this->_errorPages = other._errorPages;
        this->_redirection = other._redirection;
        this->_locations = other._locations;
        this->_serverAllowedMethods = other._serverAllowedMethods;
    }
    return *this;
}

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

void    server_data::setServerAllowedMethod ( int method )
{
    this->_serverAllowedMethods.push_back(method);
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

std::vector<int>                    server_data::getServerAllowedMethods() const
{
    return _serverAllowedMethods;
}


/*  server_data Helper Functions   */
bool    server_data::isServerValidAndReady( void )
{
    if (!_port || _host.empty())
        return false;
    return true;
}

bool    server_data::ServerIsRedirective( void ) const {
    return _redirection.first > 0 && !_redirection.second.empty();
}

bool    server_data::foundRoot( void ) const {
    return !_serverRoot.empty();
}

location_data*  server_data::matchLocation(string _path) {

    location_data   *matched = __null;
    Base it       = _locations.begin();
    string::size_type   _size = 0;

    for (;it != _locations.end(); it++) {
        string::size_type ret = commonPrefix(it->getPath(), _path);
        if (ret > _size) {
            matched = (location_data *)it.base();
            _size = ret;
        }
    }
    if (!matched && foundRoot()) {
        _locations.clear();
        location_data ret = location_data(_serverRoot, _serverIndexes, _serverAllowedMethods,  _autoIndex);
        _locations.push_back(ret);
        return (location_data*)&_locations[0];
    }
    return matched;
}
