#include <systemc.h>

SC_MODULE(controle) {
    sc_in_clk clk;
    

    void print_counter(){
        wait();
        cout << "#" << sc_time_stamp() << " :: Current counter Value " << endl;
        sc_stop();
    }

    SC_CTOR(controle) {
        std::cout << "starting processor activity..." << std::endl;
        cout << "#" << sc_time_stamp() << " :: Current counter Value 0" << endl;

        SC_CTHREAD(print_counter, clk.pos());

        sensitive << clk;
    }
};