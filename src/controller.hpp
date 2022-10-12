#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller
{
public:
    Controller();
    ~Controller();

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute(int argc, char **argv);

private:
    bool initialize(int argc, char **argv);
    void finalize();

    void outputSpecifiedLog() const;
};

#endif