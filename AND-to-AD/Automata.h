#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include "Estado.h"
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Automata
{
	vector<string> alfabeto;
	vector<Estado> estados;
	string nombre;

public:

	Automata(string);
	void colocar_valor_alfabeto(string);
	void colocar_estado(Estado);
	void colocar_nombre(string);
	string buscar_valor_alfabeto(int);
	string mostrar_funciones();
	void convertir_a_AFD();
	vector<string> encontrar_outputs_multiples(vector<vector<string>>);
	Estado encontrar_estado(string);
	Estado unir_estados(vector<Estado>, string, int);
	void reemplazar_outputs_por_nuevo_estado(vector<string>, Estado);
	void remover_estados_no_accesibles();
	void renombrar();

};

