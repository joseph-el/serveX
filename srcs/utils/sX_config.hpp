# if !defined(SX_COFIG_HPP)
# define SX_COFIG_HPP

# include "../core/serveX.hpp"

# define DEFAULT_CONF_PATH "conf/serveX.conf"


class serveX::sX_config {

    public:
    
        sX_config( std::string const& fileName = DEFAULT_CONF_PATH);
        ~sX_config( void );

};

#define READINGERROR "While Reading Config File..."
#define BRACESERROR "Mismatched braces '{}' found."
#define FILEWITHOUTSERVER "A config File Must start with a <server> without <>"

#define READINSERVERGERROR "While Reading Server Section..."
#define SERVERNOTFOUNDERROR "A file Must have at least one server"
#define SERVERSYNTAXERROR "A Server Block Must be followed by : {"
#define SERVERBRACEERROR "Unable to find the closing brace for the server : }"

#define LOCATIONNOTFOUNDERROR "'location' directive keyword must start with 'location'."
#define LOCATIONSIZEERROR "'location' directive must have a single path as argument and {"
#define LOCATIONSYNTAXERROR "'location' directive must end with '{'"
#define SECTIONSYNTAXERROR "A Section of a Config File Must Contain Valid And Not Duplicated Directives."
#define READINLOCATIONERROR "While Reading Location Section..."

# endif