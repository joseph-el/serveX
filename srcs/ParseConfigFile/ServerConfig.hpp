/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:28:35 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 18:12:18 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "LocationConfig.hpp"

    /*
        ServerConfig is a class that hold everything you need about a server configuration,
        and some helper functions to diplay them...
    */

class   ServerConfig
{
public:

    /*  Constructors */
    ServerConfig ( void );

    /* Add to vectors */
    void    addErrorPage( int errorCode, const std::string& errorPage );
    void    addLocation( LocationConfig const& locationObj );

    /*  Setters */
    void    setListenPort(int port);
    void    setHost(std::string const& host);
    void    setServerName( std::string const& serverName);
    void    setDefaultServer(bool isDefault);
    void    setMaxBodySize(int sizeInBytes);

    /*  Getters */
    int                                         getListenPort() const;
    int                                         getMaxBodySize() const;
    bool                                        isDefaultServer() const;
    std::string                                 getHost() const;
    std::string                                 getServerName() const;
    const   std::map<int, std::string>&         getErrorPages() const;
    const   std::vector<LocationConfig>&        getLocations() const;

    /*  Other Helper Functions  */
    void    printServerConfig() const;
    bool    isServerValidAndReady( void );
private:

    int                                 _maxBodySize;
    bool                                _isDefaultServer;
    int                                 _port;
    std::string                         _host;
    std::string                         _serverName;
    std::map<int, std::string>          _errorPages;
    std::vector<LocationConfig>         _locations;
    
};
#endif
