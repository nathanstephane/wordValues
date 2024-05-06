#ifndef CMDPARSE_H
#define CMD_PARSE_H
#include <string>
#include <iostream>
#include "Logger.hpp"

class CommandParser
{
    private:
    int argCount;
    std::string inputs;
    CommandParser(){}
    
    public:
    static bool ParseArg(int argc, char* argv[], Logger &log);
};

/**
 * A simple function that check the number of arguments
 * provived inorder to continue running the program.
 * returns if only one arguments was passed  from the 
 * terminal when executing the program. 
*/
bool CommandParser::ParseArg(int argc, char* argv[], Logger &log)
{
    if(argc == 2)
        {
            log.logInfo("Successfully parsed cmd arguments");
            return true;
        }
        else{
            log.logError("Provide only one argument which is the path of the file to be processed");
            return false;
        }
}

#endif