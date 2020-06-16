#ifndef EXECUTE_H /*Se a biblioteca soma.h n�o for definida, fa�a-o. Esta verifica��o � feita para para n�o ter varia chamada da mesma biblioteca no mesmo programa. S� uma chamada nos satisfaz*/
#define EXECUTE_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "fetch.h"
#include "registers.h"

using namespace std;

//Defini��o das intru��es
#define ADD 0
#define SUB 1
#define AND 2
#define OR  3

//---------------------Declara��o dos cabe�alhos---------------------
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

			// Realizando a Opera��o
			s[body.rd].value = s[body.rs].value + s[body.rt].value;

			printAfter(s);

			break;

		case SUB:

			printBefore("SUB", s);

			// Realizando a Opera��o
			s[body.rd].value = s[body.rs].value - s[body.rt].value;

			printAfter(s);

			break;

		case AND:

			printBefore("AND", s);

			// Realizando a Opera��o
			s[body.rd].value = s[body.rs].value && s[body.rt].value;

			printAfter(s);

			break;

		case OR:

			printBefore("OR ", s);

			// Realizando a Opera��o
			s[body.rd].value = s[body.rs].value || s[body.rt].value;

			printAfter(s);

			break;
		}
}

//-------------------------Escopo das fun��es------------------------
void printBefore (string comand, reg s[6])
{
	cout << "   |-----Instru��o-----|" << endl;
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
