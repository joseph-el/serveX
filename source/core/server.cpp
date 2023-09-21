# include "server.hpp"

void init_Webserv(int argc, char *const argv[])
{
    Options opt(argc, argv);

    if (!opt.successful() or !MainContext.successful())
        return ;




}