#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <fstream>
#include "Componentes.h"

class Mips{
	
	private:
		int pc, qtdInstrucoes;
		long int memoria_instrucoes[128]; //512bytes == 4096 bits
		long int memoria_dados[128];
		int banco_registradores[32];
		Control unidade_controle;

		IF_ID rp1;
		ID_EX rp2;
		EX_MEM rp3;
		MEM_WB rp4;

		void geraSinaisControle(int opcode);

	public:
		Mips();
		~Mips();
		void reset();
		void armazenaInstrucao(long int instrucaoCodificada);
		int getQtdInstrucoes();

		//Estágios pipeline
		void estagio1();
		void estagio2();
};

#endif