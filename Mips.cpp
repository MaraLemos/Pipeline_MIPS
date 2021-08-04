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
			unidade_controle.jump = 0;
        break;

        case 2: //j
        break;

        case 3: // jal
			unidade_controle.regDst = 2; //O num 2 representa o não importa
		    unidade_controle.ALUOp1 = 2;
		    unidade_controle.ALUOp0 = 2;
		    unidade_controle.ALUSrc = 2;
		    unidade_controle.Branch = 2;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 0;
		    unidade_controle.MemtoReg = 2;
		    unidade_controle.jump = 1;
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
			unidade_controle.jump = 0;
        break;

        case 5: // bne
			unidade_controle.regDst = 2; //O num 2 representa o não importa
		    unidade_controle.ALUOp1 = 0;
		    unidade_controle.ALUOp0 = 1;
		    unidade_controle.ALUSrc = 0;
		    unidade_controle.Branch = 1;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 0;
		    unidade_controle.MemtoReg = 2; //O num 2 representa o não importa
		    unidade_controle.jump = 0;
        break;

        case 8: // addi
			unidade_controle.regDst = 0;
		    unidade_controle.ALUOp1 = 0;
		    unidade_controle.ALUOp0 = 0;
		    unidade_controle.ALUSrc = 1;
		    unidade_controle.Branch = 0;
		    unidade_controle.MemRead = 0;
		    unidade_controle.MemWrite = 0;
		    unidade_controle.RegWrite = 1;
		    unidade_controle.MemtoReg = 0;
		    unidade_controle.jump = 0;
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
			unidade_controle.jump = 0;
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
			unidade_controle.jump = 0;
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

	//Desvio incondicional
	if(unidade_controle.jump == 1){ //Tipo-J

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

void Mips::estagio3() {
	// lê os valores do ALUOp
	int ALUOp0 = unidade_controle.ALUOp0;
	int ALUOp1 = unidade_controle.ALUOp1;

	// gera ALU control
	int ALU_control;

	if(ALUOp0 == 0 && ALUOp1 == 0) // lw, sw
		ALU_control = 2;
	
	else if(ALUOp0 == 0 && ALUOp1 == 1) // beq
		ALU_control = 6;
	
	else if(ALUOp0 == 1 && ALUOp1 == 0) { // Tipo-R
		int funct = (rp1.instrucao & 0x3f);

		if(funct == 32) // add
			ALU_control = 2;
		else if(funct == 34) // sub
			ALU_control= 6;
		else if(funct == 36) // and
			ALU_control = 0;
		else if(funct == 37) // or
			ALU_control = 1;
		else if(funct == 42) // slt
			ALU_control = 7;
	}

	// gera resultado da ALU
	int ALU_result;

	int op1 = rp2.datars;
	int op2 = rp2.datart;

	if(unidade_controle.ALUSrc = 1)
		op2 = rp2.constant_or_address;

	
	if(ALU_control == 2) // add
		ALU_result = op1 + op2;
	else if(ALU_control == 6) // sub
		ALU_result = op1 - op2;
	else if(ALU_control == 0) // and
		ALU_result = op1 & op2;
	else if(ALU_control == 1) // or
		ALU_result = op1 | op2;
	else if(ALU_control == 7) // slt
		ALU_result = (op1 < op2) ? 1 : 0;

	//armazena informações em registrador EX_MEM
	rp3.pc = rp2.pc + (rp2.constant_or_address >> 2); // não tenho certeza
	if(unidade_controle.regDst == 0)
		rp3.rd_rt = rp2.rt;
	else if(unidade_controle.regDst == 1)
		rp3.rd_rt = rp2.rd;
	rp3.ALU_result = ALU_result;
	rp3.ALU_zero = (ALU_result == 0 || ALU_control == 6) ? 1 : 0; // não tenho certeza
	rp3.datart = rp2.datart;
}