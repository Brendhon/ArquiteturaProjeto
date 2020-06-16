#ifndef EXECUTE_H /*Se a biblioteca soma.h não for definida, faça-o. Esta verificação é feita para para não ter varia chamada da mesma biblioteca no mesmo programa. Só uma chamada nos satisfaz*/
#define EXECUTE_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "fetch.h"
#include "registers.h"

using namespace std;

//Definição das intruções
#define ADD 0
#define SUB 1
#define AND 2
#define OR  3

//---------------------Declaração dos cabeçalhos---------------------
void printBefore (string comand, reg s[6]);
void printAfter(reg s[6]);
void showErro();
//-------------------------------------------------------------------

void execute (reg s[6])
{
	if(body.fault)
		showErro();
	else
		switch(body.funct)
		{
		case ADD:

			printBefore("ADD", s);

			// Realizando a Operação
			s[body.rd].value = s[body.rs].value + s[body.rt].value;

			printAfter(s);

			break;

		case SUB:

			printBefore("SUB", s);

			// Realizando a Operação
			s[body.rd].value = s[body.rs].value - s[body.rt].value;

			printAfter(s);

			break;

		case AND:

			printBefore("AND", s);

			// Realizando a Operação
			s[body.rd].value = s[body.rs].value && s[body.rt].value;

			printAfter(s);

			break;

		case OR:

			printBefore("OR ", s);

			// Realizando a Operação
			s[body.rd].value = s[body.rs].value || s[body.rt].value;

			printAfter(s);

			break;
		}
}

//-------------------------Escopo das funções------------------------
void printBefore (string comand, reg s[6])
{
	cout << "   |-----Instrução-----|" << endl;
	cout << "   |Opcode = " << body.op << "         |" << endl;
	cout << "   |" << comand << " ";
	cout << s[body.rd].name << ", ";
	cout << s[body.rs].name << ", ";
	cout << s[body.rt].name << "  |" << endl;
	cout << "   |-------Antes-------|" << endl;
	cout << "   |RS -> " << s[body.rs].value << " -> " << s[body.rs].name << "     |" << endl;
	cout << "   |RT -> " << s[body.rt].value << " -> " << s[body.rt].name << "     |" << endl;
	cout << "   |RD -> " << s[body.rd].value << " -> " << s[body.rd].name << "     |" << endl;
}

void printAfter(reg s[6])
{
	cout << "   |------Depois-------|" << endl;
	cout << "   |RD -> " << s[body.rd].value  << " -> " << s[body.rd].name << "     |" << endl;
	cout << "    -------------------" << endl << endl << endl << endl;
}

void showErro()
{
	cout << "         ---------" << endl;
	cout << "          ERRO!!" << endl;
	cout << "         ---------" << endl;
}

#endif
