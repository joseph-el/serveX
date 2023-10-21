#ifndef __LOCATION_DATA_H__
#define __LOCATION_DATA_H__

# include <iostream>
# include <vector>
# include "server-core.hpp"

# ifndef SERVER_PATH
    # define SERVER_PATH "/User/joseph/serveX"
# endif

enum METHODS {
    GET = 1 << 1,
    POST = 1 << 2,
    DELETE = 1 << 3,
    UNKNOWN_MT = 1 << 4
};

using namespace std;

class location_data
{
public:

    /*  Constructors */
    location_data();
    location_data(const std::string& path);
    location_data ( const location_data& );
    /* Operators */
    location_data &operator=( const location_data& other);

    /*  Setters */
    void                        setRoot( std::string const& );
    void                        setAutoIndex( bool );
    void                        setIsUpload( bool );
    void                        setIsEmptyLocation( bool );
    void                        setIndex ( std::string const& );
    void                        setAllowedMethod ( int );
    void                        setUploadPath ( std::string const& );
    void                        setCgiPath ( std::string const& );
    void                        setRedirection( int, const std::string& );

    /*  Getters */
    bool                                  getAutoIndex() const;
    bool                                  getIsUpload() const;
    bool                                  getIsEmptyLocation() const;
    std::string                           getRoot();
    std::string                           getPath() const;
    std::string                           getUploadPath() const;
    const std::string&                     getCgiPath() const;
    const std::vector<std::string>&       getIndexes() const;
    std::vector<int>                      getAllowedMethods() const;
    const   std::pair<int, std::string>&  getlocationRedirections() const;

    /*  helper Methods  */
    bool                        isEmpty() const;
    bool                        isLocationValidAndReady( void );


    // added by Joseph
    bool                        NotallowMethod(METHODS &_mth) {
        return (find(_allowedMethods.begin(), _allowedMethods.end(), _mth) == _allowedMethods.end());
    }

    bool    LocationIsRedirective( void ) {
        return _redirection.first > 0 && !_redirection.second.empty();
    }
    location_data(string root, const vector<string> &Indexs, const vector<int> &allowMethods, bool autoIndx) {
        _autoIndex = autoIndx;
        _root = root;
        _indexes = Indexs;
        _isEmptyLocation = false;
        _allowedMethods = allowMethods;
    }

private:
    bool                         _autoIndex;
    bool                         _isUpload;
    bool                         _isEmptyLocation;
    std::string                  _path;
    std::string                  _root;
    std::string                  _uploadPath;
    std::string                  _cgiPath;
    std::vector<std::string>     _indexes;
    std::vector<int>             _allowedMethods;
    std::pair<int, std::string>  _redirection;
};


# endif
