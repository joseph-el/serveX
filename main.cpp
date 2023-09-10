
#include "./srcs/ParseConfigFile/ConfigFileParser.hpp"

void    error( std::string const& error )
{
    std::cerr << error << std::endl;
    _exit(1);
}

int main(int ac, char *av[])
{
    std::string pathToConfFile;

    if (ac > 2)
         return error("Invalid Arguments: try with a single path or without it"), 1;

    /*  Loading The Conf File if Not We Load the default one */
    if (ac == 2)
        pathToConfFile = std::string(av[1]);
    else
        pathToConfFile = "./srcs/ParseConfigFile/defaultConfFile/default.conf";
    
    /* Init ConfigFileParserObj */
    ConfigFileParser    configFile(pathToConfFile);
    try
    {
        configFile.parseServersData();
    }
    catch(...)
    {
        std::cerr << "Unkown Error During The Parse Of The Config File" << std::endl;
    }

    /*  Printing Servers Content For A Quick Check   */
    for (int i = 0; i < (int)configFile.getServers().size(); i++)
        configFile.getServers()[i].printServerConfig();
    return 0;
}