/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:14:52 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 17:53:14 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

/*  LocationConfig Constructor  */
LocationConfig::LocationConfig() : _autoIndex(false), _autoUpload(false) {}
LocationConfig::LocationConfig(const std::string& path) : _autoIndex(false), _autoUpload(false), _path(path) {}


/*  LocationConfig Setters  */
void LocationConfig::setRoot( std::string const& root)
{
    this->_root = root;
}
void LocationConfig::setUploadPath( std::string const& uploadPath)
{
    this->_uploadPath = uploadPath;
}
void LocationConfig::setCgiPath( std::string const& cgiPath)
{
    this->_cgiPath = cgiPath;
}
void LocationConfig::setAutoIndex(bool autoIndex)
{
    this->_autoIndex = autoIndex;
}
void LocationConfig::setAutoUpload(bool autoUpload)
{
    this->_autoUpload = autoUpload;
}
void LocationConfig::setIndex( std::string const& index)
{
    this->_indexes.push_back(index);
}
void LocationConfig::setAllowedMethod( std::string const& method)
{
    this->_allowedMethods.push_back(method);
}

/*  LocationConfig Getters  */
bool    LocationConfig::getAutoIndex() const
{
    return _autoIndex;
}
bool    LocationConfig::getAutoUpload() const
{
    return _autoUpload;
}
std::string LocationConfig::getRoot() const
{
    return _root;
}
std::string LocationConfig::getPath() const
{
    return _path;
}
std::string LocationConfig::getUploadPath() const
{
    return _uploadPath;
}
std::string LocationConfig::getCgiPath() const
{
    return _cgiPath;
}
std::vector<std::string> LocationConfig::getIndexes() const
{
    return _indexes;
}
std::vector<std::string> LocationConfig::getAllowedMethods() const
{
    return _allowedMethods;
}

/*LocationCofig Helper Functions */
bool    LocationConfig::isEmpty() const
{
    if (_root.empty() && _indexes.size() < 1)
        return true;
    return false;
}
bool    LocationConfig::isLocationValidAndReady( void )
{
    if (_path.empty() || _root.empty() || !_indexes.size() || !_allowedMethods.size())
        return false;
    return true;
}
