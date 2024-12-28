#include "main.h"
#include "JsonParser.h"
int main(){
    std::string path = "../json.txt";
    JsonParser::JsonVal  j = JsonParser::parseJson(path);
    std::cout << (*(*(*j.json)["personne"].json)["nom"].chaine) << std::endl;
    std::getchar();
    return -1;
}