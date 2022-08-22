#include <systemc>
using namespace sc_core;

SC_MODULE(CLOCK_EXAMPLE)
{
    sc_port<sc_signal_in_if<bool>> clk;

    SC_CTOR(CLOCK_EXAMPLE)
    {
        SC_THREAD(thread);
        sensitive << clk;
        dont_initialize();
    }
    void thread()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ", value = " << clk->read() << std::endl;
            wait();
        }
    }
};
int sc_main(int nargs, char **argv)
{
    sc_clock clk("clk", 10, SC_SEC, 0.2, 10, SC_SEC, false);

    CLOCK_EXAMPLE clock_holder("clock");
    clock_holder.clk(clk);
    sc_start(31, SC_SEC);
    return 0;
}