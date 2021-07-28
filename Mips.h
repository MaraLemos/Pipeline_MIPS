#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <fstream>

class Mips{
	
	private:
		int pc, qtdInstrucoes;
		long int memoria_instrucoes[128]; //512bytes == 4096 bits
		long int memoria_dados[128];
		int banco_registradores[32];

	public:
		Mips();
		~Mips();
		void reset();
		void armazenaInstrucao(long int instrucaoCodificada);
		void imprimeInstrucoes(); //Apenas para testes
		int getQtdInstrucoes();
};

#endif