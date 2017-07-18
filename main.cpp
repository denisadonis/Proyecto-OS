#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue> 
#include <cstdlib>

#include "Proceso.h"

using namespace std;

/* • queue<>, Cola (First in, First out) sin prioridad metodos basicos 
 * .front() retorna el valor del primer elemento
 * .pop() saca el primer elemento de la cola, no devuelve nada
 * .push() inserta elementos en la cola
 * .size() retorna el tamaño de la cola
 * .back() accede al ultimo elemento en la cola
 * .empty() revisa si la cola esta vacia
 *
 * • priority_queue<> cola con prioridad:
 * de los metodos de queue<>, .front() es el unico metodo que nos es valido
 * y se sustituye por .top() que accede al elemento encima de la cola
 * .emplace() esta funcion instancia un elemento y lo inseta en la cola sin la 
 * necesidad de crear un objeto temporal
 */

// Prototipos
string abrirArchivo(void); // Abre un archivo y devuelve un string con todos los elementos concatenados
queue<string> split(string, const char); // Funcion para separar cadenas, devuelve una cola sin prioridad
void moverDeNuevosListos(queue<string> &, priority_queue<Proceso> &); //

int main()
{
	queue<string> nuevos = split(abrirArchivo(), ';');
	priority_queue<Proceso> listos;

	moverDeNuevosListos(nuevos, listos);
	
	//cout << "tamaño: " << listos.size() << endl;

	cout << "--------------------" << endl;

	while (!listos.empty()) { // Funciona mientras listos no este vacio
		cout << "ID del proceso: " << ((Proceso)listos.top()).get_id() << endl;
		cout << "Prioridad: " << ((Proceso)listos.top()).get_priority() << endl; //Cuidado con la forma de sacar objetos de la cola

		//cout << "primeros en la lista: " << listos.top() << endl;

		listos.pop();
	}

	return 0;
}

// Funcion encargada de abrir un archivo y guardar las lineas en una variable
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
			//cout << data << endl;
		}
	} catch (exception & e) {
		cout << "Error al intentar abrir el archivo" << endl;
	}

	infile.close();
	//cout << "Data: " << data << endl;
	return data; // Todo la informacion del archivo se mantiene aqui
}

// Funcion encargada de dividir las cadenas (string data, char delimitador(;))
queue<string> split(string str, const char delimiter){
	//cout << "prueba" << endl;
	istringstream isstream(str);
  queue<string> cola;
  string word = "";

  while(std::getline(isstream, word, delimiter)) { // (data, palabravacia, "/")
  	if (word != "\n"){
			cola.push(word);	        
  	}
  }

  cout << "Valor Enfrente: " << cola.front() << endl;
	return cola;
}

/* recibe la referencia de una cola de string y devuelve una cola de prioridad con 
todos los procesos que cumplen los requisitos para poder ejecutarse*/
void moverDeNuevosListos(queue<string> &nuevos, priority_queue<Proceso> &listos) //&nuevos llega con xxxx/x/x/xxx/xxx/x(varios procesos), &listos llega vacio
{
	
	bool validarProceso(queue<string> cola); // Prototipo
	
	queue<string> temp; // cola donde se almacenaran las cadenas resultantes depues de dividir los proceso
	int count = nuevos.size(); // tamaño de la cola para poder ser usada en el ciclo 
	int code[6]; // donde se guardaran temporalmento los datos de un proceso para despues poder ser insertados en la cola

	for (int i = 0; i < count; i++)
	{
		temp = split(nuevos.front(), '/'); // contiene las "6" partes de un proceso
		
		if (validarProceso(temp)) // validacion de los procesos.
		{

			for (int i = 0; i < 6; i++)
			{
				// atoi convierte cadenas a enteros
				code[i] = atoi(temp.front().c_str()); // .c_str() solo de esta forma se puede usar atoi en string
				//cout << "parteProceso: " << i << ". "<< code[i] << endl;
				temp.pop();
			}
			listos.emplace(code[0], code[1], code[2], code[3], code[4], code[5]);

		}
		nuevos.pop();
		//cout << "tamaño en Funcion: " << listos.size() << endl;
	}
}

// esta funcion es con el objetivo de intentar validar los proceso, seria mejor tratar de validarlos antes de
// convertirlos a enteros ya que si hay leras o espacios podrian ocacionar error
bool validarProceso(queue<string> cola) {
	int paso[6];
	paso[0] = 4;
	paso[1] = 1;
	paso[2] = 1;
	paso[3] = 3;
	paso[4] = 3;
	paso[5] = 1;

	if(cola.size() != 6){
		cout << "El proceso esta incompleto" << endl;
		return false;
	}

	//cout << "tamaño: " << cola.front().size() << endl;
	for (int i = 0; i < 6; i++){
		if(cola.front().size() == paso[i]){
			cout << "iguales en tamaño" << endl;
			cola.pop();
		} else {
			cout << "tamaño incorrecto" << endl;
			return false;
		}
	}

	return true;
}