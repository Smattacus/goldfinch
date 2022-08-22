// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(SUBMODULE1)
{ // a submodule that writes to channel
    sc_port<sc_signal_out_if<int>> p;
    SC_CTOR(SUBMODULE1)
    {
        SC_THREAD(writer);
    }
    void writer()
    {
        int val = 1; // init value
        while (true)
        {
            p->write(val++); // write to channel through port
            wait(1, SC_SEC);
        }
    }
};
SC_MODULE(SUBMODULE2)
{ // a submodule that reads from channel
    sc_port<sc_signal_in_if<int>> p;
    SC_CTOR(SUBMODULE2)
    {
        SC_THREAD(reader);
        sensitive << p; // triggered by value change on the channel
        dont_initialize();
    }
    void reader()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ": reads from channel, val=" << p->read() << std::endl;
            wait(); // receives from channel through port
        }
    }
};
SC_MODULE(TOP_WRITER)
{                                     // top-level module
    sc_port<sc_signal_out_if<int>> p; // port
    SUBMODULE1 sub1;                  // declares submodule
    SC_CTOR(TOP_WRITER) : sub1("sub1")
    {              // instantiate submodule
        sub1.p(p); // bind submodule's port directly to parent's port
    }
};
SC_MODULE(TOP_READER)
{
    sc_port<sc_signal_in_if<int>> p;
    SUBMODULE2 sub2;
    SC_CTOR(TOP_READER) : sub2("sub2")
    {
        sub2.p(p); // bind submodule's port directly to parent's port
    }
};

int sc_main(int, char *[])
{
    TOP_WRITER top_writer("top_writer"); // instantiate top_writer
    TOP_READER top_reader("top_reader"); // instantiate top_reader
    sc_signal<int> s;                    // define channel outside module1 and module2
    top_writer.p(s);                     // bind module1's port to channel, for writing purpose
    top_reader.p(s);                     // bind module2's port to channel, for reading purpose
    sc_start(2, SC_SEC);
    return 0;
}
