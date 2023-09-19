
#ifndef SX_LOCATION_DATA_HPP
#define SX_LOCATION_DATA_HPP

#include <string>
#include <vector>

    /*
        Sx_location_data is a class that hold data you need to know about 
        a location inside a server configuration file...
    */
class Sx_location_data
{
public:

    /*  Constructors */
    Sx_location_data();
    Sx_location_data(const std::string& path);

    /*  Setters */
    void                        setRoot( std::string const& );
    void                        setAutoIndex( bool );
    void                        setAutoUpload( bool );
    void                        setIndex ( std::string const& );
    void                        setAllowedMethod ( std::string const& );
    void                        setUploadPath ( std::string const& );
    void                        setCgiPath ( std::string const& );

    /*  Getters */
    bool                        getAutoIndex() const;
    bool                        getAutoUpload() const;
    std::string                 getRoot() const;
    std::string                 getPath() const;
    std::string                 getUploadPath() const;
    std::string                 getCgiPath() const;
    std::vector<std::string>    getIndexes() const;
    std::vector<std::string>    getAllowedMethods() const;

    /*  helper Methods  */
    bool                        isEmpty() const;
    bool                        isLocationValidAndReady( void );

private:
    bool                        _autoIndex;
    bool                        _autoUpload;
    std::string                 _path;
    std::string                 _root;
    std::string                 _uploadPath;
    std::string                 _cgiPath;
    std::vector<std::string>    _indexes;
    std::vector<std::string>    _allowedMethods;
};

#endif