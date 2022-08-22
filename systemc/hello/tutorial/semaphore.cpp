#include <systemc>
using namespace sc_core;

SC_MODULE(EXAMPLE_SEMAPHORE)
{
    sc_semaphore s;
    SC_CTOR(EXAMPLE_SEMAPHORE) : s(2)
    {
        SC_THREAD(thread_1);
        SC_THREAD(thread_2);
        SC_THREAD(thread_3);
    }
    void thread_1()
    {
        while (true)
        {
            this->_try_and_post("thread_1");
            wait(SC_ZERO_TIME);
        }
    }
    void thread_2()
    {
        while (true)
        {
            this->_try_and_post("thread_2");
            wait(SC_ZERO_TIME);
        }
    }
    void _try_and_post(const char *proc_name)
    {
        if (s.trywait() == -1)
            s.wait();
        std::cout << sc_time_stamp() << ": locked by " << proc_name << ", value is " << s.get_value() << std::endl;
        wait(1, SC_SEC);
        s.post();
        std::cout << sc_time_stamp() << ": unlocked by " << proc_name << ", value is " << s.get_value() << std::endl;
    }
    void thread_3()
    {
        while (true)
        {
            this->_try_and_post("thread_3");
            wait(SC_ZERO_TIME);
        }
    }
};
int sc_main(int nargs, char **argv)
{
    EXAMPLE_SEMAPHORE semaphore("semaphore");
    sc_start(4, SC_SEC);
    return 0;
}