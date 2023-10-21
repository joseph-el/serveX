################### AVAILABLE CONFIGURATIONS AND RULES ##########################
# <listen>                  Host:Port;                                          #
# <server_name>             exampleName;                                        #
# <error_page>              <code>      <pageUrl>;                              #
# <client_max_body_size>    <200M>;   -> it must be in Mb and have the 'M'      #
# <return>                  <status>    <redirectionUrl>;                       #
# <location> <pathToLocation> {                                                 #
#       <root>              <path>;                                             #
#       <allowed_methods>   <Methods...>;                                       #
#       <index>             <indexes>...;                                       #  
#       <upload_path>       <Path>;                                             #
#       <cgi_path>          <pathToCGI>;                                        #
#       <auto_index>        <off/on>;                                           #
#       <return>            <status>    <PathToRedirection>;                    #
# }                                                                             #
#################################################################################