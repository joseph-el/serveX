

<br />
<div align="center">


[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&size=30&duration=1000&pause=3000&background=FFFFFF00&center=true&vCenter=true&random=false&width=350&height=60&lines=serveX)](https://git.io/typing-svg)


  <p align="center">
    An flexible HTTP web server!
    <br />
    <a href="https://github.com/joseph-el/serveX/assets/80905157/d5446afd-2f66-46ad-a4ab-e53abcc41f8d"><strong>Explore the docs »</strong></a>
    <br />
    <br />
</div>


 ## About
``serveX`` is a HTTP web server like [nginx](https://en.wikipedia.org/wiki/Nginx) , meticulously crafted in C++17 by [@joseph-el](https://github.com/joseph-el) , [@tnaceur](https://github.com/tnaceur) and [@ELkhalil](https://github.com/ELkhalil)


## Overview

``serveX`` designed to provide a robust and versatile platform for handling web applications. The server is meticulously crafted to support a wide range of features, making it suitable for various web development scenarios 

## Features
 
- **HTTP Methods Support:** serveX supports all ``HTTP methods``, providing a versatile platform for handling various types of requests.
 
- **CGI Interpreter:** Execute Common Gateway Interface ``(CGI)`` scripts seamlessly, allowing dynamic content generation on the server.
 
- **Multiple CGI Scripts:** serveX can handle ``multiple CGI`` scripts simultaneously, enabling complex web applications and functionalities.
 
- **Cookies and Session Management:** Easily manage user ``sessions`` and store information using cookies, enhancing the interactivity and personalization of web applications.
 
- **Error Logging:** The server includes a high-level error ``logger`` that detects errors in configuration files, requests, and responses, providing valuable insights for debugging and maintenance.

## Configuration

### Optionner

We includes a optionner tool that allows you to fine-tune the server's behavior. Use the following command-line options to configure serveX according to your requirements:

```sh
  serveX         # run the server with the default config file: cfg/sx_config
  serveX -h      # Display help
  serveX -v      # Display the server version and exit
  serveX -t      # Test the server configuration and exit
  serveX -T      # Test configuration, dump it, and exit
  serveX -c custom_config.conf  # Set a custom configuration file
```
## syntax 
The serveX HTTP web server boasts an expressive and flexible configuration syntax
### Server Block
The server block serves as the encapsulating structure for the server configuration. It contains global server settings.
```cfg
server {
    listen              Host:Port;
    server_name         exampleName;
    client_max_body_size <Size>; 
}
```

### Location Block
The location block allows you to define configurations specific to different URI paths.

``` cfg
location <pathToLocation> {
    root               <path>;
    allowed_methods    <Methods...>;
    index              <indexes>...;
    upload_path        <Path>;
    cgi_path           <pathToCGI>;
    auto_index         <off/on>;
    return             <status>    <PathToRedirection>;
}
```

## Example Configuration

```cfg
server {
    listen              3333;
    server_name         serverX.com;
    client_max_body_size 500M;

    location / {
        allowed_methods GET HEAD PATCH;
        root             home;
        index            index.html;
    }

    location 42home {
        root             .;
        allowed_methods GET HEAD;
        return           301 https://42.fr/en/homepage/;
    }

    location template {
        root             .;
        index            index.html;
        allowed_methods GET;
    }

    location youtube.com {
        allowed_methods GET;
        root             .;
        return           301 https://www.youtube.com/channel/UCa8CyDeTWLzoP4hvdQ5_l6w;
    }

    location upload {
        root             ./;
        index            index.html;
        allowed_methods GET POST PUT PATCH;
        upload_path      /goinfre/yoel-idr;
    }
}
```
### Usage
#### clone repository
```sh
git clone https://github.com/joseph-el/serveX.git
```
#### config file and run
```sh
- setup the a config file
make ; ./serveX -c path_of_config.cfg
```

## Acknowledgments

Special thanks to [@tnaceur](https://github.com/tnaceur) and [@ELkhalil](https://github.com/ELkhalil) for their valuable contributions to the serveX project.



