#include <systemc>
using namespace sc_core;

SC_MODULE(QUEUE_COMBINED)
{
    sc_event_queue eq1, eq2;
    SC_CTOR(QUEUE_COMBINED)
    {
        SC_THREAD(trigger);
        SC_THREAD(catcher);
        sensitive << eq1 << eq2;
        dont_initialize();
    }
    void trigger()
    {
        eq1.notify(1, SC_SEC);
        eq1.notify(2, SC_SEC);
        eq2.notify(2, SC_SEC);
        eq2.notify(3, SC_SEC);
    }
    void catcher()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ": caught trigger" << std::endl;
            wait();
        }
    }
};
int sc_main(int nargs, char **argv)
{
    QUEUE_COMBINED combined("combined");
    sc_start();
    return 0;
}