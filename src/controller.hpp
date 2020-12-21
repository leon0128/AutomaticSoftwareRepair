#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>

class TranslationUnit;

class Controller
{
public:
    Controller(int argc, char **argv);

    bool execute();

private:
    bool createTree();    

    std::unordered_map<std::string, TranslationUnit*> mFileMap;
};

#endif