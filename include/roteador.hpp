#include <systemc.h>
#include <queue>
#include <vector>
#include "round_ptr.hpp"
#include "filas.hpp"

SC_MODULE(roteador){
	sc_in_clk clk;
	sc_out<bool> enable;

	
	//Classe que armazena as filas de cada canal
	Filas* filas;

	//Ponteiros de cada fila
	RoundPtr* roundPtr;

	//Vetor que vai inidicar quais canais tem requisicao false, false, false, false
	std::vector<bool> requisicoes_1 = {true, true, true, true};
	std::vector<bool> requisicoes_2 = {true, true, true, true};
	std::vector<bool> requisicoes_3 = {true, true, true, true};
	std::vector<bool> requisicoes_4 = {true, true, true, true};

	/*---------------------------   Portas de entrada   ---------------------------*/
	/* -------------------------------- Esquerda ---------------------------------*/
	sc_in<bool> val_1{"val_1"};
	sc_out<bool> ack_1{"ack_1"};
	//1: bop, 2 dado, 3 eop.
	sc_in<sc_uint<3>> bop_or_eop_1{"bop_or_eop_1"};
	//(0: nenhuma direção, -1: esquerda ou cima, (1: direita ou baixo).
	sc_in<sc_int<3>> x_dir_1{"x_dir_1"};
	sc_in<sc_int<3>> y_dir_1{"y_dir_1"};

	/*--------------------------------- Direita ----------------------------------*/
	sc_in<bool> val_2{"val_2"};
	sc_out<bool> ack_2{"ack_2"};
	sc_in<sc_uint<3>> bop_or_eop_2{"bop_or_eop_2"};
	sc_in<sc_int<3>> x_dir_2{"x_dir_2"};
	sc_in<sc_int<3>> y_dir_2{"y_dir_2"};

	/*----------------------------------- Cima -----------------------------------*/
	sc_in<bool> val_3{"val_3"};
	sc_out<bool> ack_3{"ack_3"};
	sc_in<sc_uint<3>> bop_or_eop_3{"bop_or_eop_3"};
	sc_in<sc_int<3>> x_dir_3{"x_dir_3"};
	sc_in<sc_int<3>> y_dir_3{"y_dir_3"};

	/*----------------------------------- Baixo ----------------------------------*/
	sc_in<bool> val_4{"val_4"};
	sc_out<bool> ack_4{"ack_4"};
	sc_in<sc_uint<3>> bop_or_eop_4{"bop_or_eop_4"};
	sc_in<sc_int<3>> x_dir_4{"x_dir_4"};
	sc_in<sc_int<3>> y_dir_4{"y_dir_4"}; 


	/*---------------------------   Portas de saida   ----------------------------*/
	/* -------------------------------- Esquerda ---------------------------------*/
	//1: bop, 2 dado, 3 eop.
	sc_out<sc_uint<3>> bop_or_eop_1_s{"bop_or_eop_1_s"};
	//(0: nenhuma direção, -1: esquerda ou cima, (1: direita ou baixo).
	sc_out<sc_int<3>> x_dir_1_s{"x_dir_1_s"};
	sc_out<sc_int<3>> y_dir_1_s{"y_dir_1_s"};

	/* -------------------------------- Direita ---------------------------------*/
	//1: bop, 2 dado, 3 eop.
	sc_out<sc_uint<3>> bop_or_eop_2_s{"bop_or_eop_2_s"};
	//(0: nenhuma direção, -1: esquerda ou cima, (1: direita ou baixo).
	sc_out<sc_int<3>> x_dir_2_s{"x_dir_2_s"};
	sc_out<sc_int<3>> y_dir_2_s{"y_dir_2_s"};

	//1: bop, 2 dado, 3 eop.
	/* -------------------------------- Cima ------------------------------------*/
	sc_out<sc_uint<3>> bop_or_eop_3_s{"bop_or_eop_3_s"};
	//(0: nenhuma direção, -1: esquerda ou cima, (1: direita ou baixo).
	sc_out<sc_int<3>> x_dir_3_s{"x_dir_3_s"};
	sc_out<sc_int<3>> y_dir_3_s{"y_dir_3_s"};


	//1: bop, 2 dado, 3 eop.
	/* -------------------------------- Baixo-- ---------------------------------*/
	sc_out<sc_uint<3>> bop_or_eop_4_s{"bop_or_eop_4_s"};
	//(0: nenhuma direção, -1: esquerda ou cima, (1: direita ou baixo).
	sc_out<sc_int<3>> x_dir_4_s{"x_dir_4_s"};
	sc_out<sc_int<3>> y_dir_4_s{"y_dir_4_s"};

	//Carrega a memória
	void load_buffers(Filas* f){
		filas = f;
	}

	void load_ptrs(RoundPtr* rPtr){
		roundPtr = rPtr;
	}

	//Sempre aceita os dados.
	void receber_dado(){
		if(val_1){
			Flit flit;
			flit.bop_or_eop = bop_or_eop_1.read();
			flit.x_dir = x_dir_1.read();
			flit.y_dir = y_dir_1.read();

			filas->fila_1.push(flit);
			ack_1 = true;
		}

		if(val_2){
			Flit flit;
			flit.bop_or_eop = bop_or_eop_2.read();
			flit.x_dir = x_dir_2.read();
			flit.y_dir = y_dir_2.read();

			filas->fila_2.push(flit);
			ack_2 = true;
		}

		if(val_3){
			Flit flit;
			flit.bop_or_eop = bop_or_eop_3.read();
			flit.x_dir = x_dir_3.read();
			flit.y_dir = y_dir_3.read();

			filas->fila_3.push(flit);
			ack_3 = true;
		}

		if(val_4){
			Flit flit;
			flit.bop_or_eop = bop_or_eop_4.read();
			flit.x_dir = x_dir_4.read();
			flit.y_dir = y_dir_4.read();

			filas->fila_4.push(flit);
			ack_4 = true;
		}
	}

	//Algoritmo de arbitragem
	void rotear_e_arbitrar(){
		//pegando as coordenadas xy dos primeiros flits dos buffers
		int x_dir_canal_1 = filas->fila_1.front().x_dir;
		int y_dir_canal_1 = filas->fila_1.front().y_dir;
		int bop_or_eop_canal_1 = filas->fila_1.front().bop_or_eop;

		int x_dir_canal_2 = filas->fila_2.front().x_dir;
		int y_dir_canal_2 = filas->fila_2.front().y_dir;
		int bop_or_eop_canal_2 = filas->fila_2.front().bop_or_eop;

		int x_dir_canal_3 = filas->fila_3.front().x_dir;
		int y_dir_canal_3 = filas->fila_3.front().y_dir;
		int bop_or_eop_canal_3 = filas->fila_3.front().bop_or_eop;
	
		int x_dir_canal_4 = filas->fila_4.front().x_dir;
		int y_dir_canal_4 = filas->fila_4.front().y_dir;
		int bop_or_eop_canal_4 = filas->fila_4.front().bop_or_eop;


		//Round robin para cada porta
		if(requisicoes_1[roundPtr->ptr_1]){ 
			bop_or_eop_1_s.write(bop_or_eop_canal_1);
			x_dir_1_s.write(x_dir_canal_1);
			y_dir_1_s.write(y_dir_canal_1);
			filas->fila_1.pop();
			std::cout << bop_or_eop_1_s << " " << x_dir_1_s << " " << y_dir_1_s << "\n";
		}else{
			roundPtr->ptr_1++;
		}

		if(requisicoes_2[roundPtr->ptr_2]){
			bop_or_eop_2_s.write(bop_or_eop_canal_2);
			x_dir_2_s.write(x_dir_canal_2);
			y_dir_2_s.write(y_dir_canal_2);
			filas->fila_2.pop();
			std::cout << bop_or_eop_2_s << " " << x_dir_2_s << " " << y_dir_2_s << "\n";	
		}else{
			roundPtr->ptr_2++;
		}

		if(requisicoes_3[roundPtr->ptr_3]){
			bop_or_eop_3_s.write(bop_or_eop_canal_3);
			x_dir_3_s.write(x_dir_canal_3);
			y_dir_3_s.write(y_dir_canal_3);
			filas->fila_3.pop();
			std::cout << bop_or_eop_3_s << " " << x_dir_3_s << " " << y_dir_3_s << "\n";
		}else{
			roundPtr->ptr_3++;
		}

		if(requisicoes_4[roundPtr->ptr_4]){
			bop_or_eop_4_s.write(bop_or_eop_canal_4);
			x_dir_4_s.write(x_dir_canal_4);
			y_dir_4_s.write(y_dir_canal_4);
			filas->fila_4.pop();
			std::cout << bop_or_eop_4_s << " " << x_dir_4_s << " " << y_dir_4_s << "\n";
		}else{
			roundPtr->ptr_4++;
		}

		enable.write(true);
	}

	SC_CTOR(roteador){
		SC_METHOD(receber_dado);
		SC_METHOD(rotear_e_arbitrar);

		sensitive << val_1 << clk;
	}
};