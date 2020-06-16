/*
Autores: Brendhon Eduardo Cardoso Moreira, Matricula: 1372 - L1
   	 	 Gabriel de Souza Daniel,		   Matricula: 1346 - L2

Arquitetura de 16 bits

Códigos das instruções:

	 Instruções Aritméticas
		ADD  - Tipo R (Soma dois registros)
		SUB  - Tipo R (Subtrai dois registros)

	 Instruções Lógicas
		AND	- Tipo R (Lógica 'e')
		OR 	- Tipo R (Lógica 'ou')

Modelo das instruções Tipo R:

	opcode		1° Reg de origem 	2° Reg de origem	Reg de Destino	funct
	2 bits          4 bits            	4 bits				4 bits		2 bits

Funct:

	00 -> ADD
	01 -> SUB
	10 -> AND
	11 -> OR

PC:

	00 -> Primeira linha do codigo
	01 -> Segunda linha do codigo
	10 -> Terceira linha do codigo
	11 -> Quarta linha do codigo

Exemplo:

ADD $s2, $s0, $s1

  	  00			0000				0001				0010		 00
 	OP = 0			$s0			  		$s1					$s2		 funct = ADD
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "fetch.h"
#include "execute.h"
#include "registers.h"

using namespace std;

#define SIZE_INSTRUCTION 4

/* Casos Testes
 Tipo R            -> OP  RS   RT   RD  Funct     Decimal
 ADD $s2, $s0, $s1 -> 00 0000 0001 0010 00     -> 72
 SUB $s5, $s3, $s4 -> 01 0011 0100 0101 01     -> 19733
 AND $s3, $s5, $s4 -> 10 0101 0100 0011 10 	   -> 38158
 OR  $s5, $s3, $s4 -> 11 0011 0100 0101 11 	   -> 52503
 */

void showReg(reg s[6]);

int main()
{
	setlocale(LC_ALL, "Portuguese"); //Biblioteca para expressões em português

	//Instruções   						 ADD  SUB	 AND	OR
	int instruction[SIZE_INSTRUCTION] = {72, 19733, 38158, 72};

	//Variavel - PC
	int PC = 0;

	//Inicializando os Registradores
	reg s[6];
	s[0].name = "$s0";
	s[0].value = 1;

	s[1].name = "$s1";
	s[1].value = 1;

	s[2].name = "$s2";
	s[2].value = 1;

	s[3].name = "$s3";
	s[3].value = 1;

	s[4].name = "$s4";
	s[4].value = 1;

	s[5].name = "$s5";
	s[5].value = 1;

	cout << "Valores dos registradores na Entrada" << endl;
	showReg(s);

	for(int i = 0; i < SIZE_INSTRUCTION; i++)
	{

		//Ciclo de Busca
		fetch(instruction, PC);

		//Ciclo de Execução
		execute(s);

	}

	cout << "Valores dos registradores na saida" << endl;
	showReg(s);


	return 0;
}

void showReg(reg s[6])
{
	for(int i = 0; i < 6; i++)
	{
		cout << s[i].name << " -> ";
		cout << s[i].value << endl;
	}

	cout << endl;
}
