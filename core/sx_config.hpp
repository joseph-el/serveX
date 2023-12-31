# ifndef __CONFIG_H__
# define __CONFIG_H__

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <limits>
#include <set>
#include <string.h>
#include <math.h>

# include "serveX-core.hpp"

# ifndef DEFAULT_CONF
    # define DEFAULT_CONF ""
# endif

# ifndef SERVER_PATH
    # define SERVER_PATH ""
# endif

using namespace std;

class server_data;
class location_data;

class config
{
    public:

        string              _configFileName;
        mutable ifstream    _configFile;

        /*  config Constructors */
        config( string const& fileName = DEFAULT_CONF);
        ~config( void );

        /*  config Member Functions */
        void    print() const;
        void    disp() const;
        bool    successful( void );
        void    parseServersData();
        void    setPath( std::string const&  );

        /*  config Getters */
        std::vector<server_data>   getServers( void ) const;

    private:


        vector<server_data>     _servers;
        /*  Parsing Data Functions  */
        void    _parseLocationDirectives(std::string &, location_data & , short);

        /*  Error Displayer with Exit */
        void    _errorAndExit(std::string const& , short);

        /*  Parsing Helper Functions */
        void                     _splitBySemicolon( std::string const& , short);
        std::string              _removeExtraSpaces(std::string  const& );
        bool                     _isLineEmptyOrComment(std::string  const& );
        int                      _stringToInt( std::string const& , short);
        std::string              _parseHost(std::string const& , short &);
        int                      _parsePort(std::string const& , short);
        bool                     _parseAllowedMethods( std::vector<std::string>& );
        bool                     _isPort( std::string const& );
        void                     _extractHostAndPort ( std::string const&, short, server_data& );
        void                     _checkAndCleanDuplicates( void );

        /*  FileStream Releted Functions  */
        bool                     _isFileGoodToGo( std::string const& , short);

        /*  Parsing Directives Functions */
        std::vector<std::string> _tokenizerOfDirectives( std::string const& , short);
};

extern config MainContext;

#define MAX_METHOD_SIZE 10
#define CHECK_CONF_EXTENSION(fileName) \
    do { \
        string extension = ".cfg"; \
        if (fileName.length() < extension.length() or \
            fileName.substr(fileName.length() - extension.length()) != extension) \
            cerr << ( NAME " : " "a config file must end with a .cfg extension\n"), \
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