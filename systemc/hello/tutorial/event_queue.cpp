#include <systemc>
using namespace sc_core;

SC_MODULE(QUEUE)
{
    sc_event e;
    sc_event_queue eq;
    SC_CTOR(QUEUE)
    {
        SC_THREAD(trigger);
        SC_THREAD(catch_e);

        sensitive << e;
        dont_initialize();
        SC_THREAD(catch_eq);
        sensitive << eq;
        dont_initialize();
    }
    void trigger()
    {
        while (true)
        {
            e.notify(2, SC_SEC);
            e.notify(1, SC_SEC);
            eq.notify(2, SC_SEC);
            eq.notify(1, SC_SEC);
            wait(10, SC_SEC);
        }
    }

    void catch_e()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ": catches e" << std::endl;
            wait();
        }
    }

    void catch_eq()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ": catches eq" << std::endl;
            wait();
        }
    }
};
int sc_main(int nargs, char **argv)
{
    QUEUE queue("queue");
    sc_start(30, SC_SEC);
    return 0;
}