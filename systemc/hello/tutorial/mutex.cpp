#include <systemc>
using namespace sc_core;

SC_MODULE(MUTEX_EXAMPLE)
{
    sc_mutex m;
    SC_CTOR(MUTEX_EXAMPLE)
    {
        SC_THREAD(thread_1);
        SC_THREAD(thread_2);
    }
    void thread_1()
    {
        while (true)
        {
            this->_try_to_get_mutex("thread_1");
            wait(1, SC_SEC);
            m.unlock();
            std::cout << sc_time_stamp() << ": unlocked by thread_1" << std::endl;
            wait(SC_ZERO_TIME);
        }
    }
    void thread_2()
    {
        while (true)
        {
            this->_try_to_get_mutex("thread_2");
            wait(1, SC_SEC);
            m.unlock();
            std::cout << sc_time_stamp() << ": unlocked by thread_2" << std::endl;
            wait(SC_ZERO_TIME);
        }
    }
    void _try_to_get_mutex(const char *output_name)
    {
        if (m.trylock() == -1)
        {
            m.lock();
            std::cout << sc_time_stamp() << ": " << output_name << " obtained resource by lock()" << std::endl;
        }
        else
        {
            std::cout << sc_time_stamp() << ": " << output_name << " obtained resource by trylock()" << std::endl;
        }
    }
};
int sc_main(int nargs, char **argbv)
{
    MUTEX_EXAMPLE mutex("mutex");
    sc_start(4, SC_SEC);
    return 0;
}