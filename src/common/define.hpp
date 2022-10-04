#ifndef COMMON_DEFINE_HPP
#define COMMON_DEFINE_HPP

#include <memory>
#include <string>

inline namespace COMMON
{

namespace SCOPE
{
    class Scope;
}

namespace TOKEN
{
    class TranslationUnit;
}

struct CodeInformation
{
    std::string mFilename;
    std::shared_ptr<TOKEN::TranslationUnit> mTranslationUnit;
    std::shared_ptr<SCOPE::Scope> mScope;
};

}

#endif