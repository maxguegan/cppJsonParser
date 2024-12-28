#include "JsonParser.h"
using namespace JsonParser;
JsonVal  JsonParser::parseJson(std::string & path){
    std::string raw;
    ReadFile(path, raw);
    std::string::iterator it = raw.begin();
    while(*it == ' ' || *it == '\n')it++;
    return ParseKey(raw,it);
   
}
void JsonParser::ReadFile(std::string & path, std::string & raw){
    std::ifstream file(path);
    std::string ligne;
    while(std::getline(file, ligne)){
        raw.append(ligne);
    }
}
JsonVal JsonParser::ParseKey(std::string & raw, std::string::iterator & it){
    assert(*it == '{');
    
    it++;
    std::map<std::string,JsonVal> * jsonVal = new  std::map<std::string,JsonVal>();
    while(*it != '}'){
        const auto [key,value] = RetrievePairVal(raw, it);
        (*jsonVal)[key] = value;
  
        while(*it == ' ' || *it == '\n'){
            it++;
        }
    }
    JsonVal j;
    j.json = jsonVal;
    return j;
}
std::pair<std::string,JsonVal> JsonParser::RetrievePairVal(std::string & raw, std::string::iterator & it){
    assert(it != raw.end());
    
    while(*it == ' ' || *it == '\n')it++;

    std::string key;
    JsonVal jsonVal;
    std::string::iterator itDeb;
    if(*it == '\"'){
         itDeb = ++it;
        it++;

        while(*it != '\"')it++;
    }
    key = raw.substr(itDeb - raw.begin(), it - itDeb);
    
    assert(*(++it) == ':');
    it++;
    while(*it == ' ' || *it == '\n')it++;

    if(*it == '{'){
        jsonVal = ParseKey(raw,it);
    }else{
        itDeb = it;
        if(*it == '\"'){
            it++;
            while(*it != '\"')it++;
           jsonVal = GetVal(raw,it,itDeb);
        }else{
            while(*it != ' ' && *it != '}' && *it != ',')it++;
            jsonVal = GetVal(raw,it,itDeb);
        }
    }
          it++;
    while(*it == ' ' || *it == '\n')it++;
    
    if(*it == ',')it++;

    return std::make_pair(key,jsonVal);
}
JsonVal JsonParser::GetVal(std::string & raw, std::string::iterator & it, std::string::iterator &itDeb){
   assert(it != raw.end());
    JsonVal j;

    if(*it == '\"' && *itDeb == '\"'){
        std::string * val = new std::string();
        *val = raw.substr(itDeb - raw.begin() + 1, it - itDeb - 1);
        j.chaine = val;
    }else{
        std::string sub = raw.substr(itDeb - raw.begin(), it - itDeb);

        bool isFloat = false;
        while(itDeb < it){
            if(*itDeb == '.'){
                isFloat = true;
                break;
            }
            itDeb++;
        }
        if(isFloat){
            j.deci = std::stof(sub);
        }else{
            j.entier = std::stoi(sub);
        }
    }
    return j;
}