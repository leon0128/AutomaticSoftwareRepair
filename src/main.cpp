#include "controller.hpp"

int main(int argc, char **argv)
{
    Controller controller;
    if(controller.execute(argc, argv))
        return 0;
    else
        return 1;
}