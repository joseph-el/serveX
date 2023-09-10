/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:54:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 18:17:07 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEPARSER_HPP
#define CONFIGFILEPARSER_HPP

    /*
        ConfigFileParser is a general class responsible for parsing a config file
        and extracting it's data and returning a vector of server, it follows a predefined
        grammar syntax:
            <server>
            {
                <directive> <argument>;
                <directive> <argument>;
                <location> <path> {
                    <directive> <argument>;
                    <directive> <argument>;
                }
            }
        anything other than this will be considered as an error
    */

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <limits>
#include <set>
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

class ConfigFileParser
{
public:

    /*  ConfigFileParser Constructors */
    ConfigFileParser( std::string const& fileName);
    ~ConfigFileParser( void );

    /*  ConfigFileParser Member Functions */
    void parseServersData();

    /*  ConfigFileParser Getters */
    std::vector<ServerConfig>   getServers( void ) const;

private:
    ConfigFileParser ( void );

    std::string                 _configFileName;
    std::ifstream               _configFile;
    std::vector<ServerConfig>   _servers;

    /*  Parsing Data Functions  */
    void    _parseLocationDirectives(std::string &, LocationConfig & );
    
    /*  Error Displayer with Exit */
    void    _errorAndExit(std::string const& );

    /*  Parsing Helper Functions */
    void                     _splitBySemicolon( std::string const& );
    std::string              _removeExtraSpaces(std::string  const& );
    bool                     _isLineEmptyOrComment(std::string  const& );
    int                      _stringToInt( std::string const& );
    std::string              _parseHost(std::string const& );
    int                      _parsePort(std::string const& );
    bool                     _parseAllowedMethods( std::vector<std::string>& );

    /*  FileStream Releted Functions  */
    void                     _isFileOpenedAndNotEmpty( std::ifstream& );
    bool                     _isFileGoodToGo( std::string const& );

    /*  Parsing Directives Functions */
    std::vector<std::string> _tokenizerOfDirectives( std::string const& );

};

/*  General Syntax Errors   */
#define READINGERROR "While Reading Config File..."
#define BRACESERROR "Mismatched braces '{}' found."
#define FILEWITHOUTSERVER "A config File Must start with a <server> without <>"

/*  Server Syntax Errors   */
#define READINSERVERGERROR "While Reading Server Section..."
#define SERVERNOTFOUNDERROR "A file Must have at least one server"
#define SERVERSYNTAXERROR "A Server Block Must be followed by : {"
#define SERVERBRACEERROR "Unable to find the closing brace for the server : }"

/*  Location Syntax Errors */
#define LOCATIONNOTFOUNDERROR "'location' directive keyword must start with 'location'."
#define LOCATIONSIZEERROR "'location' directive must have a single path as argument and {"
#define LOCATIONSYNTAXERROR "'location' directive must end with '{'"
#define SECTIONSYNTAXERROR "A Section of a Config File Must Contain Valid And Not Duplicated Directives."
#define READINLOCATIONERROR "While Reading Location Section..."

#endif