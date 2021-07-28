#include <iostream>
#include "Mips.h"

using namespace std;

Mips::Mips(){
	reset();
}

Mips::~Mips(){
}

void Mips::reset(){
	this->qtdInstrucoes = 0;
	this->pc = 0;
}

void Mips::armazenaInstrucao(long int instrucao){
	if(this->qtdInstrucoes != 128){
		this->memoria_instrucoes[this->qtdInstrucoes] = instrucao;
		this->qtdInstrucoes++;
	}else{
		cout << "Limite de instruções atingido" << endl;
	}
}

void Mips::imprimeInstrucoes(){
	for(int i=0; i < qtdInstrucoes;i++)
		cout << memoria_instrucoes[i] << endl;
}

int Mips::getQtdInstrucoes(){
	return this->qtdInstrucoes;
}