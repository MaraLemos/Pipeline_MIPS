#include <iostream>
#include "Mips.h"

using namespace std;

Mips::Mips(){
	reset();
}

Mips::~Mips(){
	arquivoSaida.close();
}

void Mips::reset(){
	this->qtdInstrucoes = 0;
	this->pc = 0;
	this->pcSrc = 0;
	this->clock = 0;

	//Inicia valores dos registradores com zero
	for(int i=0;i< 32;i++){
		banco_registradores[i] = 0;
	}

	for(int i=0;i<128;i++){
		memoria_dados[i] = 0;
	}

	banco_registradores[29] = 128*4; // SP

	arquivoSaida.open("saida.txt",ios::out | ios::trunc);

	unidade_controle.regDst = 2;
    unidade_controle.ALUOp1 = 2;
    unidade_controle.ALUOp0 = 2;
    unidade_controle.ALUSrc = 2;
    unidade_controle.Branch = 2;
    unidade_controle.MemRead = 2;
    unidade_controle.MemWrite = 2;
    unidade_controle.RegWrite = 2;
    unidade_controle.MemtoReg = 2;
    unidade_controle.jump = 2;
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

	clock++;

	if(pcSrc == 1)
		pc = rp3.pc;


	cout << "PC: " << pc << endl;

	//Lê memória de instruções
	long int instrucao = memoria_instrucoes[pc/4];

	cout << "Instrução sendo executada: " << instrucao << endl;
	cout << "Ciclo de clock atual: " << clock << endl;
	cout << "Conteudo dos registradores no estágio 1: " << endl;
	for(int i =0;i< 32; i++){
		cout << registradores[i] << " : " << banco_registradores[i] << endl;
	}

	if(this->arquivoSaida.is_open()){

		arquivoSaida << "___________________________________________________________________________" << endl;
		arquivoSaida << "PC: " << pc << endl;
		arquivoSaida << "Instrução sendo executada: " << instrucao << endl;
		arquivoSaida << "Ciclo de clock atual: " << clock << endl;
		arquivoSaida << "Conteudo dos registradores no estágio 1: " << endl;
		for(int i =0;i< 32; i++){
			arquivoSaida << registradores[i] << " : " << banco_registradores[i] << endl;
		}
		arquivoSaida << "Contéudo da memória de dados: " << endl;
		for(int i =0;i< 128; i++){
			if(memoria_dados[i] != 0){
				arquivoSaida << "Posição da memória: " << i << " : " << memoria_dados[i] << endl;
			}
		}
		arquivoSaida << "Posições não especificadas estão vazias" << endl;
		arquivoSaida << "Sinal de controle estágio 1: " << endl;
		arquivoSaida << "pcSrc : " << pcSrc << endl;
	}

	//Incrementa valor de pc
	pc = pc + 4;

	//Armazena informações em registrador IF/ID
	rp1.pc = pc;
	rp1.instrucao = instrucao;
}

void Mips::estagio2(){

	clock++;

	//Gera sinais de controle
	int opcode = (rp1.instrucao & 0xfc000000) >> 26;
	geraSinaisControle(opcode);

	long int constant_or_address = 0;
	int rd = 0, rt = 0, rs;

	rp2.pc = rp1.pc;

	//Desvio incondicional
	if(unidade_controle.jump == 1){ //Tipo-J

		banco_registradores[31] = pc; //Registrador $ra
		pc = (rp1.instrucao & 0x03ffffff);

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

	//WB
	rp2.RegWrite = unidade_controle.RegWrite;
	rp2.MemtoReg = unidade_controle.MemtoReg;
	//M
	rp2.Branch = unidade_controle.Branch;
	rp2.MemRead = unidade_controle.MemRead;
	rp2.MemWrite = unidade_controle.MemWrite;
	//EX
	rp2.regDst = unidade_controle.regDst;
	rp2.ALUOp1 = unidade_controle.ALUOp1;
	rp2.ALUOp0 = unidade_controle.ALUOp0;
	rp2.ALUSrc = unidade_controle.ALUSrc;

	if(arquivoSaida.is_open()){

		arquivoSaida << "Sinal de controle estágio 2: " << endl;
		arquivoSaida << "jump : " << unidade_controle.jump << endl;
	}
}

void Mips::estagio3() {

	clock++;

	// lê os valores do ALUOp
	int ALUOp0 = rp2.ALUOp0;
	int ALUOp1 = rp2.ALUOp1;

	// gera ALU control
	int ALU_control;

	if(ALUOp0 == 0 && ALUOp1 == 0) // lw, sw
		ALU_control = 2;

	else if(ALUOp0 == 1 && ALUOp1 == 0) // beq
		ALU_control = 6;

	else if(ALUOp0 == 0 && ALUOp1 == 1) { // Tipo-R
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

	if(rp2.ALUSrc = 1)
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
	rp3.pc = rp2.pc + (rp2.constant_or_address << 2);
	if(rp2.regDst == 0)
		rp3.rd_rt = rp2.rt;
	else if(rp2.regDst == 1)
		rp3.rd_rt = rp2.rd;
	rp3.ALU_result = ALU_result;
	rp3.ALU_zero = (ALU_result == 0 || ALU_control == 6) ? 1 : 0; // não tenho certeza
	rp3.datart = rp2.datart;

	//WB
	rp3.RegWrite = rp2.RegWrite;
	rp3.MemtoReg = rp2.MemtoReg;
	//M
	rp3.Branch = rp2.Branch;
	rp3.MemRead = rp2.MemRead;
	rp3.MemWrite = rp2.MemWrite;

	if(arquivoSaida.is_open()){

		arquivoSaida << "Sinais de controle estágio 3: " << endl;
		arquivoSaida << "regDst : " << rp2.regDst << endl;
		arquivoSaida << "ALUOp : " << rp2.ALUOp1 << rp2.ALUOp0 << endl;
		arquivoSaida << "ALUSrc : " << rp2.ALUSrc << endl;
	}
}

void Mips::estagio4() {

	clock++;

	pcSrc = (rp3.Branch && rp3.ALU_zero) ? 1 : 0;

	if(rp3.MemWrite == 1)
		this->memoria_dados[rp3.ALU_result] = rp3.datart;
	else if(rp3.MemRead == 1)
		rp4.data = this->memoria_dados[rp3.ALU_result];
	
	rp4.rd_rt = rp3.rd_rt;
	rp4.ALU_result = rp3.ALU_result;

	//WB
	rp4.RegWrite = rp3.RegWrite;
	rp4.MemtoReg = rp3.MemtoReg;

	if(arquivoSaida.is_open()){

		arquivoSaida << "Sinais de controle estágio 4: " << endl;
		arquivoSaida << "Branch : " << rp3.Branch << endl;
		arquivoSaida << "MemRead : " << rp3.MemRead << endl;
		arquivoSaida << "MemWrite : " << rp3.MemWrite << endl;
	}
}

void Mips::estagio5() {

	clock++;

	if(rp4.RegWrite == 1){
		if(rp4.MemtoReg == 1)
			banco_registradores[rp4.rd_rt] = rp4.data;
		else
			banco_registradores[rp4.rd_rt] = rp4.ALU_result;
	}

	if(arquivoSaida.is_open()){

		arquivoSaida << "Sinais de controle estágio 5: " << endl;
		arquivoSaida << "RegWrite : " << rp4.RegWrite << endl;
		arquivoSaida << "MemtoReg : " << rp4.MemtoReg << endl;
	}
}
