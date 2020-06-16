#ifndef CACHE_H
#define CACHE_H

using namespace std;

#define SIZE_CACHE 3

typedef struct cacheBody
{
	bool valid; // Variavel para verificar se local esta vago
	int value; 	// Variavel para armazenar instru��o em decimal

	//Construtor para iniciar as variaveis
	cacheBody()
	{
		valid = false;
		value = NULL;
	}

} memCache;

//Declarando o vetor para representar memoria cache
memCache storage[SIZE_CACHE];

//---------------------Declara��o dos cabe�alhos---------------------
int searchCache(int instruction[4], int PC);
void showCache();
void addCache(int instruction[4], int PC);
//-------------------------------------------------------------------

int cache (int instruction[4], int PC)
{

	// -------------Buscando na Mem�ria Cache------------
	return searchCache(instruction, PC);
	// --------------------------------------------------

}

//-------------------------Escopo das fun��es------------------------
int searchCache(int instruction[4], int PC)
{
	cout << "      Instru��o n� " << PC << endl;
	cout << "   |--Busca no Cache---|" << endl;
	
	for(int i = 0; i < SIZE_CACHE; i++)
	{
		if(storage[i].value == instruction[PC])
		{
			cout << "   |--------HIT--------|" << endl;
			cout << "      Local[" << i << "] = " << storage[i].value << endl << endl;
			return storage[i].value;
		}
	}
	cout << "   |-------MISS--------|" << endl;
	cout << "      N�o encontrado " << endl << endl;
	
	addCache(instruction, PC);

	return 0;
}


void addCache(int instruction[4], int PC)
{
	for(int i = 0; i < SIZE_CACHE; i++)
	{
		if(storage[i].valid == false)
		{
			storage[i].value = instruction[PC];
			storage[i].valid = true;
			break;
		}
	}
}

void showCache()
{
	for(int i = 0; i < SIZE_CACHE; i++)
	{
		cout << "      Local[" << i << "] = " << storage[i].value << endl;
	}
}

#endif
