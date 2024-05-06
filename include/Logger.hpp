#ifndef LOGGER_H
#define LOGGER_H
#include <time.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include <ctime>
#include <chrono>
/**
 * A basic logger class that acts as 
 * a log tracer for any event/information
 * regarding errors or data processing.
 * 
*/
class Logger 
{
    protected:
        time_t _time;        
        std::ofstream file;       

        std::string GetTime()
        {
            if(time(&_time)==-1)
            {
                std::cerr<<"Err: Time not available";
                return "-1";
            }else{
                char *tmp = ctime(&_time); 
                tmp[strlen(tmp)-1] ='\0'; //replaces the breaking line char by the null terminator
                return tmp;
            }
        }
    
    public:
         Logger()
        {
            file.open("log.txt",std::ios_base::app);
            std::cout<<"\n ----------Logger as of "<<GetTime()<<"----------\n";

            if (file.is_open()){ 
                file<<"\n ----------Logger as of "<<GetTime()<<"----------\n";
            }else{ 
                std::cerr<<"could not open or create file\n";
             }  
        }

        ~Logger()
        {
            file.close();
        }

        // logs information messages to the console and to the log file.
        void logInfo(const std::string& message)
        {
            std::cout<<"[INFO:"<<GetTime()<<"] "<<message<<std::endl;
            if(file.is_open())
            file<<"[INFO:"<<GetTime()<<"] "<<message<<std::endl;
        }

        // logs error messages to the console and to the log file.
        void logError(const std::string& errMessage)
        {
            std::cerr<<"[ERROR:"<<GetTime()<<"]" <<errMessage<<std::endl;
            if(!file.bad())
            file<<"[ERROR:"<<GetTime()<<"]" <<errMessage<<std::endl;
        }

        void logWarning()
        {
          
            std::cerr<<"[WARNING:"<<GetTime()<<"] Logger Test:\n";
            
            if(file.is_open())
            {
                file<<"[TEST:"<<GetTime()<<"] Logger Test: \n";
            }
            else{
                std::cerr<<"not opened";
            }    
        }

};


#endif