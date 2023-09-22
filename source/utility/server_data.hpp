#ifndef _SERVER_DATA_H_
#define _SERVER_DATA_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "location_data.hpp"

    /*
        server_data is a class that hold everything you need about a server configuration,
        and some helper functions to diplay them...
    */

class   server_data
{
public:

    /*  Constructors */
    server_data ( void );
    server_data ( const server_data& other );
    
    /* Operators */
    server_data &operator=( const server_data& other);

    /* Add to vectors */
    void    addErrorPage( int errorCode, const std::string& errorPage );
    void    addLocation( location_data const& locationObj );

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
    const   std::vector<location_data>&   getLocations() const;

    /*  Other Helper Functions  */
    bool    isServerValidAndReady( void );

private:

    int                                     _maxBodySize;
    bool                                    _isDefaultServer;
    int                                     _port;
    std::string                             _host;
    std::string                             _serverName;
    std::map<int, std::string>              _errorPages;
    std::vector<location_data>              _locations;
    
};
#endif