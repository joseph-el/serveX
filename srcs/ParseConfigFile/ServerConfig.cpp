/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:18:06 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 17:32:29 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

// ServerConfig Constructors
ServerConfig::ServerConfig() : _maxBodySize(0), _isDefaultServer(false), _port(0) {}

// ServerConfig Setters
void ServerConfig::setListenPort(int port) {
    this->_port = port;
}
void ServerConfig::setHost(std::string const& host) {
    this->_host = host;
}
void ServerConfig::setServerName(std::string const& serverName) {
    _serverName = serverName;
}
void ServerConfig::addLocation(LocationConfig const& locationObj) {
    _locations.push_back(locationObj);
}
void ServerConfig::setDefaultServer(bool isDefault) {
    _isDefaultServer = isDefault;
}
void ServerConfig::addErrorPage(int errorCode, const std::string& errorPage)  {
    _errorPages[errorCode] = errorPage;
}
void ServerConfig::setMaxBodySize(int sizeInBytes) {
    _maxBodySize = sizeInBytes;
}

// ServerConfig Getters
int             ServerConfig::getListenPort() const {
    return _port;
}
int             ServerConfig::getMaxBodySize() const {
    return _maxBodySize;
}
bool            ServerConfig::isDefaultServer() const 
{
    return _isDefaultServer;
}
std::string     ServerConfig::getServerName() const {
    return _serverName;
}
std::string     ServerConfig::getHost() const {
    return _host;
}
const std::vector<LocationConfig>&  ServerConfig::getLocations() const {
    return _locations;
}
const std::map<int, std::string>&   ServerConfig::getErrorPages() const 
{
    return _errorPages;
}


/*  ServerConfig Helper Functions   */
bool    ServerConfig::isServerValidAndReady( void )
{
    if (!_maxBodySize || !_port || _host.empty() || _serverName.empty() || !_locations.size() || !_errorPages.size())
        return false;
    return true;
}

/*  print Server Config Data*/
void    ServerConfig::printServerConfig() const
{
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "*****Checking Server Config Data****" << std::endl << std::endl;

    std::cout << "Port: " << _port << std::endl;
    std::cout << "Host:" << " " << _host << std::endl;
    std::cout << "Server Name: " << _serverName;
    std::cout << "Max Body Size: " << _maxBodySize << " bytes" << std::endl;
    std::cout << "Default Server: " << (_isDefaultServer ? "true" : "false") << std::endl;

    std::cout << "Error Pages:" << std::endl;
    for (std::map<int, std::string>::const_iterator it = _errorPages.begin(); it != _errorPages.end(); ++it)
        std::cout << "  " << it->first << " => " << it->second << std::endl;

    std::cout << "Locations:" << std::endl;
    for (size_t i = 0; i < _locations.size(); i++)
    {
        std::cout << "Location " << i + 1 << ":" << std::endl;
        
        std::cout << "  Default Path: " << _locations[i].getPath() << std::endl;
        std::cout << "  Root: " << _locations[i].getRoot() << std::endl;
        std::cout << "  AutoIndex: " << (_locations[i].getAutoIndex() ? "true" : "false") << std::endl;
        std::cout << "  AutoUpload: " << (_locations[i].getAutoUpload() ? "true" : "false") << std::endl;
        std::cout << "  Cgi_path: " << _locations[i].getCgiPath() << std::endl;
        std::cout << "  Upload_path: " << _locations[i].getUploadPath() << std::endl;
    
        std::cout << "  Indexes:";
        const std::vector<std::string>& locationIndex = _locations[i].getIndexes();
        for (size_t j = 0; j < locationIndex.size(); j++)
            std::cout << " " << locationIndex[j];

        std::cout << std::endl;

        std::cout << "Allowed_methods:";
        const std::vector<std::string>& locationAllowedMethods = _locations[i].getAllowedMethods();
        for (size_t i = 0; i < locationAllowedMethods.size(); i++)
            std::cout << " " << locationAllowedMethods[i];

        std::cout << std::endl;
    }
}