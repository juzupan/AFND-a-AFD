#include "Automata.h"




Automata::Automata(string nom)
{
	nombre = nom;
}

void Automata::colocar_valor_alfabeto(string valor) {
	alfabeto.push_back(valor);
}

void Automata::colocar_estado(Estado e) {
	estados.push_back(e);
}

string Automata::mostrar_alfabeto() {

	int tamano = alfabeto.size();
	string cadena("");

	for (int i = 0; i < tamano; i++) {
		string temp(alfabeto.at(i));
		cadena = cadena + temp;
	}
	return cadena;
}

string Automata::buscar_valor_alfabeto(int i) {

	return alfabeto.at(i);
}

string Automata::mostrar_funciones() {

	int num_estados = estados.size();
	string cadena("Tabla del automata "+ nombre + "\n\n");

	for (int n = 0; n < num_estados; n++) { // Nivel de estados

		Estado e = estados.at(n);
		int num_funciones = e.get_num_funciones();

		for (int i = 0; i < num_funciones; i++) { // Nivel de funciones

			Funcion f = e.get_funcion(i);
			vector<string> outputs = f.get_outputs();
			int num_outputs = outputs.size();
			string output = "";

			for (int j = 0; j < num_outputs; j++) { // Nivel de outputs

				output = output + " " + outputs.at(j);
			}
			cadena = cadena + "f(" + e.get_nombre() + "," + f.get_input() + "): " + output + "\n";
		}
		cadena = cadena + "\n";
	}
	return cadena;
}

void Automata::colocar_nombre(string nom) {
	nombre = nom;
}

void Automata::convertir_a_AFD() {

	vector<string> outputs_multiples = encontrar_outputs_multiples();
	int iteracion = 0;

	while (outputs_multiples.size()!=0) { // Busca outputs multiples en el automata para reemplazarlos por estados unicos

		iteracion++;
		if (iteracion == 3) break;

		// Se crea un nombre para un estado unico nuevo

		string ultimo_estado;
		int ultimo_numero = estados.size();
		stringstream ss;
		ss << "S" << ultimo_numero;
		ultimo_estado = ss.str();
		
		// Definir los estados a heredar en base a outputs multiples

		vector<Estado>estados_a_heredar;
		int num_outputs = outputs_multiples.size();

		for (int i = 0; i < num_outputs; i++) {
			estados_a_heredar.push_back(encontrar_estado(outputs_multiples.at(i)));
		}
		Estado nuevo_estado = fusionar_estados(estados_a_heredar,ultimo_estado);

		// Reemplazar outputs multiples por nuevo estado

		reemplazar_outputs_por_nuevo_estado(outputs_multiples,nuevo_estado);

		estados.push_back(nuevo_estado);

		outputs_multiples = encontrar_outputs_multiples();
	}
}

Estado Automata::fusionar_estados(vector<Estado> estados, string nombre) {

	Estado nuevo_estado(nombre);
	
	vector<Funcion> funciones_base = estados.at(0).get_funciones(); // funciones del primer estado
	nuevo_estado.colocar_estado_contenido(estados.at(0).get_nombre());

	int num_estados = estados.size();
	int num_funciones = funciones_base.size();

	for (int i = 1; i < num_estados; i++) { // Nivel de estados

		nuevo_estado.colocar_estado_contenido(estados.at(i).get_nombre());
		vector<Funcion> funciones_agregar = estados.at(i).get_funciones();
		
		for (int y = 0; y < num_funciones; y++) { // Nivel de funciones
			Funcion f = funciones_agregar.at(y);
			funciones_base.at(y).agregar_outputs(f);
		}
	}
	nuevo_estado.colocar_funcion(funciones_base);
	return nuevo_estado;
}



Estado Automata::encontrar_estado(string nombre) {
	
	int num_estados = estados.size();
	for (int i = 0; i < num_estados; i++) {
		if (estados.at(i).get_nombre() == nombre) return estados.at(i);
	}
	Estado vacio("vacio");
	return vacio;
}

vector<string> Automata::encontrar_outputs_multiples() {

	int num_estados = estados.size();

	for (int n = 0; n < num_estados; n++) { // Nivel de estados

		Estado e = estados.at(n);
		int num_funciones = e.get_num_funciones();

		for (int i = 0; i < num_funciones; i++) { // Nivel de funciones

			Funcion f = e.get_funcion(i);
			vector<string> outputs = f.get_outputs();
			int num_outputs = outputs.size();
			if (num_outputs>1) return outputs;
		}
	}
	vector<string> vacio; 
	return vacio;
}

vector<Estado> Automata::encontrar_estados_con_cierto_output_multiple(vector<string> outputs_buscados) {

	vector<Estado> estados_encontrados;
	int num_estados = estados.size();
	

	for (int n = 0; n < num_estados; n++) { // Nivel de estados

		Estado e = estados.at(n);
		int num_funciones = e.get_num_funciones();

		for (int i = 0; i < num_funciones; i++) { // Nivel de funciones

			Funcion f = e.get_funcion(i);
			vector<string> outputs = f.get_outputs();
			if (Ayuda::comparar_outputs(outputs, outputs_buscados)) estados_encontrados.push_back(e);
		}
	}
	return estados_encontrados; 
}

void Automata::reemplazar_outputs_por_nuevo_estado(vector<string> outputs_buscados, Estado nuevo_estado) {

	vector<string> nuevo_output;
	nuevo_output.push_back(nuevo_estado.get_nombre());

	int num_estados = estados.size();

	for (int n = 0; n < num_estados; n++) { // Nivel de estados

		estados.at(n).reemplazar_outputs(outputs_buscados, nuevo_output);
	}
}


