#ifndef _SERVER_DATA_H_
#define _SERVER_DATA_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "location_data.hpp"
# define MAX_BODY_SIZE 5368709120
    
    /*
        server_data is a class that hold everything you need about a server configuration,
        and some helper functions to diplay them...
    */

class   server_data
{
public:

    /*  Constructors */
    server_data ( void );
    server_data ( const server_data& );
    
    /* Operators */
    server_data &operator=( const server_data& );

    /* Add to vectors */
    void    addErrorPage( int, const std::string& );
    void    addLocation( location_data const& );

    /*  Setters */
    void    setListenPort(int);
    void    setHost(std::string const& );
    void    setServerName( std::string const& );
    void    setMaxBodySize( unsigned long long );
    void    setServerRoot( std::string const& );
    void    setIndex ( std::string const& );
    void    setRedirection(int, const std::string& );

    /*  Getters */
    int                                      getListenPort() const;
    unsigned long long                       getMaxBodySize() const;
    std::string                              getHost() const;
    std::string                              getServerName() const;
    const   std::map<int, std::string>&      getErrorPages() const;
    const   std::pair<int, std::string>&     getServerRedirection() const;
    const   std::vector<location_data>&      getLocations() const;
    const   std::vector<std::string>&        getServerIndexes() const;
    std::string                              getServerRoot() const;

    /*  Other Helper Functions  */
    bool    isServerValidAndReady( void );

private:

    unsigned long long                      _maxBodySize;
    int                                     _port;
    std::string                             _host;
    std::string                             _serverName;
    std::string                             _serverRoot;
    std::vector<std::string>                _serverIndexes;
    std::map<int, std::string>              _errorPages;
    std::pair<int, std::string>             _redirection;
    std::vector<location_data>              _locations;
};
#endif