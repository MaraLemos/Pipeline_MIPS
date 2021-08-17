#ifndef Converte_H
#define Converte_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using  namespace std;

string registradores[32] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};


int binDec(string str) {
    int dec = 0;
    
    for(int i = 0; i < str.size(); i++) {
      string aux = "";
      aux += str[i];
      dec += atoi(aux.c_str())*pow(2, (str.size()-1) -i);
    }
    
    return dec;
}

string converteInstrucao(string str) {
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
        int imm = binDec(str.substr(16, 16));

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
            instrucao += "sll " + rd + "," + rs + "," + rt;
        }
    }

    return instrucao;
}

#endif