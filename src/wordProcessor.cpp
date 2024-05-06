#include "wordProcessor.hpp"


WordProcessor::WordProcessor(){}


WordProcessor::WordProcessor(std::string& path, Logger& log) : words(0),
                                                             sumValues(0)
{
    _log = &log;
    words_values = std::make_shared<std::vector<std::pair<std::string,int >>>();
    filename= std::filesystem::path(path).stem().string();

    inputFile.open(path);
    inputFile.is_open() ? _log->logInfo("Successfully opened input file.") 
    : _log->logError("Failed to open input file.");

}

WordProcessor::~WordProcessor()
{
    if(inputFile.is_open())
    {
        inputFile.close();
    }
    if(_log)
    {
        delete _log;
        _log = nullptr;
    }
    
}

void WordProcessor::readValues()
{
    valuesFile.open("values.csv",std::ios::binary);
    if (valuesFile.is_open())
    { 
        _log->logInfo("successfully opened values file.");
        std::string buf;
        while (valuesFile)
        {
            std::getline(valuesFile,buf);
            setValues(buf);
        }
    }
     else 
     {
         _log->logError("failed to open values file.");
        
     }

}

void WordProcessor::setValues(std::string& s)
{
 
    int ctr=0;   
    bool comma=false; 
    std::string key="";
    std::string val="";
    while (s[ctr] != '\0')
    {   
       
        if(comma==false && s[ctr] !=',')
        {
            key+=s[ctr];
        }
        else if(comma==true && s[ctr] !=',')
        {
            val+=s[ctr];
        } 
        if(s[ctr]==',')
          {
            comma=true;
            
          }
          ctr++;
    }
    charPoints[key]= std::stoi(val); 
}

int WordProcessor::calcVal(const std::string& word)
{
    int sum = 0;
    int ctr=0;
    std::string charbuff="";

    while (word[ctr] != '\0') 
    {
        if(static_cast<unsigned char>(word[ctr]) > 127)
        {
           while (static_cast<unsigned char>(word[ctr]) > 127)
           {
                charbuff+=word[ctr];
                ctr++;
           }
            ctr--;  
        }else
        {
            charbuff=word[ctr];
        }
        sum += charPoints[charbuff];
        charbuff="";
        ctr++;
    }

    return sum;
}

bool WordProcessor::readWords()
{
    if(inputFile.is_open())
    {
        std::string wordBuf;
        while (inputFile >> wordBuf)
        {
            _log->logInfo("processing "+wordBuf);
            int val = calcVal(wordBuf);

            words_values->emplace_back(std::make_pair(wordBuf,val));
            ++words;
            std::cout<<wordBuf<<" : val= "<<val<<"\n";
            
        }
        return true;
    }else
    {
        _log->logError("error reading input file. file might be closed");
        return false;
    }
}

bool WordProcessor::cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b )
{
    return a.second < b.second;
}

void WordProcessor::printToFile()
{
    std::string outputFilename= filename+".count.txt";
    outputFile.open(outputFilename,std::ios_base::app);
    if(outputFile.is_open())
    {
        _log->logInfo("successfully opened "+filename);
        std::sort(words_values->begin(), words_values->end() , [this]( std::pair<std::string,int> &a,  std::pair<std::string,int> &b)
        {
            return cmp(a,b);
        });
        int ctr=0;
        for(auto& w : *words_values.get())
        {
            outputFile << w.first<<","<<w.second<<std::endl;
            _log->logInfo("successfully wrote to file: "+w.first+" with value : "+std::to_string(w.second));
            sumValues+=w.second;
            ctr++;
        }
        _log->logInfo("-----Total words values processed = "+std::to_string(sumValues));
        _log->logInfo("-----Processed "+std::to_string(ctr)+" words out of "+std::to_string(words));
        outputFile.close();
    }else{
        _log->logError("Error opening output files");
    }
}

void WordProcessor::run()
{
        readValues();
        readWords() ? printToFile() : exit(0);

}