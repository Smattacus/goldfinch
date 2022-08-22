#include <systemc>
using namespace sc_core;

SC_MODULE(PROCESS){
    SC_CTOR(PROCESS){
        SC_THREAD(thread);

SC_METHOD(method);
}

void thread()
{
    int idx = 0;
    while (true)
    {
        std::cout << "thread" << idx++ << " @ " << sc_time_stamp() << std::endl;

        wait(1, SC_SEC);
    }
}

void method()
{
    int idx = 0;
    std::cout << "method" << idx++ << " @ " << sc_time_stamp() << std::endl;
    next_trigger(1, SC_SEC);
}
}
;
int sc_main(int nargs, char **argv)
{
    PROCESS process("process");
    sc_start(4, SC_SEC);
    return 0;
}