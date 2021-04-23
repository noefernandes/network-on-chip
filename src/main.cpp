#include "roteador.hpp"
#include "Control.hpp"

int sc_main(int argc, char *argv[]){
	Filas* buffers = new Filas();
	RoundPtr* roundPtr = new RoundPtr();

	sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);

	sc_signal<bool> val_1, val_2, val_3, val_4;
	sc_signal<sc_uint<3>> bop_or_eop_1, bop_or_eop_2, bop_or_eop_3, bop_or_eop_4;
	sc_signal<sc_int<3>> x_dir_1, x_dir_2, x_dir_3, x_dir_4;
	sc_signal<sc_int<3>> y_dir_1, y_dir_2, y_dir_3, y_dir_4;
	sc_signal<bool> ack_1, ack_2, ack_3, ack_4;

	sc_signal<sc_uint<3>> bop_or_eop_1_s, bop_or_eop_2_s, bop_or_eop_3_s, bop_or_eop_4_s;
	sc_signal<sc_int<3>> x_dir_1_s, x_dir_2_s, x_dir_3_s, x_dir_4_s;
	sc_signal<sc_int<3>> y_dir_1_s, y_dir_2_s, y_dir_3_s, y_dir_4_s;
	sc_signal<bool> enable;

	controle controle("controle");
	controle.clk(clock);

	roteador roteador("roteador");
	roteador.clk(clock);
	roteador.load_buffers(buffers);
	roteador.load_ptrs(roundPtr);
	roteador.val_1(val_1);
	roteador.val_2(val_2);
	roteador.val_3(val_3);
	roteador.val_4(val_1);
	roteador.bop_or_eop_1(bop_or_eop_1);
	roteador.bop_or_eop_2(bop_or_eop_2);
	roteador.bop_or_eop_3(bop_or_eop_3);
	roteador.bop_or_eop_4(bop_or_eop_4);
	roteador.x_dir_1(x_dir_1);
	roteador.x_dir_2(x_dir_2);
	roteador.x_dir_3(x_dir_3);
	roteador.x_dir_4(x_dir_4);
	roteador.y_dir_1(y_dir_1);
	roteador.y_dir_2(y_dir_2);
	roteador.y_dir_3(y_dir_3);
	roteador.y_dir_4(y_dir_4);

	roteador.bop_or_eop_1_s(bop_or_eop_1_s);
	roteador.bop_or_eop_2_s(bop_or_eop_2_s);
	roteador.bop_or_eop_3_s(bop_or_eop_3_s);
	roteador.bop_or_eop_4_s(bop_or_eop_4_s);
	roteador.x_dir_1_s(x_dir_1_s);
	roteador.x_dir_2_s(x_dir_2_s);
	roteador.x_dir_3_s(x_dir_3_s);
	roteador.x_dir_4_s(x_dir_4_s);
	roteador.y_dir_1_s(y_dir_1_s);
	roteador.y_dir_2_s(y_dir_2_s);
	roteador.y_dir_3_s(y_dir_3_s);
	roteador.y_dir_4_s(y_dir_4_s);
	roteador.ack_1(ack_1);
	roteador.ack_2(ack_2);
	roteador.ack_3(ack_3);
	roteador.ack_4(ack_4);
	
	

	sc_start();


	return 0;
}