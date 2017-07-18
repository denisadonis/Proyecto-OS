#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue> 
#include <cstdlib>
#include <cctype>

#include "Proceso.h"

using namespace std;

/* queue cola sin prioridad metodos basicos 
 * .front() devuelve el valor del primer elemento
 * .pop() saca el primer elemento de la cola no devuelve nada
 * .push() inserta elementos en la cola
 * .size() devuelve el tamaño de la cola
 *
 * priority_queue cola con prioridad:
 * de los metodos de queue front() es el unico metodo que nos es valido
 * se sustituye por top().
 * .emplace() esta funcion intancia un elemento y lo inseta en la cola sin la 
 * necesidad de crear un objeto temporal
 */

string abrirArchivo(void); // abre un archivo y devuelve un string con todos los elementos concatenados
queue<string> split(string, const char); // Funcion para separar cadenas devuelve una cola sin prioridad
void moverDeNuevosListos(queue<string> &, priority_queue<Proceso> &);

int main()
{
	queue<string> nuevos = split(abrirArchivo(), ';'); 
	priority_queue<Proceso> listos;
	string temp = "ho1a mundo";

	moverDeNuevosListos(nuevos, listos);
	
	while (!listos.empty()) {
		cout << "id: " << ((Proceso)listos.top()).get_id() << ", p: "<< ((Proceso)listos.top()).get_priority() << endl; //Cuidado con la forma de sacar objetos de la cola
		listos.pop();
	}

	return 0;
}

string abrirArchivo(void)
{
	string line;
	string data = "";
	ifstream infile;

	try	{
		infile.open("file/procesos.txt", ios::in);

		while (getline(infile, line))
		{
			data += line + "\n";
		}
	} catch (exception & e) {
		cout << "error al intentar abrir el archivo" << endl;
	}

	infile.close();

	return data;
}

queue<string> split(string str, const char delimiter)
{
	istringstream isstream(str);
    queue<string> cola;
    string word;

    while(std::getline(isstream, word, delimiter)) {
    	if (word != "\n")
    	{
			cola.push(word);	        
    	}
    }

	return cola;
}
/* resive la referencia de una cola de string y devuelve una cola de prioridad con 
todos los procesos que cumplen los requisitos para poder ejecutarse*/
void moverDeNuevosListos(queue<string> & nuevos, priority_queue<Proceso> & listos)
{
	bool validarProceso(queue<string> cola);
	queue<string> temp; // cola donde se almacenaran las cadenas resultantes depues de dividir los proceso
	int count = nuevos.size(); // tamaño de la cola para poder ser usada en el ciclo 
	int code[6]; // donde se guardaran temporalmento los datos de un proceso para despues poder ser insertados en la cola

	for (int i = 0; i < count; ++i)
	{
		temp = split(nuevos.front(), '/');
		if (validarProceso(temp))
		{
			for (int i = 0; i < 6; ++i)
			{
				// atoi convierte cadenas a enteros
				code[i] = atoi(temp.front().c_str()); // .c_str() solo de esta forma se puede usar atoi en string
				temp.pop();
			}
			listos.emplace(code[0], code[1], code[2], code[3], code[4], code[5]);
		} else {
			nuevos.push(nuevos.front()); /* esto permitira que aquellos elementos que no cuplan con los requisitos
			vuelvan a la cola con el objetivo de que al final los presentemos en pantalla como elementos
			que no pasaron la prueba */ 
		}
		nuevos.pop();
	}
}

// esta funcion en con el objetivo de intentar validar los proceso, seria mejor tratar de validarlos antes de
// convertirlos a enteros ya que si hay leras o espacios podrian ocacionar error
bool validarProceso(queue<string> cola) 
{
	bool estado = true;

	// Primer nivel de validacion 
	if (cola.size() != 6)
	{
		estado = false;
	}

	// Segundo nivel de validacion
	for (int i = 0; i < cola.size() and estado; ++i)
	{
		for (int x = 0; x < cola.front().size(); ++x)
		{
			if (!isdigit(cola.front()[x])) {
				estado = false;
			}
		}
		cola.push(cola.front());
		cola.pop();
	}

	 for (int i = 0; !cola.empty() and estado; ++i) {
	 	switch (i) {
	 	case 0:
	 		if (cola.front().size() != 4)
	 			estado = false;
	 		break;
	 	case 1:
	 	case 2:
	 		if (cola.front().size() != 1)
	 			estado = false;
	 		break;
	 	case 3:
	 	case 4:
	 		if (cola.front().size() != 3)
	 			estado = false;
	 		break;
	 	case 5:
	 		if (atoi(cola.front().c_str()) >= 1 & atoi(cola.front().c_str()) <= 3)
	 			estado = false;
	 		break;
	 	default:
	 		cout << "hay algun error" << endl;
	 	}

	 	cola.pop();
	 }

	return estado;
}