#include <systemc>
using namespace sc_core;

SC_MODULE(SIGNAL_EVENT)
{
    sc_signal<int> s1, s2;

    SC_CTOR(SIGNAL_EVENT)
    {
        SC_THREAD(producer1);
        SC_THREAD(producer2);

        SC_THREAD(consumer);

        sensitive << s1 << s2;
        dont_initialize();
    }
    void producer1()
    {
        int v = 1;
        while (true)
        {
            s1.write(v++);
            wait(2, SC_SEC);
        }
    }
    void producer2()
    {
        int v = 1;
        while (true)
        {
            s2 = v++;
            wait(3, SC_SEC);
        }
    }
    void consumer()
    {
        while (true)
        {
            if (s1.event() == true && s2.event() == true)
            {
                std::cout << sc_time_stamp() << ": s1 & s2 triggered" << std::endl;
            }
            else if (s1.event() == true)
            {
                std::cout << sc_time_stamp() << ": s1 triggered" << std::endl;
            }
            else
            {
                std::cout << sc_time_stamp() << ": s2 triggered" << std::endl;
            }
            wait();
        }
    }
};
int sc_main(int nargs, char **argv)
{
    SIGNAL_EVENT signal_event("signal_event");
    sc_start(7, SC_SEC);
    return 0;
}