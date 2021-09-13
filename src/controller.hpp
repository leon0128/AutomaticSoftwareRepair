#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>

class Analyzer;

class Controller
{
private:
    inline static const char *CONFIGURE_FILENAME{"configure.json"};

public:
    Controller();
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute();

private:
    bool initialize();
    bool analyzeFile(const std::string &filename
        , Analyzer&);
    
    bool initConfigureError(const std::string &what) const;
    
};

#endif