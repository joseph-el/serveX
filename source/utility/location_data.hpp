
#ifndef _LOCATION_DATA_H_
#define _LOCATION_DATA_H_

#include <string>
#include <vector>
#include <utility>

    /*
        location_data is a class that hold data you need to know about 
        a location inside a server configuration file...
    */
class location_data
{
public:

    /*  Constructors */
    location_data();
    location_data(const std::string& path);

    /*  Setters */
    void                        setRoot( std::string const& );
    void                        setAutoIndex( bool );
    void                        setAutoUpload( bool );
    void                        setIsEmptyLocation( bool );
    void                        setIndex ( std::string const& );
    void                        setAllowedMethod ( int );
    void                        setUploadPath ( std::string const& );
    void                        setCgiPath ( std::string const& );
    void                        setRedirection( int, const std::string& );

    /*  Getters */
    bool                                  getAutoIndex() const;
    bool                                  getAutoUpload() const;
    bool                                  getIsEmptyLocation() const;
    std::string                           getRoot() const;
    std::string                           getPath() const;
    std::string                           getUploadPath() const;
    std::string                           getCgiPath() const;
    std::vector<std::string>              getIndexes() const;
    std::vector<int>                      getAllowedMethods() const;
    const   std::pair<int, std::string>&  getlocationRedirections() const;

    /*  helper Methods  */
    bool                        isEmpty() const;
    bool                        isLocationValidAndReady( void );

private:
    bool                         _autoIndex;
    bool                         _autoUpload;
    bool                         _isEmptyLocation;
    std::string                  _path;
    std::string                  _root;
    std::string                  _uploadPath;
    std::string                  _cgiPath;
    std::vector<std::string>     _indexes;
    std::vector<int>             _allowedMethods;
    std::pair<int, std::string>  _redirection;
};

#endif