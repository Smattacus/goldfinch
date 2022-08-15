#include <systemc>
using namespace sc_core;

void hello1()
{
    std::cout << "Hello world without systemc" << std::endl;
}

int sc_main(int args, char *[])
{
    hello1();
    return 0;
}