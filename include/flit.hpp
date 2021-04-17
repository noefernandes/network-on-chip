#include <systemc.h>

struct Flit{
	//1: bop, 2: dado, 3 eop.
	int bop_or_eop;
	
	//Especifica direcoes e valor do deslocamento.
	//x_dir = false (esquerda), x_dir = true (direita).
	//y_dir = false (cima), y_dir = true (baixo).
	int x_dir;
	int x_mod;
	int y_dir;
	int y_mod;
};