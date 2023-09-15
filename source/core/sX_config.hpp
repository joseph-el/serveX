# if !defined(SX_COFIG_HPP)
# define SX_COFIG_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <limits>
#include <set>

#include "../utils/sX_server_data.hpp"   // waiting to link by makefile
#include "../utils/sX_location_data.hpp"
# include "sX_optioneer.hpp"

# define DEFAULT_CONF   "/Users/joseph/Desktop/serveX/conf/serveX.conf"
# define DEFAULT_ERROR  "/Users/joseph/Desktop/serveX/logs/error.conf"
# define DEFAULT_ACCESS "/Users/joseph/Desktop/serveX/logs/access.conf"

using namespace std;

class serveX_config
{
    public:

        string              _configFileName;
        mutable ifstream    _configFile;

        /*  serveX_config Constructors */
        serveX_config( string const& fileName = DEFAULT_CONF);
        ~serveX_config( void );

        /*  serveX_config Member Functions */
        void    disp() const;
        bool    successful( void );
        void    parseServersData();
        void    setPath( std::string const&  );

        /*  serveX_config Getters */
        std::vector<Sx_server_data>   getServers( void ) const;

    private:

        vector<Sx_server_data>     _servers;

        /*  Parsing Data Functions  */
        void    _parseLocationDirectives(std::string &, Sx_location_data & , short);

        /*  Error Displayer with Exit */
        void    _errorAndExit(std::string const& , short);

        /*  Parsing Helper Functions */
        void                     _splitBySemicolon( std::string const& , short);
        std::string              _removeExtraSpaces(std::string  const& );
        bool                     _isLineEmptyOrComment(std::string  const& );
        int                      _stringToInt( std::string const& , short);
        std::string              _parseHost(std::string const& , short);
        int                      _parsePort(std::string const& , short);
        bool                     _parseAllowedMethods( std::vector<std::string>& );

        /*  FileStream Releted Functions  */
        // void                     _isFileOpenedAndNotEmpty( std::ifstream& );
        bool                     _isFileGoodToGo( std::string const& , short);

        /*  Parsing Directives Functions */
        std::vector<std::string> _tokenizerOfDirectives( std::string const& , short);
};

extern serveX_config sX_config;

#define CHECK_CONF_EXTENSION(fileName) \
    do { \
        string extension = ".conf"; \
        if (fileName.length() < extension.length() or \
            fileName.substr(fileName.length() - extension.length()) != extension) \
            cerr << "serveX : A Config File Must End With a .conf Extension\n", \
            exit(EXIT_FAILURE); \
    } while (false)

/*  General Syntax Errors   */
#define READINGERROR "while reading config file..."
#define BRACESERROR "mismatched braces '{}' found."
#define FILEWITHOUTSERVER "a config file must start with a <server> without <>"

/*  Server Syntax Errors   */
#define READINSERVERGERROR "while reading server section..."
#define SERVERNOTFOUNDERROR "a file must have at least one server"
#define SERVERSYNTAXERROR "a Server Block Must be followed by : {"
#define SERVERBRACEERROR "unable to find the closing brace for the server : }"

/*  Location Syntax Errors */
#define LOCATIONNOTFOUNDERROR "'location' directive keyword must start with 'location'."
#define LOCATIONSIZEERROR "'location' directive must have a single path as argument and {"
#define LOCATIONSYNTAXERROR "'location' directive must end with '{'"
#define SECTIONSYNTAXERROR "a Section of a Config File Must Contain Valid And Not Duplicated Directives."
#define READINLOCATIONERROR "while Reading Location Section..."

#endif