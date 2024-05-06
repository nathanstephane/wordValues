/**
 * BETCHE NATHAN STEPHANE
 * nathanstephaneth@gmail.com
*/

#include <iostream>
#include "Logger.hpp"
#include "cmdParser.hpp"
#include "wordProcessor.hpp"


int main(int argc, char* argv[])
{
     Logger log;
    if(CommandParser::ParseArg(argc, argv, log))
    {
        std::string path = argv[1];
        WordProcessor wordProcessor(path,log); 
        wordProcessor.run();
    }
    else
    {
        std::string path = argv[1];
        log.logError("Failed to process words from"+ path);
        exit(0);
    }

    return 0;
}