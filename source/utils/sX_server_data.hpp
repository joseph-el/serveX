#ifndef SX_SERVER_DATA_HPP
#define SX_SERVER_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "sX_location_data.hpp"

    /*
        Sx_server_data is a class that hold everything you need about a server configuration,
        and some helper functions to diplay them...
    */

class   Sx_server_data
{
public:

    /*  Constructors */
    Sx_server_data ( void );

    /* Add to vectors */
    void    addErrorPage( int errorCode, const std::string& errorPage );
    void    addLocation( Sx_location_data const& locationObj );

    /*  Setters */
    void    setListenPort(int port);
    void    setHost(std::string const& host);
    void    setServerName( std::string const& serverName);
    void    setDefaultServer(bool isDefault);
    void    setMaxBodySize(int sizeInBytes);

    /*  Getters */
    int                                             getListenPort() const;
    int                                             getMaxBodySize() const;
    bool                                            isDefaultServer() const;
    std::string                                     getHost() const;
    std::string                                     getServerName() const;
    const   std::map<int, std::string>&             getErrorPages() const;
    const   std::vector<Sx_location_data>&   getLocations() const;

    /*  Other Helper Functions  */
    bool    isServerValidAndReady( void );

private:

    int                                     _maxBodySize;
    bool                                    _isDefaultServer;
    int                                     _port;
    std::string                             _host;
    std::string                             _serverName;
    std::map<int, std::string>              _errorPages;
    std::vector<Sx_location_data>           _locations;
    
};

#endif