#include <systemc>
using namespace sc_core;

SC_MODULE(COMBINED)
{
    sc_event e1, e2, e3, e4, e5, e6, e7, e8, e9, e10;

    SC_CTOR(COMBINED)
    {
        SC_THREAD(trigger);
        SC_THREAD(catcher_0);
        SC_THREAD(catcher_1);
        SC_THREAD(catcher_2and3);
        SC_THREAD(catcher_4or5);
        SC_THREAD(catcher_timeout_or_6);
        SC_THREAD(catcher_timeout_or_7or8);
        SC_THREAD(catcher_timeout_or_9and10);
    }

    void trigger(void)
    {
        e1.notify(1, SC_SEC);
        e2.notify(2, SC_SEC);
        e3.notify(3, SC_SEC);
        e4.notify(4, SC_SEC);
        e5.notify(5, SC_SEC);
        e6.notify(6, SC_SEC);
        e7.notify(7, SC_SEC);
        e8.notify(8, SC_SEC);
        e9.notify(9, SC_SEC);
        e10.notify(10, SC_SEC);
    }
    void catcher_0(void)
    {
        wait(2, SC_SEC);
        std::cout << sc_time_stamp() << ": 2sec timeout" << std::endl;
    }
    void catcher_1(void)
    {
        wait(e1);
        std::cout << sc_time_stamp() << ": catch e1" << std::endl;
    }
    void catcher_2and3(void)
    {
        wait(e2 & e3);
        std::cout << sc_time_stamp() << ": catch e2 and e3" << std::endl;
    }
    void catcher_4or5(void)
    {
        wait(e4 | e5);
        std::cout << sc_time_stamp() << ": caught e4 or e5" << std::endl;
    }
    void catcher_timeout_or_6(void)
    {
        wait(sc_time(5, SC_SEC), e6);
        std::cout << sc_time_stamp() << ": 5sec timeout or caught e6" << std::endl;
    }
    void catcher_timeout_or_7or8(void)
    {
        wait(sc_time(20, SC_SEC), e7 | e8);
        std::cout << sc_time_stamp() << ": 20s timeout or caught e7 | e8" << std::endl;
    }
    void catcher_timeout_or_9and10(void)
    {
        wait(sc_time(20, SC_SEC), e9 & e10);
        std::cout << sc_time_stamp() << ": 20s timeout or caught (e9 & e10)" << std::endl;
    }
};

int sc_main(int args, char **argv)
{
    COMBINED combined("combined");
    sc_start();
    return 0;
}