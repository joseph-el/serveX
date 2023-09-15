#include "sX_location_data.hpp"

/*  Sx_location_data Constructor  */
Sx_location_data::Sx_location_data() : _autoIndex(false), _autoUpload(false) {}
Sx_location_data::Sx_location_data(const std::string& path) : _autoIndex(false), _autoUpload(false), _path(path) {}


/*  Sx_location_data Setters  */
void Sx_location_data::setRoot( std::string const& root)
{
    this->_root = root;
}
void Sx_location_data::setUploadPath( std::string const& uploadPath)
{
    this->_uploadPath = uploadPath;
}
void Sx_location_data::setCgiPath( std::string const& cgiPath)
{
    this->_cgiPath = cgiPath;
}
void Sx_location_data::setAutoIndex(bool autoIndex)
{
    this->_autoIndex = autoIndex;
}
void Sx_location_data::setAutoUpload(bool autoUpload)
{
    this->_autoUpload = autoUpload;
}
void Sx_location_data::setIndex( std::string const& index)
{
    this->_indexes.push_back(index);
}
void Sx_location_data::setAllowedMethod( std::string const& method)
{
    this->_allowedMethods.push_back(method);
}

/*  Sx_location_data Getters  */
bool    Sx_location_data::getAutoIndex() const
{
    return _autoIndex;
}
bool    Sx_location_data::getAutoUpload() const
{
    return _autoUpload;
}
std::string Sx_location_data::getRoot() const
{
    return _root;
}
std::string Sx_location_data::getPath() const
{
    return _path;
}
std::string Sx_location_data::getUploadPath() const
{
    return _uploadPath;
}
std::string Sx_location_data::getCgiPath() const
{
    return _cgiPath;
}
std::vector<std::string> Sx_location_data::getIndexes() const
{
    return _indexes;
}
std::vector<std::string> Sx_location_data::getAllowedMethods() const
{
    return _allowedMethods;
}

/*LocationCofig Helper Functions */
bool    Sx_location_data::isEmpty() const
{
    if (_root.empty() && _indexes.size() < 1)
        return true;
    return false;
}
bool    Sx_location_data::isLocationValidAndReady( void )
{
    if (_path.empty() || _root.empty() || !_indexes.size() || !_allowedMethods.size())
        return false;
    return true;
}