#ifndef WORD_PROCESSOR_H
#define WORD_PROCESSOR_H



#include <fstream>
#include "Logger.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <filesystem>


/**
* This class contains the data members and
* function necessary to parse the input file
* to be processed and count the words values in
* it.
*
* The class has a raw pointer to Logger (_log) as using a smart
* pointer would lead to taking ownership of log and potentialy
* destroying it when not in used or reference else where in memory.
* unless I am mistaken :)
*
* words_values in this case is a pointer as processing too many words
* or large files and storing them might take up space on the stack. 
*/
class WordProcessor
{
    private:
        std::ifstream inputFile;
        std::ifstream valuesFile;
        std::ofstream outputFile;
        Logger* _log;
        std::unordered_map<std::string,int> charPoints;
        std::shared_ptr<std::vector<std::pair<std::string,int >>>  words_values;
        size_t words;
        size_t sumValues;
        std::string filename;

        void readValues();
        bool readWords();
        bool cmp(std::pair<std::string, int>& v1, std::pair<std::string, int>& v2);
        WordProcessor(); //forces the user to use the parameterized constructor

    public:
        WordProcessor(std::string& path, Logger& log);
        ~WordProcessor();
        int calcVal(const std::string& word);
        void setValues(std::string& s);
        void printToFile();
        void run();
        
};

#endif