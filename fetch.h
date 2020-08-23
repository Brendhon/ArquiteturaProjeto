#ifndef FETCH_H /*Se a biblioteca soma.h n�o for definida, fa�a-o. Esta verifica��o � feita para para n�o ter varia chamada da mesma biblioteca no mesmo programa. S� uma chamada nos satisfaz*/
#define FETCH_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "cache.h"

using namespace std;

struct instructionBody
{
	int op; 	//OPCODE
	int rs; 	//1� Reg de origem
	int rt; 	//2� Reg de origem
	int rd; 	//Reg de destino
	int funct;	//Tipo de fun��o

	bool fault; //Variavel para verificar erro

} body;


//---------------------Declara��o dos cabe�alhos--------------------
int search (int instruction[4], int&);
void decoder (int currentInstruction);
int interpreter(int limit1, int limit2, int instruction[16]);
void updatePC (int&);
void validation ();
//-------------------------------------------------------------------


//------------------------Fun��o Principal---------------------------
void fetch (int instruction[4], int &PC)
{

	//----------------1� Passo: Busca pela instru��o-----------------
	int currentInstruction; //Instru��o Atual
	currentInstruction = search(instruction, PC);
	//---------------------------------------------------------------


	//-------------------2� Passo: Decodifica��o---------------------
	decoder(currentInstruction);
	//---------------------------------------------------------------


	//------------------3� Passo: Atualiza��o do PC------------------
	updatePC(PC);
	//---------------------------------------------------------------
}


//-------------------------Escopo das fun��es------------------------
int search (int instruction[4], int &PC)
{
	// Realiza a busca no cache
	int containCache = cache(instruction, PC);

	// Se existe na mem�ria do cache retorna a instru��o contida
	if(containCache != 0)
		return containCache;
	else
		return instruction[PC];

}

void decoder (int currentInstruction)
{
	int result; //Resultado do deslocamento
	int cont; //Contador
	int decode[16]; //Vetor que ir� armazenar o valor em Binario


	//Utiliza um n�mero de 16 bits como base para a convers�o.
	for(cont = 15; cont >= 0; cont--)
	{
		//Executa a opera��o shift right at� a �ltima posi��o da direita para cada bit.
		result = currentInstruction >> cont;

		//Por meio do "e" l�gico ele compara se o valor na posi��o mais � direita � 1 ou 0
		if(result & 1)
			decode[cont] = 1;
		else
			decode[cont] = 0;
	}

	//Interpretando a instru��o
	body.op 	= interpreter(14, 15, decode);
	body.rs 	= interpreter(10, 13, decode);
	body.rt 	= interpreter(6, 9, decode);
	body.rd 	= interpreter(2, 5, decode);
	body.funct 	= interpreter(0, 1, decode);

	validation();

}

int interpreter (int limit1, int limit2, int instruction[16])
{
	int i; //Auxiliar
	int size = limit2 - limit1 + 1; //Tamanho da parte da instru��o
	int vector[size]; //Vetor para armazenar a parte da instru��o
	int j = size - 1; //Segunda variavel auxiliar
	int decimal = 0; //Variavel para armazenar o valor decimal de cada parte

	//"for" para recortar as partes do vetor
	for(i = limit2; i >= limit1; i--)
	{
		vector[j] = instruction[i];
		j--;
	}

	//Transformar as partes em decimais para criar facilita��es
	for(i = size - 1 ; i >= 0; i--)
	{
		decimal = decimal + vector[i] * pow(2, i);
	}

	return decimal;

}

void validation ()
{
	if((body.op > 3) 		||
			(body.funct > 3)||
			(body.rs > 5) 	||
			(body.rt > 5) 	||
			(body.rd > 5))
		body.fault = true;
	else
		body.fault = false;
}

void updatePC (int &PC)
{
	PC = PC + 1;
}
//--------------------------------------------------------------


#endif
