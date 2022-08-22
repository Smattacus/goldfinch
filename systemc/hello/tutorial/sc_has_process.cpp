#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE_A){
    MODULE_A(sc_module_name name){
        std::cout << this->name() << ", no SC_CTOR or SC_HAS_PROCESS" << std::endl;
}
}
;

SC_MODULE(MODULE_B1){
    SC_CTOR(MODULE_B1){
        SC_METHOD(func_b);
}
void func_b()
{
    std::cout << name() << ", SC_CTOR" << std::endl;
}
}
;

SC_MODULE(MODULE_B2)
{
    SC_HAS_PROCESS(MODULE_B2);

    MODULE_B2(sc_module_name name)
    {
        SC_METHOD(func_b);
    }
    void func_b()
    {
        std::cout << name() << ", SC_HAS_PROCESS" << std::endl;
    }
};

SC_MODULE(MODULE_C)
{
    const int i;

    SC_HAS_PROCESS(MODULE_C);

    MODULE_C(sc_module_name name, int i) : i(i)
    {
        SC_METHOD(func_c);
    }
    void func_c()
    {
        std::cout << name() << ", additional input argument" << std::endl;
    }
};

SC_MODULE(MODULE_D1)
{

    SC_CTOR(MODULE_D1);
    void func_d()
    {
        std::cout << this->name() << ", SC_CTOR inside header, constructor defined outside header." << std::endl;
    }
};

MODULE_D1::MODULE_D1(sc_module_name name) : sc_module(name)
{
    SC_METHOD(func_d);
}

SC_MODULE(MODULE_D2)
{
    SC_HAS_PROCESS(MODULE_D2);
    MODULE_D2(sc_module_name);
    void func_d()
    {
        std::cout << this->name() << ", SC_CTOR inside header, constructor defined outside header." << std::endl;
    }
};

MODULE_D2::MODULE_D2(sc_module_name name) : sc_module(name)
{
    SC_METHOD(func_d);
}

SC_MODULE(MODULE_E)
{
    MODULE_E(sc_module_name name);

    void func_e()
    {
        std::cout << this->name() << ", SC_HAS_PROCESS outside header, CANNOT use SC_CTOR" << std::endl;
    }
};

MODULE_E::MODULE_E(sc_module_name name)
{
    SC_HAS_PROCESS(MODULE_E);
    SC_METHOD(func_e);
}

int sc_main(int, char *[])
{
    MODULE_A module_a("module_a");
    MODULE_B1 module_b1("module_b1");
    MODULE_B2 module_b2("module_b2");
    MODULE_C module_c("module_c", 1);
    MODULE_D1 module_d1("module_d1");
    MODULE_D2 module_d2("module_d2");
    MODULE_E module_e("module_e");
    sc_start();
    return 0;
}