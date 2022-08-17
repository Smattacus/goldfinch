#include <systemc>
using namespace sc_core;

SC_MODULE(PROCESS)
{
    sc_clock clk;

    SC_CTOR(PROCESS) : clk("clk", 1, SC_SEC)
    {
        SC_METHOD(clk_method);
        SC_THREAD(clk_thread);
        SC_CTHREAD(clk_cthread, clk);
    }

    void clk_method(void)
    {
        std::cout << "clk_method triggered @ " << sc_time_stamp() << std::endl;
        next_trigger(sc_time(1, SC_SEC));
    }

    void clk_thread()
    {
        while (true)
        {
            std::cout << "clk_thread triggered @ " << sc_time_stamp() << std::endl;
            wait(1, SC_SEC);
        }
    }

    void clk_cthread()
    {
        while (true)
        {
            std::cout << "cthread triggered @ " << sc_time_stamp() << std::endl;
            wait();
        }
    }
};

int sc_main(int nargs, char **argv)
{
    PROCESS process("process");
    std::cout << "execution phase begins @" << sc_time_stamp() << std::endl;
    sc_start(3, SC_SEC);
    std::cout << "Execution is over @ " << sc_time_stamp() << std::endl;
    return 0;
}