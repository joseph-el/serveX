        
        ConfigFileParser is a general class responsible for parsing a config file
        
        and extracting it's data and returning a vector of server, it follows a predefined
        
        grammar syntax:
        
            <server>
            {
                <directive> <argument>;
                <directive> <argument>;
                <location> <path> {
                    <directive> <argument>;
                    <directive> <argument>;
                }
            }
        
        anything other than this will be considered as an error