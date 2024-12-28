#pragma once
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>
namespace JsonParser{
    union JsonVal
    {
        std::string * chaine;
        int entier;
        float deci;
        std::map<std::string,JsonVal> *json;

    };      

    JsonVal  parseJson(std::string & path);
    void ReadFile(std::string & path, std::string & raw);
    JsonVal ParseKey(std::string & raw, std::string::iterator & it);
    std::pair<std::string,JsonVal> RetrievePairVal(std::string & raw, std::string::iterator & it);
    JsonVal GetVal(std::string & raw, std::string::iterator & it, std::string::iterator &itDeb);
}
