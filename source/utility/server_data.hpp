#ifndef __SERVER_DATA_H__
#define __SERVER_DATA_H__

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

# include "server-core.hpp"

# define MAX_BODY_SIZE 5368709120
    
    /*
        server_data is a class that hold everything you need about a server configuration,
        and some helper functions to diplay them...
    */
using namespace std;

class   server_data {
public:

    /*  Constructors */
    server_data ( void );
    server_data ( const server_data& other );

    /* Operators */
    server_data &operator=( const server_data& other);

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
    void    setAutoIndex ( bool );
    void    setRedirection(int, const std::string& );
    void    setServerAllowedMethod ( int );


    /*  Getters */
    int                                      getListenPort() const;
    bool                                     getAutoIndex() const;
    unsigned long long                       getMaxBodySize() const;
    std::string                              getHost() const;
    std::string                              getServerName() const;
    const   std::map<int, std::string>&      getErrorPages() const;
    const   std::pair<int, std::string>&     getServerRedirection() const;
    const   std::vector<location_data>&      getLocations() const;
    const   std::vector<std::string>&        getServerIndexes() const;
    std::string                              getServerRoot() const;
    std::vector<int>                         getServerAllowedMethods() const;

    /*  Other Helper Functions  */
    bool    isServerValidAndReady( void );

    // added by joseph

    bool    ServerIsRedirective( void ) const ;
    bool    foundRoot( void ) const;
    
    typedef vector<location_data>::const_iterator Base;
    location_data* matchLocation(string);

private:

    unsigned long long                      _maxBodySize;
    int                                     _port;
    bool                                    _autoIndex;
    std::string                             _host;
    std::string                             _serverName;
    std::string                             _serverRoot;
    std::vector<std::string>                _serverIndexes;
    std::map<int, std::string>              _errorPages;
    std::pair<int, std::string>             _redirection;
    std::vector<location_data>              _locations;
    std::vector<int>                        _serverAllowedMethods;

};

# endif