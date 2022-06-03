#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>
#include <deque>
#include <filesystem>
#include <vector>
#include <memory>

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
    bool createAnalyzersFromPool(std::vector<std::shared_ptr<Analyzer>>&);
    Analyzer *createAnalyzer(const std::string &filename);

    bool initConfigureError(const std::string &what) const;
    bool poolAnalyzingWarning(const std::string &what) const;
    bool emptyPoolError() const;
};

#endif