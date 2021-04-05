#include "controller.hpp"

int main(int argc, char **argv)
{
    Controller controller;
    if(controller.execute())
        return 0;
    else
        return 1;
}