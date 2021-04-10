#include <systemc.h>
#include <queue>
#include <vector>
#include "round_ptr.hpp"
#include "filas.hpp"

SC_MODULE(roteador){
	sc_in_clk clk;
	
	//Classe que armazena as filas de cada canal
	Filas* filas;

	//Ponteiros de cada fila
	RoundPtr* roundPtr;

	//Vetor que vai inidicar quais canais tem requisicao
	std::vector<bool> requisicoes_1 = {false, false, false, false};
	std::vector<bool> requisicoes_2 = {false, false, false, false};
	std::vector<bool> requisicoes_3 = {false, false, false, false};
	std::vector<bool> requisicoes_4 = {false, false, false, false};

	/* -------------------------------- Esquerda ---------------------------------*/
	sc_in<bool> val_1;
	sc_out<bool> ack_1;
	//1: bop, 2 dado, 3 eop.
	sc_in<sc_uint<3>> bop_or_eop_1;
	//Especifica direcoes e valor do deslocamento.
	sc_in<bool> x_dir_1;
	sc_in<sc_uint<8>> x_mod_1;
	sc_in<bool> y_dir_1;
	sc_in<sc_uint<8>> y_mod_1;

	/*--------------------------------- Direita ----------------------------------*/
	sc_in<bool> val_2;
	sc_out<bool> ack_2;
	//1: bop, 2 dado, 3 eop.
	sc_in<sc_uint<3>> bop_or_eop_2;
	//Especifica direcoes e valor do deslocamento.
	sc_in<bool> x_dir_2;
	sc_in<sc_uint<8>> x_mod_2;
	sc_in<bool> y_dir_2;
	sc_in<sc_uint<8>> y_mod_2;

	/*----------------------------------- Cima -----------------------------------*/
	sc_in<bool> val_3;
	sc_out<bool> ack_3;
	//1: bop, 2 dado, 3 eop.
	sc_in<sc_uint<3>> bop_or_eop_3;
	//Especifica direcoes (false: esquerda ou cima), (true: direita ou baixo) e valor do deslocamento.
	sc_in<bool> x_dir_3;
	sc_in<sc_uint<8>> x_mod_3;
	sc_in<bool> y_dir_3;
	sc_in<sc_uint<8>> y_mod_3;

	/*----------------------------------- Baixo ----------------------------------*/
	sc_in<bool> val_4;
	sc_out<bool> ack_4;
	//1: bop, 2 dado, 3 eop.
	sc_in<sc_uint<3>> bop_or_eop_4;
	//Especifica direcoes e valor do deslocamento.
	sc_in<bool> x_dir_4;
	sc_in<sc_uint<8>> x_mod_4;
	sc_in<bool> y_dir_4;
	sc_in<sc_uint<8>> y_mod_4; 

	//Sempre aceita os dados.
	void receber_dado(){
		if(val_1){
			Phit phit;
			phit.bop_or_eop = bop_or_eop_1.read();
			phit.x_dir = x_dir_1.read();
			phit.x_mod = x_mod_1.read();
			phit.y_dir = y_dir_1.read();
			phit.y_mod = y_mod_1.read();

			filas->fila_1.push(phit);
			ack_1 = true;
		}

		if(val_2){
			Phit phit;
			phit.bop_or_eop = bop_or_eop_2.read();
			phit.x_dir = x_dir_2.read();
			phit.x_mod = x_mod_2.read();
			phit.y_dir = y_dir_2.read();
			phit.y_mod = y_mod_2.read();

			filas->fila_2.push(phit);
			ack_2 = true;
		}

		if(val_3){
			Phit phit;
			phit.bop_or_eop = bop_or_eop_3.read();
			phit.x_dir = x_dir_3.read();
			phit.x_mod = x_mod_3.read();
			phit.y_dir = y_dir_3.read();
			phit.y_mod = y_mod_3.read();

			filas->fila_3.push(phit);
			ack_3 = true;
		}

		if(val_4){
			Phit phit;
			phit.bop_or_eop = bop_or_eop_4.read();
			phit.x_dir = x_dir_4.read();
			phit.x_mod = x_mod_4.read();
			phit.y_dir = y_dir_4.read();
			phit.y_mod = y_mod_4.read();

			filas->fila_4.push(phit);
			ack_4 = true;
		}
	}

	//Algoritmo de arbitragem
	void arbitrar(){

			int x_dir_canal_1 = filas->fila_1.front().x_dir;
			int y_dir_canal_1 = filas->fila_1.front().y_dir;
		
			int x_dir_canal_2 = filas->fila_2.front().x_dir;
			int y_dir_canal_2 = filas->fila_2.front().y_dir;

			int x_dir_canal_3 = filas->fila_3.front().x_dir;
			int y_dir_canal_3 = filas->fila_3.front().y_dir;
		
			int x_dir_canal_4 = filas->fila_4.front().x_dir;
			int y_dir_canal_4 = filas->fila_4.front().y_dir;

			//Verifica se algum dos phits na frente das filas de cada canal
			//vão para esquerda ou para direita. 
			requisicoes_1[1] = x_dir_canal_2 == false;
			requisicoes_1[2] = x_dir_canal_3 == false;
			requisicoes_1[3] = x_dir_canal_4 == false;
			
			requisicoes_2[0] = x_dir_canal_1 == true;
			requisicoes_2[2] = x_dir_canal_3 == true;
			requisicoes_2[3] = x_dir_canal_4 == true;
	}

	SC_CTOR(roteador){
		SC_METHOD(receber_dado);

		sensitive << clk;
	}
};