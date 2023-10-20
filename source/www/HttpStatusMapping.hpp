# ifndef __MAP_HTTP_STATUS__
# define __MAP_HTTP_STATUS__

# include <map>
# include <array>
# include <iterator>
# include <iostream>

# include "server-core.hpp"

using namespace std;

# define HTTP_CONTINUE 100
# define HTTP_SWITCHING_PROTOCOLS 101
# define HTTP_AVAILABLE_METHOD 9

# define HTTP_OK 200
# define HTTP_CREATED 201
# define HTTP_ACCEPTED 202
# define HTTP_NON_AUTHORITATIVE_INFORMATION 203
# define HTTP_NO_CONTENT 204
# define HTTP_RESET_CONTENT 205
# define HTTP_PARTIAL_CONTENT 206
 
# define HTTP_MULTIPLE_CHOICES 300
# define HTTP_MOVED_PERMANENTLY 301
# define HTTP_FOUND 302
# define HTTP_SEE_OTHER 303
# define HTTP_NOT_MODIFIED 304
# define HTTP_USE_PROXY 305
# define HTTP_TEMPORARY_REDIRECT 307
 
# define HTTP_BAD_REQUEST 400
# define HTTP_UNAUTHORIZED 401
# define HTTP_PAYMENT_REQUIRED 402
# define HTTP_FORBIDDEN 403
# define HTTP_NOT_FOUND 404
# define HTTP_METHOD_NOT_ALLOWED 405
# define HTTP_NOT_ACCEPTABLE 406
# define HTTP_PROXY_AUTHENTICATION_REQUIRED 407
# define HTTP_REQUEST_TIMEOUT 408
# define HTTP_CONFLICT 409
# define HTTP_GONE 410
# define HTTP_LENGTH_REQUIRED 411
# define HTTP_PRECONDITION_FAILED 412
# define HTTP_REQUEST_ENTITY_TOO_LARGE 413
# define HTTP_REQUEST_URI_TOO_LONG 414
# define HTTP_UNSUPPORTED_MEDIA_TYPE 415
# define HTTP_REQUESTED_RANGE_NOT_SATISFIABLE 416
# define HTTP_EXPECTATION_FAILED 417

# define HTTP_INTERNAL_SERVER_ERROR 500
# define HTTP_NOT_IMPLEMENTED 501
# define HTTP_BAD_GATEWAY 502
# define HTTP_SERVICE_UNAVAILABLE 503
# define HTTP_GATEWAY_TIMEOUT 504
# define HTTP_VERSION_NOT_SUPPORTED 505

# define AUTOINDEX_PAGE "<!DOCTYPE html>\r\n"\
                        "<html lang=\"en\" >\r\n"\
                        "<head>\r\n"\
                        "  <meta charset=\"UTF-8\">\r\n"\
                        "  <title>Webserv</title>\r\n"\
                        "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n"\
                        "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">\r\n"\
                        "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>\r\n"\
                        "<link href=\"https://fonts.googleapis.com/css2?family=Urbanist:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap\" rel=\"stylesheet\">\r\n"\
                        "<link href=\"https://fonts.googleapis.com/css2?family=Cedarville+Cursive&display=swap\" rel=\"stylesheet\">\r\n"\
                        "\t<style>\r\n"\
                        "\t\t* {\r\n"\
                        "\t\t\t-webkit-text-size-adjust: 100%;\r\n"\
                        "\t\t\t-webkit-tap-highlight-color: transparent;\r\n"\
                        "\t\t\t-webkit-font-smoothing: antialiased;\r\n"\
                        "\t\t\ttext-rendering: optimizeLegibility;\r\n"\
                        "\t\t\tbox-sizing: border-box;\r\n"\
                        "\t\t\tuser-select: none;\r\n"\
                        "\t\t\tfont-family: \"Urbanist\", sans-serif;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t::-webkit-scrollbar {\r\n"\
                        "\t\t\theight: 20px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t::-webkit-scrollbar-track {\r\n"\
                        "\t\t\tbackground: #444;\r\n"\
                        "\t\t\tborder-radius: 30px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t::-webkit-scrollbar-thumb {\r\n"\
                        "\t\t\tbackground: #ccc;\r\n"\
                        "\t\t\twidth: 70px;\r\n"\
                        "\t\t\tborder-radius: 30px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t::-webkit-scrollbar-thumb:hover {\r\n"\
                        "\t\t\tbackground: white;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\thtml {\r\n"\
                        "\t\t\tdisplay: flex;\r\n"\
                        "\t\t\tflex-direction: column;\r\n"\
                        "\t\t\talign-items: center;\r\n"\
                        "\t\t\tjustify-content: center;\r\n"\
                        "\t\t\tbackground-image: url('https://images.pexels.com/photos/1424337/pexels-photo-1424337.jpeg?cs=srgb&dl=pexels-simon-berger-1424337.jpg&fm=jpg');\r\n"\
                        "\t\t\tbackground-size: cover;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tbody {\r\n"\
                        "\t\t\tmargin: 0;\r\n"\
                        "\t\t\tdisplay: flex;\r\n"\
                        "\t\t\tflex-direction: column;\r\n"\
                        "\t\t\talign-items: center;\r\n"\
                        "\t\t\tjustify-content: center;\r\n"\
                        "\t\t\twidth: 100%;\r\n"\
                        "\t\t\tmax-width: 1000px;\r\n"\
                        "\t\t\tmin-height: 100vh;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@counter-style symbols {\r\n"\
                        "\t\t\tsystem: cyclic;\r\n"\
                        "\t\t\tsymbols: \"\\01F4C2\";\r\n"\
                        "\t\t\tsuffix: \"  \";\r\n"\
                        "\t\t}\r\n"\
                        "\t\t@counter-style symbolss {\r\n"\
                        "\t\t\tsystem: cyclic;\r\n"\
                        "\t\t\tsymbols: \"\\1F4C4\";\r\n"\
                        "\t\t\tsuffix: \"  \";\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@supports not (list-style-type: symbols) {\r\n"\
                        "\t\t\tul {\r\n"\
                        "\t\t\t\tdisplay: none !important;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\tdiv > div {\r\n"\
                        "\t\t\t\tdisplay: flex !important;\r\n"\
                        "\t\t\t\talign-items: center !important;\r\n"\
                        "\t\t\t\tjustify-content: center !important;\r\n"\
                        "\t\t\t\twidth: 100% !important;\r\n"\
                        "\t\t\t\theight: 100% !important;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tbody > div {\r\n"\
                        "\t\t\tposition: relative;\r\n"\
                        "\t\t\tdisplay: flex;\r\n"\
                        "\t\t\tflex-direction: column;\r\n"\
                        "\t\t\talign-items: center;\r\n"\
                        "\t\t\tjustify-content: center;\r\n"\
                        "\t\t\theight: 100%;\r\n"\
                        "\t\t\twidth: 100%;\r\n"\
                        "\t\t\tbackground: #111;\r\n"\
                        "\t\t\tpadding: 20px;\r\n"\
                        "\t\t\tborder-radius: 50px;\r\n"\
                        "\t\t\toutline: 1px solid white;\r\n"\
                        "\t\t\toutline-offset: 10px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@keyframes bg-rgb {\r\n"\
                        "\t\t\t0% {\r\n"\
                        "\t\t\t\tbackground-position: 0%;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\t100% {\r\n"\
                        "\t\t\t\tbackground-position: 500%;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\th1 {\r\n"\
                        "\t\t\tposition: relative;\r\n"\
                        "\t\t\tfont-size: 20pt;\r\n"\
                        "\t\t\tmargin: 0;\r\n"\
                        "\t\t\tline-height: 34pt;\r\n"\
                        "\t\t\tcolor: #eee;\r\n"\
                        "\t\t\tmargin-bottom: 10px;\r\n"\
                        "\t\t\ttext-align: center;\r\n"\
                        "\t\t\toverflow: hidden;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\th1::after {\r\n"\
                        "\t\t\tposition: absolute;\r\n"\
                        "\t\t\tbottom: 0;\r\n"\
                        "\t\t\tright: 100%;\r\n"\
                        "\t\t\twidth: 800%;\r\n"\
                        "\t\t\theight: 4px;\r\n"\
                        "\t\t\tbackground: linear-gradient(\r\n"\
                        "\t\t\t\t\t90deg,\r\n"\
                        "\t\t\t\t\tRed,\r\n"\
                        "\t\t\t\t\tOrange,\r\n"\
                        "\t\t\t\t\tYellow,\r\n"\
                        "\t\t\t\t\tLawnGreen,\r\n"\
                        "\t\t\t\t\tBlue,\r\n"\
                        "\t\t\t\t\tViolet\r\n"\
                        "\t\t\t);\r\n"\
                        "\t\t\tbackground-position: center;\r\n"\
                        "\t\t\tcontent: \"\";\r\n"\
                        "\t\t\tanimation: title 5s ease-in-out infinite;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@keyframes title {\r\n"\
                        "\t\t\t0% {\r\n"\
                        "\t\t\t\tright: 100%;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\t100% {\r\n"\
                        "\t\t\t\tright: -800%;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tdiv > div {\r\n"\
                        "\t\t\tdisplay: none;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tdiv > div p {\r\n"\
                        "\t\t\tcolor: red;\r\n"\
                        "\t\t\tfont-size: 14pt;\r\n"\
                        "\t\t\tline-height: 24pt;\r\n"\
                        "\t\t\ttext-align: center;\r\n"\
                        "\t\t\tmargin: 10px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul {\r\n"\
                        "\t\t\tposition: relative;\r\n"\
                        "\t\t\twidth: 100%;\r\n"\
                        "\t\t\tmax-height: 230px;\r\n"\
                        "\t\t\tdisplay: flex;\r\n"\
                        "\t\t\tflex-direction: column;\r\n"\
                        "\t\t\talign-items: space-between;\r\n"\
                        "\t\t\tjustify-content: space-between;\r\n"\
                        "\t\t\tflex-wrap: wrap;\r\n"\
                        "\t\t\toverflow-x: scroll;\r\n"\
                        "\t\t\toverflow-y: hidden;\r\n"\
                        "\t\t\tpadding-bottom: 15px;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul li {\r\n"\
                        "\t\t\tposition: relative;\r\n"\
                        "\t\t\tcolor: #ccc;\r\n"\
                        "\t\t\tpadding: 10px 50px 10px 12px;\r\n"\
                        "\t\t\tlist-style-type: symbols;\r\n"\
                        "\t\t\tfont-size: 12pt;\r\n"\
                        "\t\t\tline-height: 24pt;\r\n"\
                        "\t\t\tfont-weight: 500;\r\n"\
                        "\t\t\tmargin: 0px 60px 0px 0px;\r\n"\
                        "\t\t\ttext-shadow: 1px 1px 0px black, 2px 2px 0px black;\r\n"\
                        "\t\t\ttransition: all 0.1s linear;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul li::after {\r\n"\
                        "\t\t\tposition: absolute;\r\n"\
                        "\t\t\tbottom: 5px;\r\n"\
                        "\t\t\tright: 10%;\r\n"\
                        "\t\t\twidth: 100%;\r\n"\
                        "\t\t\theight: 2px;\r\n"\
                        "\t\t\tbackground: #111;\r\n"\
                        "\t\t\tcontent: \"\";\r\n"\
                        "\t\t\ttransition: all 0.2s ease-in-out;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul li:hover::after {\r\n"\
                        "\t\t\tright: -20%;\r\n"\
                        "\t\t\ttransition: all 0.2s ease-in-out;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul li:hover {\r\n"\
                        "\t\t\tbackground: #ccc;\r\n"\
                        "\t\t\tcolor: black;\r\n"\
                        "\t\t\tcursor: pointer;\r\n"\
                        "\t\t\ttext-shadow: none;\r\n"\
                        "\t\t\ttransition: all 0.1s linear;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\tul li::marker {\r\n"\
                        "\t\t\tanimation: idle 8s linear infinite;\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@keyframes idle {\r\n"\
                        "\t\t\t0% {\r\n"\
                        "\t\t\t\ttransform: rotateY(0deg) translateX(0px) scale(1);\r\n"\
                        "\t\t\t\tfilter: saturate(100%) brightness(1);\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\t50% {\r\n"\
                        "\t\t\t\ttransform: rotateY(180deg) translateX(10px) scale(1.4);\r\n"\
                        "\t\t\t\tfilter: saturate(300%) brightness(2);\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\t100% {\r\n"\
                        "\t\t\t\ttransform: rotateY(360deg) translateX(0px) scale(1);\r\n"\
                        "\t\t\t\tfilter: saturate(100%) brightness(1);\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (pointer: coarse) {\r\n"\
                        "\t\t\tul {\r\n"\
                        "\t\t\t\tpadding-bottom: unset;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\t::-webkit-scrollbar {\r\n"\
                        "\t\t\t\tdisplay: none;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 1090px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 920px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 990px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 820px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 890px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 720px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 790px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 620px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 690px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 520px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\tul li {\r\n"\
                        "\t\t\t\tpadding: 10px 20px 10px 12px;\r\n"\
                        "\t\t\t\tmargin: 0px 40px 0px 0px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 590px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 420px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 490px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 320px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t\tul li {\r\n"\
                        "\t\t\t\tpadding: 10px 10px 10px 10px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "\r\n"\
                        "\t\t@media (max-width: 390px) {\r\n"\
                        "\t\t\tbody {\r\n"\
                        "\t\t\t\tmax-width: 280px;\r\n"\
                        "\t\t\t}\r\n"\
                        "\t\t}\r\n"\
                        "        a {\r\n"\
                        "            text-decoration: none;\r\n"\
                        "            color: inherit;\r\n"\
                        "            font-size: 150%;\r\n"\
                        "            font-weight: bold;\r\n"\
                        "        }\r\n"\
                        "\t</style>\r\n"\
                        "\r\n"\
                        "</head>\r\n"\
                        "<body>\r\n"\
                        "<div>\r\n"\
                        "\r\n"\
                        "\t<div>\r\n"\
                        "\t\t<p>\r\n"\
                        "\t\t\tYour browser does not support symbols as a list-style type.\r\n"\
                        "\t\t</p>\r\n"\
                        "\t</div>\r\n"\
                        "\r\n"\
                        "\t<h1>Listing Directory</h1>\r\n"\
                        "\r\n"\
                        "\t<ul>\r\n"

class HttpStatusMapping : public map <short , string> {
     public :
         HttpStatusMapping();
};


extern HttpStatusMapping WebStatusMap;

# endif