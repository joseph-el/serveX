# ifndef __SERVEX_H__
# define __SERVEX_H__

# define serveX_main main

#if !defined(__unused)
    #define __unused __attribute__((unused))
#endif

# include <cstdio>
# include <sys/select.h>

# include "sx_location_data.hpp"
# include "sx_server_data.hpp"
# include "sx_config.hpp"


# include "sx_socket.hpp"
# include "sx_optioneer.hpp"

# include "sx_time.hpp"
# include "sx_templates_helper.hpp"
# include "sx_filesManipulation.hpp"
# include "sx_StringManipulation.hpp"

# include "sx_cgi.hpp"
# include "sx_headers.hpp"
# include "sx_requestBody.hpp"
# include "sx_request.hpp"
# include "sx_response.hpp"
# include "sx_client.hpp"
# include "sx_mimetype.hpp"
# include "sx_redirective.hpp"
# include "sx_cgiExtension.hpp"
# include "sx_HttpStatusMapping.hpp"
# include "sx_logger.hpp"

void init_serveX(int , char *const []);

# endif