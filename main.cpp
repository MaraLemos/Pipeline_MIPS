#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //Necessario para uso da funcao toupper
#include <locale.h> //Necessario para uso da funcao setlocale
#include <string.h>
#include <fstream>

using namespace std;

/**
 * Verifica se existe uma nova opeção a ser realizada para encerrar a aplicação
 * @return bool
 *
 * @author Mara de Lemos Gomes
 */
bool novaOp() {
    char alternativa;
    cout << "\n\nVoltar ao menu inicial?\n1- Sim\t2 - Não" << endl;
    cin >> alternativa;
    if (alternativa != '1' && alternativa != '2') {
        cout << "Alternativa inválida, selecione 1 ou 2\n";
        novaOp();
    } else {
        if (alternativa == '1') {
            return true;
        } else {
            exit(0);
        }
    }
    return false;
}

/**
 * Identifica qual a instrução lida e converte os campos fixos de acordo com seu tipo(R,I ou J)
 * @return bool
 *
 * @author Mara de Lemos Gomes
 */
bool identificaInstrucao(string campo, int* instrucao){

	if(campo == "add"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
			instrucao[i] = 0;

		//shamt 00000
		for(int i=6;i < 11; i++)
			instrucao[i] = 0;

		//funct 100000
		instrucao[5] = 1;
		for(int i=0;i<5;i++)
			instrucao[i] = 0;

		return true;
	}
	if(campo == "sub"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
			instrucao[i] = 0;

		//shamt 00000
		for(int i=6;i < 11; i++)
			instrucao[i] = 0;

		//funct 100010
		instrucao[5] = 1;
		for(int i=0;i<5;i++)
			instrucao[i] = 0;
		instrucao[1] = 1;

		return true;
	}

	if(campo == "and"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
			instrucao[i] = 0;
			
		//shamt 00000
		for(int i=6;i < 11; i++)
			instrucao[i] = 0;

		//funct 100100
		instrucao[5] = 1;
		for(int i=0;i<5;i++)
			instrucao[i] = 0;
		instrucao[2] = 1;

		return true;
	}

	if(campo == "or"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
			instrucao[i] = 0;

		//shamt 00000
		for(int i=6;i < 11; i++)
			instrucao[i] = 0;

		//funct 100100
		instrucao[5] = 1;
		instrucao[4] = 0;
		instrucao[3] = 0;
		instrucao[2] = 1;
		instrucao[1] = 0;
		instrucao[0] = 1;

		return true;
	}

	if(campo == "slt"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
		instrucao[i] = 0;

		//rs

		//rt

		//rd

		//shamt 00000
		for(int i=6;i < 11; i++)
		instrucao[i] = 0;

		//funct 101010
		instrucao[5] = 1;
		instrucao[4] = 0;
		instrucao[3] = 1;
		instrucao[2] = 0;
		instrucao[1] = 1;
		instrucao[0] = 0;

		return true;
	}

	if(campo == "sll"){ //Tipo R
		//op 000000
		for(int i=26;i < 32; i++)
			instrucao[i] = 0;

		//rs 00000
		for(int i=20;i < 26;i++)
			instrucao[i] = 0;

		//funct 000000
		for(int i=0;i < 6; i++)
			instrucao[i] = 0;

		return true;
	}

	if(campo == "addi"){ //Tipo I
		//op 001000
		instrucao[31] = 0;
		instrucao[30] = 0;
		instrucao[29] = 1;
		instrucao[28] = 0;
		instrucao[27] = 0;
		instrucao[26] = 0;

		return true;
	}

	if(campo == "lw"){ //Tipo I
		//op 100011
		instrucao[31] = 1;
		instrucao[30] = 0;
		instrucao[29] = 0;
		instrucao[28] = 0;
		instrucao[27] = 1;
		instrucao[26] = 1;

		//rs

		//rt

		//address
		return true;
	}

	if(campo == "sw"){ //Tipo I
		//op 101011
		instrucao[31] = 1;
		instrucao[30] = 0;
		instrucao[29] = 1;
		instrucao[28] = 0;
		instrucao[27] = 1;
		instrucao[26] = 1;

		//rs

		//rt

		//address
		return true;
	}
	
	if(campo == "beq"){ //Tipo I
		//op 000100
		instrucao[31] = 0;
		instrucao[30] = 0;
		instrucao[29] = 0;
		instrucao[28] = 1;
		instrucao[27] = 0;
		instrucao[26] = 0;

		//rs

		//rt

		//constant
		return true;
	}

	if(campo == "bne"){ //Tipo I
		//op 000101
		instrucao[31] = 0;
		instrucao[30] = 0;
		instrucao[29] = 0;
		instrucao[28] = 1;
		instrucao[27] = 0;
		instrucao[26] = 1;

		//rs

		//rt

		//constant
		return true;
	}

	if(campo == "j"){ //Tipo J
		//op 000010
		instrucao[31] = 0;
		instrucao[30] = 0;
		instrucao[29] = 0;
		instrucao[28] = 0;
		instrucao[27] = 1;
		instrucao[26] = 0;

		return true;
	}

	if(campo == "jr"){ //Tipo R
		//op 000000
		for(int i=26; i<32;i++)
			instrucao[i] = 0;

		//rs

		//rt 000000
		for(int i=16; i<21;i++)
			instrucao[i] = 0;

		//rd 000000
		for(int i=11; i<16;i++)
			instrucao[i] = 0;

		//shamt 000000
		for(int i=6; i<11;i++)
			instrucao[i] = 0;

		//funct 001000
		instrucao[5] = 0;
		instrucao[5] = 0;
		instrucao[3] = 1;
		instrucao[2] = 0;
		instrucao[1] = 0;
		instrucao[0] = 0;

		return true;
	}

	if(campo == "jal"){ //Tipo J
		//op 000011
		instrucao[31] = 0;
		instrucao[30] = 0;
		instrucao[29] = 0;
		instrucao[28] = 0;
		instrucao[27] = 1;
		instrucao[26] = 1;

		return true;
	}

	return false;
}

/**
 * Identifica o registrador recebido como parametro e armazena o valor apropriado a instrucao em binario
 * @param campo
 * @param instrucao
 * @param posini
 * @param posfinal
 *
 * @author Mara de Lemos Gomes
 */
void coverteRegistrador(string campo,int *instrucao,int posini,int posfinal){

	
	if(campo == "$zero"){ //0
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	} 
	if(campo == "$at"){ //1
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$v0"){ //2
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$v1"){ //3
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$a0"){ //4
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$a1"){ //5
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$a2"){ //6
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$a3"){ //7
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t0"){ //8
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	} 
	if(campo == "$t1"){ //9
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t2"){ //10
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t3"){ //11
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t4"){ //12
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t5"){ //13
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo  == "$t6"){ //14
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$t7"){ //15
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 0;
	}
	if(campo == "$s0"){ //16
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s1"){ //17
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s2"){ //18
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s3"){ //19
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s4"){ //20
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s5"){ //21
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s6"){ //22
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$s7"){ //23
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 0;
		instrucao[posfinal] = 1;
	}
	if(campo == "$t8"){ //24
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$t9"){ //25
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$k0"){ //26
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$k1"){ //27
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 0;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$gp"){ //28
		instrucao[posini] = 0;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$sp"){ //29
		instrucao[posini] = 1;
		instrucao[posini+1] = 0;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$fp"){ //30
		instrucao[posini] = 0;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	if(campo == "$ra"){ //31
		instrucao[posini] = 1;
		instrucao[posini+1] = 1;
		instrucao[posini+2] = 1;
		instrucao[posini+3] = 1;
		instrucao[posfinal] = 1;
	}
	
}

/**
 * Converte um inteiro para binario e armazena o resultado em um vetor
 * @param num
 * @return vet
 *
 * @author Mara de Lemos Gomes
 */
int* decimalparaBin(int num, int tam){
	int* vet = new int[tam];

	for(int j=0;j < tam;j++)
		vet[j] = 0;

	int i = (tam-1);
	while(num != 0){
		vet[i] = (num % 2);
		num = (num/2);
		i--;
	}
	return vet;
}

/**
 * Converte uma instrução para binario
 * @param linha
 *
 * @author Mara de Lemos Gomes
 */
void converteInstrucao(string linha){

	int *instrucao = new int[32];

	char *buffer = new char[20];
    char *campo;

	strcpy(buffer, linha.c_str());
    campo = strtok(buffer, " ");

    string a = campo;

    if(identificaInstrucao(campo, instrucao)){

    	if(a == "add" || a == "sub" || a == "and"  || a == "or" || a == "slt"){
	    	campo = strtok(NULL, ",");
	    	//rd
	    	coverteRegistrador(campo,instrucao,11,15);
	    	campo = strtok(NULL, ",");
	    	//rs
	    	coverteRegistrador(campo,instrucao,21,25);
	    	campo = strtok(NULL, " #");
	    	//rt
	    	coverteRegistrador(campo,instrucao,16,20);
	    }
	    if(a == "sll"){
	    	//rd
	    	campo = strtok(NULL, ",");
	    	coverteRegistrador(campo,instrucao,11,15);

	    	//rt
	    	campo = strtok(NULL, ",");
	    	coverteRegistrador(campo,instrucao,16,20);

	    	//shamt
	    	campo = strtok(NULL, " #");
	    	int *shamt,j = 0;
	    	shamt = decimalparaBin(atoi(campo),5);
	    	for(int i=10; i>=6;i--){
	    		instrucao[i] = shamt[j];
	    		j++;
	    	}
	    }
	    if(a == "addi"){
	    	//rs
	    	campo = strtok(NULL, ",");
	    	coverteRegistrador(campo,instrucao,21,25);
	    	//rt
	    	campo = strtok(NULL, ",");
	    	coverteRegistrador(campo,instrucao,16,20);
	    	//constant
	    	campo = strtok(NULL, " #");
	    	int *constant, j = 0;
	    	constant = decimalparaBin(atoi(campo),16);
	    	for(int i=15; i>=0;i--){
	    		instrucao[i] = constant[j];
	    		j++;
	    	}
	    }

    }else{
    	cout << "Erro! Instrução inválida";
    }

    //Teste
    for(int i=31;i>=0;i--)
    	cout << instrucao[i];
}

/**
 * Solicita ao usuario o nome de um arquivo de texto e faz a leitura do mesmo
 *
 * @author Mara de Lemos Gomes
 */
void leArquivo(){

    string nome,linha;
    cout << "Informe o nome do arquivo:" << endl;
    cin >> nome;
    ifstream arquivo;
    arquivo.open(nome,ios::in);
    if(!arquivo.is_open())
        cout << "Erro ao abrir arquivo "+nome+". Certifique-se de que o mesmo se encontra no diretório do executável";
    else{
        cout << "Lendo, convertendo e armazenando instruções" << endl;

        while(arquivo >> linha){

        	converteInstrucao(linha);

        }
    }
}
/**
 * Interface com o usuário
 *
 * @author Mara de Lemos Gomes
 */
void menu(){
	char alternativa;

    printf("\e[H\e[2J"); //Limpa a tela do terminal
    cout << "\tSimulador Pipeline MIPS" << endl;
    cout << "___________________________________________________"<<endl;
    cout << "Entrada:" << endl;
    cout << "\n(a) Carga do arquivo\n(b) Entrada via teclado" << endl;
    cout << "___________________________________________________"<<endl;
    cout << "Execução:" << endl;
    cout << "\n(c) Passo-a-Passo\n(d) Direta" << endl;
    cout << "___________________________________________________"<<endl;
    cout << "\n(e) Reset" << endl;
    cout << "(s) Sair" << endl;

    cin >> alternativa;
    alternativa = toupper(alternativa); //Converte o caractere para maiusculo

    string instrucao;

    switch (alternativa) {
        case 'A':
            printf("\e[H\e[2J");
            //Verificar se memoria já está ocupada
            leArquivo();

            if(novaOp()){
                menu();
            }else{
                exit(0);
            }
            break;

        case 'B':
            printf("\e[H\e[2J");
            //Verificar se memoria já está ocupada
            char qtdInstrucoes;
            cout << "Informe a quantidade de instruções:" << endl;
            cin >> qtdInstrucoes;
            if(!(isdigit(qtdInstrucoes) != 0)){
                cout << "Caractere inválido." << endl;
            }else{
                cout << "Digite cada instrução em uma linha" << endl;
                for(int i=0;i<(qtdInstrucoes - '0');i++){
                    cin.ignore();
                    getline(cin, instrucao);
                    converteInstrucao(instrucao);
                }
            }
            if(novaOp()){
                menu();
            }else{
                exit(0);
            }
            break;

        case 'C':
            printf("\e[H\e[2J");
            //Verificar se memoria já está ocupada
            if(true){ //Se memoria estiver vazia
                cout << "Entre com as instruções através de (a) ou (b) no menu inicial." << endl;
            }else{

            }
            if(novaOp()){
                menu();
            }else{
                exit(0);
            }
            break;

        case 'D':
            printf("\e[H\e[2J");
            //Verificar se memoria já está ocupada
            if(true){ //Se memoria estiver vazia
                cout << "Entre com as instruções através de (a) ou (b) no menu inicial." << endl;
            }
            if(novaOp()){
                menu();
            }else{
                exit(0);
            }
            break;

        case 'E':
            printf("\e[H\e[2J");
            cout<<"Reset realizado com sucesso"<<endl;
            
            if(novaOp()){
                menu();
            }else{
                exit(0);
            }
            break;

        case 'S':
            exit(0);
            break;
        default:
            printf("\e[H\e[2J");
            cout << "Caractere inválido\nEscolha uma das opções\n\n";
            menu();
            break;
    }
}

int main(int argc, char const *argv[])
{

    setlocale(LC_ALL, NULL); //Correção de acentuação

    menu();
    return 0;
}