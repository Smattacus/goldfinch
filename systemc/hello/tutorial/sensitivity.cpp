#include <systemc>
using namespace sc_core;

SC_MODULE(SENSITIVITY)
{
    sc_event e1, e2;

    SC_CTOR(SENSITIVITY)
    {
        SC_THREAD(trigger_1);
        SC_THREAD(trigger_2);
        SC_THREAD(catch_1or2_dyn);
        SC_THREAD(catch_1or2_static);

        sensitive << e1 << e2;
    }
    void trigger_1()
    {
        wait(SC_ZERO_TIME);
        while (true)
        {
            e1.notify();
            wait(2, SC_SEC);
        }
    }
    void trigger_2()
    {
        wait(SC_ZERO_TIME);
        while (true)
        {
            e2.notify();

            wait(3, SC_SEC);
        }
    }
    void catch_1or2_dyn()
    {
        while (true)
        {
            wait(e1 | e2);
            std::cout << "Dynamic sensitivity: e1 | e2 @ " << sc_time_stamp() << std::endl;
        }
    }
    void catch_1or2_static()
    {
        while (true)
        {
            wait();
            std::cout << "Static sensitivity e1 or e2 @ " << sc_time_stamp() << std::endl;
        }
    }
};
int sc_main(int nargs, char **argv)
{
    SENSITIVITY sensitivity("sensitivity");
    sc_start(7, SC_SEC);
    return 0;
}