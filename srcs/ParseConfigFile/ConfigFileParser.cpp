/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:13:37 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 18:04:01 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFileParser.hpp"

/*  ConfigFile Constructors  */
ConfigFileParser::ConfigFileParser ( void ) {}
ConfigFileParser::ConfigFileParser( std::string const& fileName) : _configFileName(fileName)
{
    std::string extensionToCheck = ".conf";
    if (!(fileName.length() >= extensionToCheck.length() &&
          fileName.compare(fileName.length() - extensionToCheck.length(), extensionToCheck.length(), extensionToCheck) == 0))
        _errorAndExit("A Config File Must End With a .conf Extension");
}
ConfigFileParser::~ConfigFileParser(void) {}


/*  ConfigFile Getters */
std::vector<ServerConfig> ConfigFileParser::getServers(void) const
{
    return _servers;
}


/*  ConfigFile Parsers  */
void ConfigFileParser::parseServersData()
{
    std::string                 line;
    std::string                 trimmedLine;
    std::vector<std::string>    tokens;
    bool                        serverEnded = false;
    bool                        isDefaultParsedBefore = false;

    /*  Opening The File    */
    std::ifstream _configFile(_configFileName.c_str());
    _isFileOpenedAndNotEmpty(_configFile);

    while (getline(_configFile, line))
    {
        if (!_isFileGoodToGo(line))
            break;
        trimmedLine = _removeExtraSpaces(line);
        if (_isLineEmptyOrComment(trimmedLine))
            continue;
        /*  When a Line Contain a Server    */
        if (!trimmedLine.empty() && trimmedLine == "server")
        {
            /*  Server object Init */
            ServerConfig currentConfig;

            serverEnded = false;
            getline(_configFile, line);
            if (!_isFileGoodToGo(line))
                break;
            if (_removeExtraSpaces(line) != "{")
                _errorAndExit(SERVERSYNTAXERROR);
            while (getline(_configFile, line))
            {
                /*  Starting To Read inside the server Here  */
                if (!_isFileGoodToGo(line))
                    _errorAndExit(READINSERVERGERROR);
                trimmedLine = _removeExtraSpaces(line);
                if (_isLineEmptyOrComment(trimmedLine))
                    continue;
                /*  PARSING DIRECTIVES */
                tokens = _tokenizerOfDirectives(trimmedLine);
                if (line.find("location") != std::string::npos)
                {
                    if (tokens[0] != "location")
                        _errorAndExit(LOCATIONNOTFOUNDERROR);
                    if (tokens.size() != 3)
                        _errorAndExit("Location Must An Argument Path");
                    if (tokens.back() != "{")
                        _errorAndExit(LOCATIONSYNTAXERROR);
                    /*  Init Location Object Here */
                    LocationConfig currentLocationConfig(tokens[1]);
                    while (getline(_configFile, line))
                    {
                        if (!_isFileGoodToGo(line))
                            _errorAndExit(READINLOCATIONERROR);
                        trimmedLine = _removeExtraSpaces(line);
                        if (_isLineEmptyOrComment(trimmedLine))
                            continue;
                        if (trimmedLine == "}")
                        {
                            if (currentLocationConfig.isEmpty())
                                _errorAndExit("Parsing the Location!");
                            if (!currentLocationConfig.isLocationValidAndReady())
                                _errorAndExit("Location Inside A Server Must Contain At Least: DefaultPath, Root, index, and At least 1 AllowedMethod");
                            currentConfig.addLocation(currentLocationConfig);
                            break;
                        }
                        _parseLocationDirectives(trimmedLine, currentLocationConfig);
                    }
                    continue;
                }
                else if (tokens[0] == "host" && currentConfig.getHost().empty())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'Host' directive must have a single Argument.");
                    currentConfig.setHost(_parseHost(tokens[1]));
                }
                else if (tokens[0] == "port" && !currentConfig.getListenPort())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'Port' directive must have a single Argument.");
                    currentConfig.setListenPort(_parsePort(tokens[1]));
                }
                else if (tokens[0] == "server_name" && currentConfig.getServerName().empty())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'server_name' directive must have a single argument.");
                    currentConfig.setServerName(tokens[1]);
                }
                else if (tokens[0] == "default_server" && !isDefaultParsedBefore)
                {
                    // must have a booleen
                    if (tokens.size() != 2)
                        _errorAndExit("'default_server' directive must have a single argument: on or off");
                    if (tokens[1] == "on")
                        currentConfig.setDefaultServer(true);
                    else if (tokens[1] == "off")
                        currentConfig.setDefaultServer(false);
                    else
                        _errorAndExit("cannot recognize the 'default_server' directive Arguments try {on || off}.");
                    isDefaultParsedBefore = true;
                }
                else if (tokens[0] == "error_page")
                {
                    if (tokens.size() != 3)
                        _errorAndExit("'error_page' directive must have two argument: errorNumber and errorPage");
                    currentConfig.addErrorPage(_stringToInt(tokens[1]), tokens[2]);
                }
                else if (tokens[0] == "client_max_body_size" && !currentConfig.getMaxBodySize())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'client_max_body_size' directive must have One argument: Size In Mb");
                    std::string sizeArgument = tokens[1];
                    if (sizeArgument[sizeArgument.size() - 1] != 'M')
                        _errorAndExit("Invalid format for 'client_max_body_size' directive. It should end with 'M'");
                    tokens[1].erase(tokens[1].size() - 1);
                    int tmpSize = _stringToInt(tokens[1]);
                    unsigned int maxSizeInBytes = tmpSize * 1024 * 1024;
                    currentConfig.setMaxBodySize(maxSizeInBytes);
                }
                else if (tokens[0] == "}")
                {
                    if (!currentConfig.isServerValidAndReady())
                        _errorAndExit("Server Must Contain At Least: DefaultPath, Root, Index and At least 1 AllowedMethod");
                    _servers.push_back(currentConfig);
                    serverEnded = true;
                    isDefaultParsedBefore = false;
                    break;
                }
                else
                    _errorAndExit(SECTIONSYNTAXERROR);
            }
            if (!serverEnded)
                _errorAndExit(SERVERBRACEERROR);
        }
        else
            _errorAndExit(FILEWITHOUTSERVER);
    }
    if (_servers.size() < 1)
        _errorAndExit(SERVERNOTFOUNDERROR);
    _configFile.close();
}
void ConfigFileParser::_parseLocationDirectives(std::string &trimmedLine, LocationConfig &currentLocationConfig)
{
    std::vector<std::string> tokens = _tokenizerOfDirectives(trimmedLine);

    if (tokens.empty())
        _errorAndExit("Cannote Parse Location Directives 'Empty Directive'");
    if (tokens[0] == "root" && currentLocationConfig.getRoot().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'root' directive must have a single argument.");
        currentLocationConfig.setRoot(tokens[1]);
    }
    else if (tokens[0] == "index" && !currentLocationConfig.getIndexes().size())
    {
        if (tokens.size() < 2)
            _errorAndExit("'index' directive must have arguments");
        for (size_t i = 1; i < tokens.size(); i++)
            currentLocationConfig.setIndex(tokens[i]);
    }
    else if (tokens[0] == "auto_index")
    {
        if (tokens.size() != 2)
            _errorAndExit("'auto_index' directive must have a single argument: on or off");
        if (tokens[1] == "on")
            currentLocationConfig.setAutoIndex(true);
        else if (tokens[1] == "off")
            currentLocationConfig.setAutoIndex(false);
        else
            _errorAndExit("cannot recognize the 'autoindex' directive Arguments try {on || off}.");
    }
    else if (tokens[0] == "auto_upload")
    {
        if (tokens.size() != 2)
            _errorAndExit("'auto_upload' directive must have a single argument: on or off");
        if (tokens[1] == "on")
            currentLocationConfig.setAutoUpload(true);
        else if (tokens[1] == "off")
            currentLocationConfig.setAutoUpload(false);
        else
            _errorAndExit("cannot recognize the 'auto_upload' directive Arguments try {on || off}.");
    }
    else if (tokens[0] == "upload_path" && currentLocationConfig.getUploadPath().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'upload_path' directive must have a single argument: path");
        currentLocationConfig.setUploadPath(tokens[1]);
    }
    else if (tokens[0] == "cgi_path" && currentLocationConfig.getCgiPath().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'cgi_path' directive must have a single argument: path");
        currentLocationConfig.setCgiPath(tokens[1]);
    }
    else if (tokens[0] == "allowed_methods" && !currentLocationConfig.getAllowedMethods().size())
    {
        if (tokens.size() > 4)
            _errorAndExit("'allowed_methods' directive must have Three Methonds Only");
        else if (tokens.size() < 2)
            _errorAndExit("'allowed_methods' directive must have at least One Methond");
        /* Parsing it */
        if (!_parseAllowedMethods(tokens))
            _errorAndExit("Invalid Method keyword");
        for (size_t i = 1; i < tokens.size(); i++)
            currentLocationConfig.setAllowedMethod(tokens[i]);
    }
    else
        _errorAndExit("Duplicate Or Unkown Type Of Directive inside Location");
}


/* ---------- Parsing Helper Functions ----------- */
//  Check if Line Empty Or Comment
bool ConfigFileParser::_isLineEmptyOrComment(std::string const &line)
{
    if (line.empty() || line[0] == '#' || line[0] == '\n')
        return true;
    return false;
}
//  Convert String To Int
int ConfigFileParser::_stringToInt( std::string const& input)
{
    std::istringstream iss(input);
    long value;

    iss >> value;

    if (iss.fail() || !iss.eof())
        _errorAndExit("Int: Invalid characters");
    if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
        _errorAndExit("int: Overflow/Underflow during conversion of an Int");
    int result = static_cast<int>(value);
    return result;
}
//  Check For Multiple Semicolone
void ConfigFileParser::_splitBySemicolon( std::string const& line)
{
    int semicoloneCount = 0;

    if (!line.empty())
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line[i] == ';')
                semicoloneCount++;
        }
    }
    if (semicoloneCount > 1)
        _errorAndExit("Duplicate Semicolons in a Directive Line.");
}
//  Iterate and remove Extra Spaces from a line 
std::string ConfigFileParser::_removeExtraSpaces( std::string const& line)
{
    std::string result;
    bool spaceFound = false;

    if (line.empty())
        return line;
    for (size_t i = 0; i < line.length(); ++i)
    {
        if (line[i] == ' ' || line[i] == '\t')
            spaceFound = true;
        else
        {
            if (spaceFound)
            {
                result += ' ';
                spaceFound = false;
            }
            result += line[i];
        }
    }

    if (result.empty())
        return result;
    result = result.substr(result.find_first_not_of(" "));
    result = result.substr(0, result.find_last_not_of(" ") + 1);

    return result;
}
// Tokrnize A line and give a meaning to every token (Also Check for Some Errors)
std::vector<std::string> ConfigFileParser::_tokenizerOfDirectives(std::string const &line)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    /*  Check if Line have multiple semicolone */
    _splitBySemicolon(line);

    /*  {} Braces Line check if Stands Alone at a line */
    if (!line.empty() && line.find("{") != std::string::npos && (line.find("{") + 1) < line.length())
        _errorAndExit("A '{' Brace Must Not Be Followed By Anything !");
    /*  Check if There is Something with }  in the same line */
    if (!line.empty() && line.find("}") != std::string::npos && (line.find("}") + 1) < line.length())
        _errorAndExit("A '}' Brace Must Not Be Followed By Anything !");

    while (iss >> token)
        tokens.push_back(token);
    if (tokens.empty())
        _errorAndExit(SECTIONSYNTAXERROR);

    /*  Check If Directive Ends With a Semicolone */
    if (!line.empty() && (tokens[0] != "location" && tokens[0] != "}" && tokens[0] != "{" && tokens[0] != "server") && line[line.length() - 1] != ';')
        _errorAndExit("A Directive Must End with A semicolone");

    /* Remove the Semicolone from the last Token To Make The Line ready*/
    if (!tokens[tokens.size() - 1].empty() && line[line.length() - 1] == ';')
        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
    return tokens;
}
// Check The Host Errors 
std::string ConfigFileParser::_parseHost(std::string const &line)
{
    std::istringstream iss(line);
    std::vector<std::string> parts;
    std::string token;

    while (std::getline(iss, token, '.'))
    {
        if (token.find_first_not_of("0123456789") == std::string::npos)
        {
            int num = _stringToInt(token);
            if (num >= 0 && num <= 255)
                parts.push_back(token);
            else
                _errorAndExit("Host Name Out Of Range Error");
        }
        else
            _errorAndExit("Invalid Digits in The Host Value");
    }
    if (parts.size() != 4)
        _errorAndExit("A host Must Have 4 parts");
    return line;
}
// Checking The Port Value Errors  
int ConfigFileParser::_parsePort(std::string const &line)
{
    std::istringstream iss(line);
    long value;

    iss >> value;

    if (iss.fail() || !iss.eof())
        _errorAndExit("Invalid characters in Port Value");
    if (value < 1 || value > 65535)
        _errorAndExit("Out Of Range Port Value");
    int result = static_cast<int>(value);
    return result;
}
// Check The Alloed Methods in a Location
bool ConfigFileParser::_parseAllowedMethods(std::vector<std::string> &tokens)
{
    if (!tokens.size())
        return false;

    std::set<std::string> knownAllowedMethods;
    bool valid = false;

    knownAllowedMethods.insert("GET");
    knownAllowedMethods.insert("POST");
    knownAllowedMethods.insert("DELETE");

    for (size_t i = 1; i < tokens.size(); i++)
    {
        if (knownAllowedMethods.find(tokens[i]) != knownAllowedMethods.end())
        {
            knownAllowedMethods.erase(tokens[i]);
            valid = true;
        }
        else
        {
            valid = false;
            break;
        }
    }
    if (!valid || knownAllowedMethods.size() == 3)
        return false;
    return true;
}


/* ------- File Error Handling  */
// check if the file opened sucessfully
void ConfigFileParser::_isFileOpenedAndNotEmpty(std::ifstream &configFile)
{
    if (!configFile.is_open())
        _errorAndExit("Failed to open Config File");
    bool is_empty = configFile.peek() == std::ifstream::traits_type::eof();
    if (is_empty)
        _errorAndExit("Empty Config File");
}
// check if the file is still good to run
bool ConfigFileParser::_isFileGoodToGo(std::string const &line)
{
    if (_configFile.fail())
        _errorAndExit(READINGERROR);
    if (line.empty() && _configFile.eof())
        return false;
    return true;
}


/*  ------- Error printer and exit handler ------- */
void ConfigFileParser::_errorAndExit(std::string const &error)
{
    std::cerr << "Error: " << error << std::endl;
    _exit(1);
}