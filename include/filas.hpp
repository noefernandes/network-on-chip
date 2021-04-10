#ifndef FILAS_H
#define FILAS_H

#include <queue>
#include "phit.hpp"

class Filas{
	public:
		std::queue<Phit> fila_1;
		std::queue<Phit> fila_2;
		std::queue<Phit> fila_3;
		std::queue<Phit> fila_4;

	std::queue<Phit> get_fila_1(){ return fila_1; }
	std::queue<Phit> get_fila_2(){ return fila_2; }
	std::queue<Phit> get_fila_3(){ return fila_3; }
	std::queue<Phit> get_fila_4(){ return fila_4; }
};

#endif
