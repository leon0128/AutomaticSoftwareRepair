#ifndef UTILITY_CONCURRENCY_HPP
#define UTILITY_CONCURRENCY_HPP

#include <functional>

namespace CONCURRENCY
{

// function's return type should be bool.
// if funcion returns true, execution is terminated.
// at the end of execution, running function is processed to the end.
void execute(const std::function<bool()> &function
    , std::size_t concurrencySize);

}

#endif