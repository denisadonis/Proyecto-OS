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
	int parada;
	int ciclosProcesador;
	cout << "Indique el Numero de Ciclos para el programa: " << endl;
	cin >> ciclosProcesador;

	queue<string> nuevos = split(abrirArchivo(), ';');
	priority_queue<Proceso> listos;

	moverDeNuevosListos(nuevos, listos);
	
	//cout << "tamaño: " << listos.size() << endl;

	cout << "--------------------" << endl;
	cout << "Proceos que no cumplen los requisitos:" << endl;
	while (!nuevos.empty()) {
		cout << nuevos.front() << endl;
		nuevos.pop();
	}

	cout << "--------------------" << endl;

	while (!listos.empty()) { // Funciona mientras listos no este vacio
		cout << "ID del proceso: " << ((Proceso)listos.top()).get_id() << endl;
		cout << "Prioridad: " << ((Proceso)listos.top()).get_priority() << endl; //Cuidado con la forma de sacar objetos de la cola

		//cout << "primeros en la lista: " << listos.top() << endl;

		listos.pop();
	}

	cin >> parada; // Para que el .exe no se pare de un solo.

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
			data += line; // Comentario: + "\n"; estaba causando problemas
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

	istringstream isstream(str);
  	queue<string> cola;
  	string word = "";

	while(std::getline(isstream, word, delimiter)) { // (data, palabravacia, "/")
  		if (word != "\n"){
			cola.push(word);	        
  		}
  	}

  //cout << "Valor Enfrente: " << cola.front() << endl;
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
		// temp, contiene las "6" partes de un proceso correcto (ó podrian ser mas y ser un proceso Invalido).
		temp = split(nuevos.front(), '/'); 
		
		if (validarProceso(temp)) // validacion de los procesos.
		{

			for (int i = 0; i < 6; i++)
			{
				// atoi convierte cadenas a enteros, luego del primer digito, cualquier simbolo/letra sera ignorado
				code[i] = atoi(temp.front().c_str()); // .c_str() solo de esta forma se puede usar atoi en string
				temp.pop();
			}
			listos.emplace(code[0], code[1], code[2], code[3], code[4], code[5]);

		} else {
			nuevos.push(nuevos.front());
		}
		nuevos.pop(); // Saca cada unos de los varios procesos que tiene hasta que quede vacio.
	}
}

// Esta funcion tiene el objetivo de validar los procesos.
bool validarProceso(queue<string> cola) {

	string temporal[6];
	// Espacios que tienen cada unas de las partes de un Proceso.
	int paso[6];
	paso[0] = 4; // Id del Proceso
	paso[1] = 1; // Estado del Proceso
	paso[2] = 1; // Prioridad
	paso[3] = 3; // Cantidad de Instrucciones
	paso[4] = 3; // Numeros de instruccion donde se iniciara el bloqueo del proceso
	paso[5] = 1; // Evento por el que espera (3 = E/S 13 ciclos, 5 = Disco duro 27 ciclos)

	// Comprueba si el Proceso consta de 6 partes separadas por "/".
	if(cola.size() != 6){
		cout << "El Proceso esta Incompleto." << endl;
		return false;
	}

	// Comprueba si cada parte del Prooceso consta de el tamaño correcto de espacios(caracteres).
	for (int i = 0; i < 6; i++){
		if(cola.front().size() == paso[i]){
			
			// Es necesario volver a meter el valor al final de la cola para las proximas validaciones.
			cola.push(cola.front()); 
			cola.pop();
		} else {

			//cout << cola.front().size();
			cout << "El Espacio de una parte del Proceso es Incorrecto." << endl;
			return false;
		}
	}

	// Se necesita que recorra las 6 partes del proceso para validaciones.
	for(int i = 0; i < 6; i++){
		// Recorre cada Parte del proceso en busca de un caracter diferente de un numero.
		for(int j = 0; j < paso[i]; j++){
			// Hace la comparacion para ver si cada caracter es un digito (0-9).
			if(!isdigit(cola.front()[j])){
				cout << "contiene una caracter diferente a un numero, por lo tanto es incorrecto" << endl;
				return false;
			}
		}

		temporal[i] = cola.front();
		//cout << i << ". Temporal: " << temporal[i] << endl;

		// Es necesario volver a meter el valor al final de la cola para las proximas validaciones.
		cola.push(cola.front());
		cola.pop(); // Se saca el valor enfrente para continuar con las demas partes.
	}

	// Se encarga de validar la prioridad (El valor debe estar entre 1 y 3).
	if(stoi(temporal[2]) < 1 || stoi(temporal[2]) > 3){ // stoi(str) - convierte una cadena a valor numerico
		cout << "La prioridad de un proceso debe estar entre 1 y 3." << endl;
		return false;
	}

	// Se encarga de validar que la Cantidad de Instrucciones deba de ser MAYOR a las de bloqueo.
	if(temporal[4] > temporal[3]){
		cout << "Instruccion de Bloqueo No puede ser mayor que la Cantidad de Instrucciones." << endl;
		return false;
	}

	// Se encarga de validar si lleva un evento conocido
	if(!(stoi(temporal[5]) == 3 || stoi(temporal[5]) == 5)){
		cout << "No es Evento conocido." << endl;
		return false;
	}

	// Si no se encontro ningun error, la funcion retorna true.
	return true;
}