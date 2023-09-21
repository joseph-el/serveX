#include "config.hpp"

config MainContext;

/*  config Constructors  */

config::config( std::string const& fileName) 
{
    setPath(fileName);
}

bool config::successful( void )
{
    try {
        parseServersData();
    }
    catch (bool) {
        return false;
    }
    return true;
}

void config::setPath( std::string const& fileName )  
{
    CHECK_CONF_EXTENSION(fileName);
    _configFile.close();
	_configFile.open(fileName, ios::in);
	if (!_configFile.good()) {
		cerr << NAME ": [emerg] " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
	_configFileName = fileName;
}

config::~config(void) 
{
    _configFile.close();
}

/*  config Getters */
std::vector<server_data> config::getServers(void) const
{
    return _servers;
}

/*  config Parsers  */
void config::parseServersData()
{
    std::string                 line;
    std::string                 trimmedLine;
    std::vector<std::string>    tokens;
    bool                        serverEnded = false;
    bool                        isDefaultParsedBefore = false;
    short                       lineNumber = 0;
    /*  Opening The File    */
    // std::ifstream _configFile(_configFileName.c_str());
    // _isFileOpenedAndNotEmpty(_configFile);

    for (; getline(_configFile, line); lineNumber++)
    {
        if (!_isFileGoodToGo(line, lineNumber))
            break;
        trimmedLine = _removeExtraSpaces(line);
        if (_isLineEmptyOrComment(trimmedLine))
            continue;
        /*  When a Line Contain a Server    */
        if (!trimmedLine.empty() && trimmedLine == "server")
        {
            /*  Server object Init */
            server_data currentConfig;

            serverEnded = false;
            getline(_configFile, line);
            if (!_isFileGoodToGo(line, lineNumber))
                break;
            if (_removeExtraSpaces(line) != "{")
                _errorAndExit(SERVERSYNTAXERROR, lineNumber);
            for (;getline(_configFile, line);lineNumber++)
            {
                /*  Starting To Read inside the server Here  */
                if (!_isFileGoodToGo(line, lineNumber))
                    _errorAndExit(READINSERVERGERROR, lineNumber);
                trimmedLine = _removeExtraSpaces(line);
                if (_isLineEmptyOrComment(trimmedLine))
                    continue;
                /*  PARSING DIRECTIVES */
                tokens = _tokenizerOfDirectives(trimmedLine, lineNumber);
                if (line.find("location") != std::string::npos)
                {
                    if (tokens[0] != "location")
                        _errorAndExit(LOCATIONNOTFOUNDERROR, lineNumber);
                    if (tokens.size() != 3)
                        _errorAndExit("Location Must An Argument Path", lineNumber);
                    if (tokens.back() != "{")
                        _errorAndExit(LOCATIONSYNTAXERROR, lineNumber);
                    /*  Init Location Object Here */
                    location_data currentLocationConfig(tokens[1]);
                    for (;getline(_configFile, line);lineNumber++)
                    {
                        if (!_isFileGoodToGo(line, lineNumber))
                            _errorAndExit(READINLOCATIONERROR, lineNumber);
                        trimmedLine = _removeExtraSpaces(line);
                        if (_isLineEmptyOrComment(trimmedLine))
                            continue;
                        if (trimmedLine == "}")
                        {
                            if (currentLocationConfig.isEmpty())
                                _errorAndExit("Parsing the Location!", lineNumber);
                            if (!currentLocationConfig.isLocationValidAndReady())
                                _errorAndExit("Location Inside A Server Must Contain At Least: DefaultPath, Root, index, and At least 1 AllowedMethod", lineNumber);
                            currentConfig.addLocation(currentLocationConfig);
                            break;
                        }
                        _parseLocationDirectives(trimmedLine, currentLocationConfig, lineNumber);
                    }
                    continue;
                }
                else if (tokens[0] == "host" && currentConfig.getHost().empty())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'Host' directive must have a single Argument.", lineNumber);
                    currentConfig.setHost(_parseHost(tokens[1], lineNumber));
                }
                else if (tokens[0] == "port" && !currentConfig.getListenPort())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'Port' directive must have a single Argument.", lineNumber);
                    currentConfig.setListenPort(_parsePort(tokens[1], lineNumber));
                }
                else if (tokens[0] == "server_name" && currentConfig.getServerName().empty())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'server_name' directive must have a single argument.", lineNumber);
                    currentConfig.setServerName(tokens[1]);
                }
                else if (tokens[0] == "default_server" && !isDefaultParsedBefore)
                {
                    // must have a booleen
                    if (tokens.size() != 2)
                        _errorAndExit("'default_server' directive must have a single argument: on or off", lineNumber);
                    if (tokens[1] == "on")
                        currentConfig.setDefaultServer(true);
                    else if (tokens[1] == "off")
                        currentConfig.setDefaultServer(false);
                    else
                        _errorAndExit("cannot recognize the 'default_server' directive Arguments try {on || off}.", lineNumber);
                    isDefaultParsedBefore = true;
                }
                else if (tokens[0] == "error_page")
                {
                    if (tokens.size() != 3)
                        _errorAndExit("'error_page' directive must have two argument: errorNumber and errorPage", lineNumber);
                    currentConfig.addErrorPage(_stringToInt(tokens[1], lineNumber), tokens[2]);
                }
                else if (tokens[0] == "client_max_body_size" && !currentConfig.getMaxBodySize())
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'client_max_body_size' directive must have One argument: Size In Mb", lineNumber);
                    std::string sizeArgument = tokens[1];
                    if (sizeArgument[sizeArgument.size() - 1] != 'M')
                        _errorAndExit("Invalid format for 'client_max_body_size' directive. It should end with 'M'", lineNumber);
                    tokens[1].erase(tokens[1].size() - 1);
                    int tmpSize = _stringToInt(tokens[1], lineNumber);
                    unsigned int maxSizeInBytes = tmpSize * 1024 * 1024;
                    currentConfig.setMaxBodySize(maxSizeInBytes);
                }
                else if (tokens[0] == "}")
                {
                    if (!currentConfig.isServerValidAndReady())
                        _errorAndExit("Server Must Contain At Least: DefaultPath, Root, Index and At least 1 AllowedMethod",lineNumber);
                    _servers.push_back(currentConfig);
                    serverEnded = true;
                    isDefaultParsedBefore = false;
                    break;
                }
                else
                    _errorAndExit(SECTIONSYNTAXERROR, lineNumber);
            }
            if (!serverEnded)
                _errorAndExit(SERVERBRACEERROR, lineNumber);
        }
        else
            _errorAndExit(FILEWITHOUTSERVER, lineNumber);
    }
    if (_servers.size() < 1)
        _errorAndExit(SERVERNOTFOUNDERROR, lineNumber);
}

void config::_parseLocationDirectives(std::string &trimmedLine, location_data &currentLocationConfig, short lineNumber)
{
    std::vector<std::string> tokens = _tokenizerOfDirectives(trimmedLine, lineNumber);

    if (tokens.empty())
        _errorAndExit("Cannote Parse Location Directives 'Empty Directive'", lineNumber);
    if (tokens[0] == "root" && currentLocationConfig.getRoot().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'root' directive must have a single argument.", lineNumber);
        currentLocationConfig.setRoot(tokens[1]);
    }
    else if (tokens[0] == "index" && !currentLocationConfig.getIndexes().size())
    {
        if (tokens.size() < 2)
            _errorAndExit("'index' directive must have arguments", lineNumber);
        for (size_t i = 1; i < tokens.size(); i++)
            currentLocationConfig.setIndex(tokens[i]);
    }
    else if (tokens[0] == "auto_index")
    {
        if (tokens.size() != 2)
            _errorAndExit("'auto_index' directive must have a single argument: on or off", lineNumber);
        if (tokens[1] == "on")
            currentLocationConfig.setAutoIndex(true);
        else if (tokens[1] == "off")
            currentLocationConfig.setAutoIndex(false);
        else
            _errorAndExit("cannot recognize the 'autoindex' directive Arguments try {on || off}.", lineNumber);
    }
    else if (tokens[0] == "auto_upload")
    {
        if (tokens.size() != 2)
            _errorAndExit("'auto_upload' directive must have a single argument: on or off", lineNumber);
        if (tokens[1] == "on")
            currentLocationConfig.setAutoUpload(true);
        else if (tokens[1] == "off")
            currentLocationConfig.setAutoUpload(false);
        else
            _errorAndExit("cannot recognize the 'auto_upload' directive Arguments try {on || off}.", lineNumber);
    }
    else if (tokens[0] == "upload_path" && currentLocationConfig.getUploadPath().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'upload_path' directive must have a single argument: path", lineNumber);
        currentLocationConfig.setUploadPath(tokens[1]);
    }
    else if (tokens[0] == "cgi_path" && currentLocationConfig.getCgiPath().empty())
    {
        if (tokens.size() != 2)
            _errorAndExit("'cgi_path' directive must have a single argument: path", lineNumber);
        currentLocationConfig.setCgiPath(tokens[1]);
    }
    else if (tokens[0] == "allowed_methods" && !currentLocationConfig.getAllowedMethods().size())
    {
        if (tokens.size() > 4)
            _errorAndExit("'allowed_methods' directive must have Three Methonds Only", lineNumber);
        else if (tokens.size() < 2)
            _errorAndExit("'allowed_methods' directive must have at least One Methond", lineNumber);
        /* Parsing it */
        if (!_parseAllowedMethods(tokens))
            _errorAndExit("Invalid Method keyword", lineNumber);
        for (size_t i = 1; i < tokens.size(); i++)
            currentLocationConfig.setAllowedMethod(tokens[i]);
    }
    else
        _errorAndExit("Duplicate Or Unkown Type Of Directive inside Location", lineNumber);
}

/* ---------- Parsing Helper Functions ----------- */
//  Check if Line Empty Or Comment
bool config::_isLineEmptyOrComment(std::string const &line)
{
    if (line.empty() || line[0] == '#' || line[0] == '\n')
        return true;
    return false;
}
//  Convert String To Int

int config::_stringToInt( std::string const& input, short lineNumber)
{
    std::istringstream iss(input);
    long value;

    iss >> value;

    if (iss.fail() || !iss.eof())
        _errorAndExit("Int: Invalid characters", lineNumber);
    if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
        _errorAndExit("int: Overflow/Underflow during conversion of an Int", lineNumber);
    int result = static_cast<int>(value);
    return result;
}
//  Check For Multiple Semicolone

void config::_splitBySemicolon( std::string const& line, short lineNumber)
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
        _errorAndExit("Duplicate Semicolons in a Directive Line.", lineNumber);
}
//  Iterate and remove Extra Spaces from a line 

std::string config::_removeExtraSpaces( std::string const& line)
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

std::vector<std::string> config::_tokenizerOfDirectives(std::string const &line, short lineNumber)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    /*  Check if Line have multiple semicolone */
    _splitBySemicolon(line, lineNumber);

    /*  {} Braces Line check if Stands Alone at a line */
    if (!line.empty() && line.find("{") != std::string::npos && (line.find("{") + 1) < line.length())
        _errorAndExit("A '{' Brace Must Not Be Followed By Anything !", lineNumber);
    /*  Check if There is Something with }  in the same line */
    if (!line.empty() && line.find("}") != std::string::npos && (line.find("}") + 1) < line.length())
        _errorAndExit("A '}' Brace Must Not Be Followed By Anything !", lineNumber);

    while (iss >> token)
        tokens.push_back(token);
    if (tokens.empty())
        _errorAndExit(SECTIONSYNTAXERROR, lineNumber);

    /*  Check If Directive Ends With a Semicolone */
    if (!line.empty() && (tokens[0] != "location" && tokens[0] != "}" && tokens[0] != "{" && tokens[0] != "server") && line[line.length() - 1] != ';')
        _errorAndExit("A Directive Must End with A semicolone", lineNumber);

    /* Remove the Semicolone from the last Token To Make The Line ready*/
    if (!tokens[tokens.size() - 1].empty() && line[line.length() - 1] == ';')
        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
    return tokens;
}
// Check The Host Errors 

std::string config::_parseHost(std::string const &line, short &lineNumber)
{
    std::istringstream iss(line);
    std::vector<std::string> parts;
    std::string token;

    for (; getline(iss, token, '.'); lineNumber++)
    {
        if (token.find_first_not_of("0123456789") == std::string::npos)
        {
            int num = _stringToInt(token, lineNumber);
            if (num >= 0 && num <= 255)
                parts.push_back(token);
            else
                _errorAndExit("Host Name Out Of Range Error", lineNumber);
        }
        else
            _errorAndExit("Invalid Digits in The Host Value", lineNumber);
    }
    if (parts.size() != 4)
        _errorAndExit("A host Must Have 4 parts", lineNumber);
    return line;
}
// Checking The Port Value Errors  

int config::_parsePort(std::string const &line, short lineNumber)
{
    std::istringstream iss(line);
    long value;

    iss >> value;

    if (iss.fail() || !iss.eof())
        _errorAndExit("Invalid characters in Port Value", lineNumber);
    if (value < 1 || value > 65535)
        _errorAndExit("Out Of Range Port Value", lineNumber);
    int result = static_cast<int>(value);
    return result;
}
// Check The Alloed Methods in a Location

bool config::_parseAllowedMethods(std::vector<std::string> &tokens)
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


bool config::_isFileGoodToGo(std::string const &line, short lineNumber)
{
    if (_configFile.fail())
        _errorAndExit(READINGERROR, lineNumber);
    if (line.empty() && _configFile.eof())
        return false;
    return true;
}

/*  ------- Error printer and exit handler ------- */
void config::_errorAndExit(std::string const &error, short lineNumber)
{
    cerr << NAME ": [emerg] " + error + " in " + _configFileName + ":" << to_string(lineNumber) << endl;
    throw false;
}

/*  Display Current Servers Data    */
void    config::disp() const
{
    string configFile;
    _configFile.clear();
    _configFile.seekg(0, std::ios::beg);
    getline(_configFile, configFile, (char)0);
    cerr << configFile;
}