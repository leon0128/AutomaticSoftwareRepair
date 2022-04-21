#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>
#include <deque>
#include <filesystem>

class Analyzer;

class Controller
{
public:
    Controller();
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute(int argc, char **argv);

private:
    bool initialize(int argc, char **argv);

    bool addAllFiles(std::deque<std::string>&
        , const std::filesystem::path &path);
    Analyzer *analyze(const std::string &filename);
    
    bool initConfigureError(const std::string &what) const;
    bool poolAnalyzingWarning(const std::string &what) const;
    bool emptyPoolError() const;
};

#endif