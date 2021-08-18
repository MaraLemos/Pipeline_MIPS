#ifndef Converte_H
#define Converte_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using  namespace std;

string registradores[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};


int binDec(string str) {
    long int dec = 0;
    
    for(int i = 0; i < str.size(); i++) {
      string aux = "";
      aux += str[i];
      dec += atoi(aux.c_str())*pow(2, (str.size()-1) -i);
    }
    
    return dec;
}

string decBin(long int val){
	string bin = "";
	
    for(int i = 0; i < 32; i++)
	    bin += "0";

	for(int i = 31; i >= 0; i--){
	    if(val % 2 == 0)
	    	bin[i] = '0';
	    else
	    	bin[i] = '1';
	    
    	val = val / 2;
	}
	return bin;
}

int complemento2(string str) {
  if(str[0] == '1') {
    bool primerio1 = false;
    for(int i = str.size()-1; i >= 0; i--) {
      if(primerio1) {
        if(str[i] == '0')
          str[i] = '1';
        else
          str[i] = '0';
      }
      
      if(str[i] == '1')
        primerio1 = true;
    }
    return -binDec(str);
  }
  return binDec(str);
}

string converteInstrucao(int val) {
    string str = decBin(val);
    string instrucao = "";
    string op = str.substr(0, 6);
    
    if(op == "000010") { // j
        int offset = binDec(str.substr(6, 26));

        instrucao += "j " + to_string(offset);
    }
    else if(op == "000011") { // jal
        int offset = binDec(str.substr(6, 26));

        instrucao += "jal " + to_string(offset);
    }
    else if(op == "100011") { // lw
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        int offset = binDec(str.substr(16, 16));

        instrucao += "lw " + rt + "," + to_string(offset) + "(" + rs + ")";
    }
    else if(op == "101011") { // sw
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        int offset = binDec(str.substr(16, 16));

        instrucao += "sw " + rt + "," + to_string(offset) + "(" + rs + ")";
    }
    else if(op == "000100") { // beq
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        int offset = binDec(str.substr(16, 16));
        
        instrucao += "beq " + rs + "," + rt + "," + to_string(offset);
    }
    else if(op == "000101") { // bne
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        int offset = binDec(str.substr(16, 16));
        
        instrucao += "bne " + rs + "," + rt + "," + to_string(offset);
    }
    else if(op == "001000") { // addi
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        int imm = complemento2(str.substr(16, 16));

        instrucao += "addi " + rt + "," + rs + "," + to_string(imm);
    }
    else if(op == "000000") { // Tipo-R ou jr
        string rs = registradores[binDec(str.substr(6, 5))];
        string rt = registradores[binDec(str.substr(11, 5))];
        string rd = registradores[binDec(str.substr(16, 5))];
        
        string funct = str.substr(26, 6);

        if(funct == "001000") { // jr
            instrucao += "jr " + rs;
        }
        else if(funct == "100000") { // add
            instrucao += "add " + rd + "," + rs + "," + rt;
        }
        else if(funct == "100010") { // sub
            instrucao += "sub " + rd + "," + rs + "," + rt;
        }
        else if(funct == "100100") { // and
            instrucao += "and " + rd + "," + rs + "," + rt;
        }
        else if(funct == "100101") { // or
            instrucao += "or " + rd + "," + rs + "," + rt;
        }
        else if(funct == "101010") { // slt
            instrucao += "slt " + rd + "," + rs + "," + rt;
        }
        else if(funct == "000000") { // sll
            int sa = binDec(str.substr(21, 5));
            instrucao += "sll " + rd + "," + rt + "," + to_string(sa);
        }
    }

    return instrucao;
}

#endif