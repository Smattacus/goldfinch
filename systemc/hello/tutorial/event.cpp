#include <systemc>
using namespace sc_core;

SC_MODULE(EVENT)
{
    sc_event e;
    SC_CTOR(EVENT)
    {
        SC_THREAD(trigger);

        SC_THREAD(catcher);
    }

    void trigger()
    {
        while (true)
        {
            e.notify(1, SC_SEC);

            if (sc_time_stamp() == sc_time(4, SC_SEC))
            {
                e.cancel();
            }
            wait(2, SC_SEC);
        }
    }

    void catcher()
    {
        while (true)
        {
            wait(e);
            std::cout << "Event caught at " << sc_time_stamp() << std::endl;
        }
    }
};

int sc_main(int nargs, char **argv)
{
    EVENT event("event");
    sc_start(8, SC_SEC);
    return 0;
}