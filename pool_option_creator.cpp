#include <iostream>
#include <filesystem>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <random>

inline extern std::deque<std::string> samePool;
inline decltype(samePool) samePool{};
inline extern std::deque<std::string> otherPool;
inline decltype(otherPool) otherPool{};

inline extern constexpr const std::size_t revertedCount{1ull};


// argv[1]: "--same" or "--other"
// argv[2]: target filename
// argv[3...]: pool filenames

bool setPool(const std::string &targetFilename
    , const std::deque<std::string> &poolFilenames);
bool output(const std::string &flag);
bool argumentError();
bool targetError(const std::string &filename);
bool poolError(const std::string &filename);
bool flagError(const std::string &flag);

int main(int argc, char **argv)
{
    if(argc < 4)
        return argumentError(), 1;

    std::string targetFilename{argv[2]};
    std::deque<std::string> poolFilenames;
    for(int i{3}; i < argc; i++)
        poolFilenames.emplace_back(argv[i]);

    if(!setPool(targetFilename, poolFilenames))
        return 1;

    if(!output(argv[1]))
        return 1;

    return 0;
}

bool setPool(const std::string &targetFilename
    , const std::deque<std::string> &poolFilenames)
{
    auto &&addFilesRecursively{[&](auto &&recursiveFunc
        , std::deque<std::filesystem::path> &paths
        , const std::filesystem::path &path)
        -> void
        {
            if(std::filesystem::is_regular_file(path))
            {
                if(path.extension().string() == ".c")
                    paths.push_back(path);
            }
            else if(std::filesystem::is_directory(path))
            {
                for(auto &&child : std::filesystem::directory_iterator{path})
                    recursiveFunc(recursiveFunc, paths, child.path());
            }
        }};

    std::filesystem::path targetPath{targetFilename};
    if(std::filesystem::is_regular_file(targetPath))
        targetPath = targetPath.parent_path();
    else if(std::filesystem::is_directory(targetPath))
        ;
    else
        return targetError(targetFilename);
    
    for(std::size_t i{0ull}; i < revertedCount; i++)
    {
        if(!targetPath.has_parent_path())
            return targetError(targetFilename);
        targetPath = targetPath.parent_path();
    }

    std::deque<std::filesystem::path> poolPaths;
    for(auto &&poolFilename : poolFilenames)
    {
        addFilesRecursively(addFilesRecursively
            , poolPaths
            , poolFilename);
    }

    for(auto &&path : poolPaths)
    {
        std::filesystem::path parent{path};
        for(std::size_t i{0ull}; i < revertedCount + 1ull; i++)
        {
            if(!parent.has_parent_path())
                return poolError(path.string());
            parent = parent.parent_path();
        }

        if(parent == targetPath)
            samePool.push_back(path.string());
        else
            otherPool.push_back(path.string());
    }

    return true;
}

bool output(const std::string &flag)
{
    auto &&out{[&](auto &&filenames)
        -> void
        {
            for(auto &&filename : filenames)
                std::cout << "--pool " << filename << " ";
        }};

    bool isSame{false};
    if(flag == "--same")
        isSame = true;
    else if(flag == "--other")
        isSame = false;
    else
        return flagError(flag);

    if(isSame)
        out(samePool);
    else
    {
        std::deque<std::string> sample;
        std::sample(otherPool.begin()
            , otherPool.end()
            , std::back_inserter(sample)
            , samePool.size()
            , std::mt19937_64{std::random_device{}()});
        out(sample);
    }

    return true;
}

bool argumentError()
{
    std::cerr << "argumentError():\n"
        "    exe: ./exe (--same or --other) target pool...\n"
        << std::flush;
    return false;
}

bool targetError(const std::string &filename)
{
    std::cerr << "targetError():\n"
        "    what: failed to use target file.\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

bool poolError(const std::string &filename)
{
    std::cerr << "poolError():\n"
        "    what: failed to use pool file.\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

bool flagError(const std::string &flag)
{
    std::cerr << "flagError():\n"
        "    what: unknown flag.\n"
        "    flag: " << flag
        << std::endl;
    return false;
}