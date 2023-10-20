# ifndef __SERVER_H__
# define __SERVER_H__

# include <cstdio>
# include <sys/select.h>

# include "location_data.hpp"
# include "server_data.hpp"
# include "config.hpp"


# include "socket.hpp"
# include "optioneer.hpp"

# include "time.hpp"
# include "templates_helper.hpp"
# include "filesManipulation.hpp"
# include "StringManipulation.hpp"

# include "cgi.hpp"
# include "headers.hpp"
# include "requestBody.hpp"
# include "request.hpp"
# include "response.hpp"
# include "client.hpp"
# include "mimeTypes.hpp"
# include "redirective.hpp"
# include "cgi_extension.hpp"
# include "HttpStatusMapping.hpp"
# include "logger.hpp"

# define Webserv_core main

    void init_Webserv(int , char *const []);

# endif
