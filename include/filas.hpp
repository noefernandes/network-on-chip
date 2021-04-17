#ifndef FILAS_H
#define FILAS_H

#include <queue>
#include "flit.hpp"
#include "Tokenizer.hpp"

class Filas{
	public:
		std::queue<Flit> fila_1;
		std::queue<Flit> fila_2;
		std::queue<Flit> fila_3;
		std::queue<Flit> fila_4;

	Filas(){
		l_filas();
	}

	int str_to_int(std::string str){
		int number;
		std::istringstream iss(str);
		iss >> number;
		iss.clear();
		return number;
	}

	void l_filas(){
		std::ifstream arquivo("files/buffers.txt", std::fstream::in);
        std::string line;
        int cont = 0;
        while(std::getline(arquivo, line)){
            if (!line.empty()){
                Tokenizer tokenizer(line);
                std::vector<std::string> token = tokenizer.getToken();
                if(cont == 0){
	                Flit flit;
	                flit.bop_or_eop = str_to_int(token[0]);
	                flit.x_dir = str_to_int(token[1]);
	                flit.y_dir = str_to_int(token[2]);
	            	fila_1.push(flit);
	            }else if(cont == 1){
	            	Flit flit;
	                flit.bop_or_eop = str_to_int(token[0]);
	                flit.x_dir = str_to_int(token[1]);
	                flit.y_dir = str_to_int(token[2]);
	            	fila_1.push(flit);
	            }else if(cont == 2){
	            	Flit flit;
	                flit.bop_or_eop = str_to_int(token[0]);
	                flit.x_dir = str_to_int(token[1]);
	                flit.y_dir = str_to_int(token[2]);
	            	fila_1.push(flit);
	            }else if(cont == 3){
	            	Flit flit;
	                flit.bop_or_eop = str_to_int(token[0]);
	                flit.x_dir = str_to_int(token[1]);
	                flit.y_dir = str_to_int(token[2]);
	            	fila_1.push(flit);
	            }

            }else{
            	cont++;
            }
        }
        arquivo.close();
	}

	std::queue<Flit>& get_fila_1(){ return fila_1; }
	std::queue<Flit>& get_fila_2(){ return fila_2; }
	std::queue<Flit>& get_fila_3(){ return fila_3; }
	std::queue<Flit>& get_fila_4(){ return fila_4; }
};

#endif
