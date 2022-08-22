#include <systemc>
using namespace sc_core;
int sc_main(int args, char **argv)
{
    sc_set_time_resolution(1, SC_FS);

    std::cout << "1 SEC = " << sc_time(1, SC_SEC).to_default_time_units() << " SEC" << std::endl;

    std::cout << "1  MS = " << sc_time(1, SC_MS).to_default_time_units() << " SEC" << std::endl;

    std::cout << "1  US = " << sc_time(1, SC_US).to_default_time_units() << " SEC" << std::endl;

    std::cout << "1  NS = " << sc_time(1, SC_NS).to_default_time_units() << " SEC" << std::endl;

    std::cout << "1  PS = " << sc_time(1, SC_PS).to_default_time_units() << " SEC" << std::endl;

    std::cout << "1  FS = " << sc_time(1, SC_FS).to_default_time_units() << " SEC" << std::endl;

    sc_start(7261, SC_SEC);

    double t = sc_time_stamp().to_seconds();

    std::cout << (int(t) / 3600) << " hours, " << (int(t) % 60) << " minutes, " << int(t) << "seconds" << std::endl;
    return 0;
}