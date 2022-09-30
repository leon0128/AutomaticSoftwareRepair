#include "representation.hpp"

namespace SIM
{

std::deque<Representation::Element*> Representation::mReps{};

void Representation::deleteReps()
{
    for(auto &&element : mReps)
        delete element;
}

}