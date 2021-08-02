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

	//Inicia valores dos registradores com zero
	for(int i=0;i< 32;i++)
		banco_registradores[i] = 0;
}

int Mips::getQtdInstrucoes(){
	return this->qtdInstrucoes;
}

void Mips::armazenaInstrucao(long int instrucao){
	if(this->qtdInstrucoes != 128){
		this->memoria_instrucoes[this->qtdInstrucoes] = instrucao;
		this->qtdInstrucoes++;
	}else{
		cout << "Limite de instruções atingido" << endl;
	}
}

void Mips::geraSinaisControle(int opcode){
	switch(opcode){

        case 0: //add,sub,and,or,slt,sll, jr
	        unidade_controle.regDst = 1;
		    unidade_controle.ALUOp1 = 1;
		    unidade_controle.ALUOp0 = 0;
		    unidade_controle.ALUSrc = 0;
		    unidade_controle.Branch = 0;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 1;
		    unidade_controle.MemtoReg = 0;
        break;

        case 2: //j
        break;

        case 3: // jal
        break;

        case 4: // beq
        	unidade_controle.regDst = 2; //O num 2 representa o não importa
		    unidade_controle.ALUOp1 = 0;
		    unidade_controle.ALUOp0 = 1;
		    unidade_controle.ALUSrc = 0;
		    unidade_controle.Branch = 1;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 0;
		    unidade_controle.MemtoReg = 2; //O num 2 representa o não importa
        break;

        case 5: // bne
        break;

        case 8: // addi
        break;

        case 35: // lw
        	unidade_controle.regDst = 0;
		    unidade_controle.ALUOp1 = 0;
		    unidade_controle.ALUOp0 = 0;
		    unidade_controle.ALUSrc = 1;
		    unidade_controle.Branch = 0;
		    unidade_controle.MemRead = 1;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 1;
		    unidade_controle.MemtoReg = 1;
        break;

        case 43: // sw
        	unidade_controle.regDst = 2; //O num 2 representa o não importa
		    unidade_controle.ALUOp1 = 0;
		    unidade_controle.ALUOp0 = 0;
		    unidade_controle.ALUSrc = 1;
		    unidade_controle.Branch = 0;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 1;
		    unidade_controle.RegWrite = 0;
		    unidade_controle.MemtoReg = 2; //O num 2 representa o não importa
        break;        
	}
}

void Mips::estagio1(){

	//Lê memória de instruções
	long int instrucao = memoria_instrucoes[pc/4];

	//Incrementa valor de pc
	pc = pc + 4;

	//Armazena informações em registrador IF/ID
	rp1.pc = pc;
	rp1.instrucao = instrucao;
}

void Mips::estagio2(){

	//Gera sinais de controle
	int opcode = (rp1.instrucao & 0xfc000000) >> 26;
	geraSinaisControle(opcode);

	long int constant_or_address = 0;
	int rd = 0, rt = 0, rs;

	rp2.pc = rp1.pc;

	if(opcode == 2 || opcode == 3){ //Tipo-J

		rp2.pc = (rp1.instrucao & 0x03ffffff);

	}else{

		//Lê registradores
		rs = (rp1.instrucao & 0x03e00000) >> 21;
		rt = (rp1.instrucao & 0x001f0000) >> 16;

		//Extensor de sinal
		if(opcode == 8 || opcode == 35 || opcode == 43 || opcode == 4 || opcode == 5) //Tipo-I
			constant_or_address = (rp1.instrucao & 0x0000ffff);
		else //Tipo-R
			rd = (rp1.instrucao & 0x0000f800) >> 11;
	}


	//Armazena informações em registrador ID/EX
	rp2.rd = rd;
	rp2.rt = rt;
	rp2.datars = banco_registradores[rs];
	rp2.datart = banco_registradores[rt];
	rp2.constant_or_address = constant_or_address;
}