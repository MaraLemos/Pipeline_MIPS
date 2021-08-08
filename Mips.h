#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include "Componentes.h"

using namespace std;

class Mips{

	private:
		int pc, qtdInstrucoes, pcSrc, clock;
		long int memoria_instrucoes[128]; //512bytes == 4096 bits
		long int memoria_dados[128];
		int banco_registradores[32];
		string registradores[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

		Control unidade_controle;

		IF_ID rp1;
		ID_EX rp2;
		EX_MEM rp3;
		MEM_WB rp4;

		void geraSinaisControle(int opcode);

		ofstream arquivoSaida;

	public:
		Mips();
		~Mips();
		void reset();
		void armazenaInstrucao(long int instrucaoCodificada);
		int getQtdInstrucoes();
		bool existeInstrucao();
		
		//Estágios pipeline
		void estagio1();
		void estagio2();
		void estagio3();
		void estagio4();
		void estagio5();
};

#endif
