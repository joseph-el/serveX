/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:12:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/09 18:12:39 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <vector>

    /*
        LocationConfig is a class that hold everything you need about a location inside
        a server configuration file...
    */
class LocationConfig
{
public:

    /*  Constructors */
    LocationConfig();
    LocationConfig(const std::string& path);

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
