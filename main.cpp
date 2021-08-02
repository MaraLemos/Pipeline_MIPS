#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //Necessario para uso da funcao toupper
#include <locale.h> //Necessario para uso da funcao setlocale
#include <string.h>
#include <cmath>
#include <fstream>
#include "Mips.h"

using namespace std;

/**
 * Converte binario para decimal
 * @param vet
 * @return decimal
 *
 * @author Mara de Lemos Gomes
 */
size_t binarioParaDec(int *vet){
    size_t decimal = 0; 

    for(int i=0; i < 32; i++){
        decimal += vet[i]*pow(2,i);
    }

    return decimal;
}

/**
 * Converte instrucao para representação inteira
 * @param linha
 * @param instrucaoCodificada
 * @return boolean
 *
 * @author Mara de Lemos Gomes
 */
bool codificaInstrucao(string linha, long int *instrucaoCodificada){

	int instrucao[32];
	int j = 31;

	char buffer[32];

	strcpy(buffer, linha.c_str());
    
    //Certifica-se que não há caracteres inválidos
    for(int i=0; buffer[i] != '\0'; i++){
    	if(buffer[i] == '1' || buffer[i] == '0'){
    		instrucao[j] = buffer[i] - '0';
    		j--;
    	}
    }

    if(j == -1){
    	(*instrucaoCodificada) = binarioParaDec(instrucao);
    	return true;
    }

    return false;
}

/**
 * Solicita ao usuario o nome de um arquivo de texto e faz a leitura do mesmo
 * @param mips
 *
 * @author Mara de Lemos Gomes
 */
void leArquivo(Mips *mips){

    string nome, linha;
    cout << "Informe o caminho e nome do arquivo:" << endl;
    cin.ignore();
    getline(cin, nome);
    ifstream arquivo;
    arquivo.open(nome, ios::in);
    if(!arquivo.is_open())
        cout << "Erro ao abrir "+nome;
    else{
        cout << "Lendo, convertendo e armazenando instruções" << endl;
		long int instrucaoCodificada;

        while(arquivo >> linha){

        	if(codificaInstrucao(linha,&instrucaoCodificada)){
        		mips->armazenaInstrucao(instrucaoCodificada);
        	}
        }
    }
}

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
        if (alternativa == '1')
            return true;
    }
    return false;
}

/**
 * Interface com o usuário
 * @param mips
 *
 * @author Mara de Lemos Gomes
 */
void menu(Mips *mips){
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

    string linha;

    switch (alternativa) {
        case 'A':
            printf("\e[H\e[2J");

            if(mips->getQtdInstrucoes() == 128)
            	cout << "Memória de instruções cheia!" << endl;
            else
            	leArquivo(mips);

            if(novaOp())
                menu(mips);
            break;

        case 'B':
            printf("\e[H\e[2J");

            if(mips->getQtdInstrucoes() == 128){

            	cout << "Memória de instruções cheia!" << endl;

            }else{
            	cout << "Digite uma instrução" << endl;
	            cin.ignore();
	            getline(cin, linha);

	            long int instrucaoCodificada;

	            cout << "Lendo, convertendo e armazenando instrução" << endl;

	            if(codificaInstrucao(linha,&instrucaoCodificada))
	        		mips->armazenaInstrucao(instrucaoCodificada);
	        	
            }
            
            if(novaOp())
                menu(mips);
            break;

        case 'C':
            printf("\e[H\e[2J");
            if(mips->getQtdInstrucoes() == 0){ //Se memoria estiver vazia
                cout << "Entre com as instruções através de (a) ou (b) no menu inicial." << endl;
            }else{
            	
            }
            if(novaOp())
                menu(mips);
            break;

        case 'D':
            printf("\e[H\e[2J");
            if(mips->getQtdInstrucoes() == 0){ //Se memoria estiver vazia
                cout << "Entre com as instruções através de (a) ou (b) no menu inicial." << endl;
            }else{
            	for(int i=0; i < mips->getQtdInstrucoes(); i++){
            		mips->estagio1();
            		mips->estagio2();
            	}
            }
            if(novaOp())
                menu(mips);
            break;

        case 'E':
            printf("\e[H\e[2J");
            mips->reset();
            cout<<"Reset realizado com sucesso"<<endl;
            
            if(novaOp())
                menu(mips);
            break;

        case 'S':
            break;

        default:
            printf("\e[H\e[2J");
            cout << "Caractere inválido\nEscolha uma das opções\n\n";
            menu(mips);
            break;
    }
}

int main(int argc, char const *argv[])
{

    setlocale(LC_ALL, NULL); //Correção de acentuação

    Mips *mips = new Mips();
    menu(mips);
    return 0;
}