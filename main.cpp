#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue> 
#include <cstdlib>
#include <cctype>
#include <iomanip>

#include "Proceso.h"
#include "Ejecutando.h"
#include "Bloqueado.h"

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

top
 accesses the top element 

empty
 checks whether the underlying container is empty 

size
 returns the number of elements 

push
 inserts element and sorts the underlying container 

emplace
constructs element in-place and sorts the underlying container 

pop
removes the top element 

swap
swaps the contents 
 */

// Prototipos de Funciones
string abrirArchivo(void); // Función que Abre un archivo y devuelve un string con todos los elementos concatenados.
queue<string> split(string, const char); // Función para separar cadenas, devuelve una cola sin prioridad.
void moverDeNuevosListos(queue<string> &, priority_queue<Proceso> &); // Función encargada de recibir los procesos.

int main()
{
	int parada;
	int ciclosProcesador;
	cout << "Indique el Numero de Ciclos para el programa: " << endl;
	cin >> ciclosProcesador;

	// Divide los procesos cada vez que encuentra un ";" al llamar la Funcion split y los almacena en la variable "nuevos".
	queue<string> nuevos = split(abrirArchivo(), ';'); 
	priority_queue<Proceso> listos;
	queue<Bloqueado> bloqueados;
	queue<Proceso> finalizados;

	Bloqueado temp;
	int tamanio;

	bool estado = true;

	int count = nuevos.size(); // Variable que Almacena la cantidad de procesos almacenados en el archivo de texto.

	cout << "Procesos en el archivo de Texto:" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << nuevos.front() << endl;
		nuevos.push(nuevos.front());
		nuevos.pop();
	}

	cout << "--------------------" << endl;
	cout << "Proceos que No Cumplen los Requisitos:" << endl;
	
	// LLamado a la Función.
	moverDeNuevosListos(nuevos, listos);

	cout << "--------------------" << endl;
	
	/*
	while (!listos.empty()) { // El While funciona mientras listos no este vacio.
		cout << ID:	<< ((Proceso)listos.top()).get_id() << endl;

		listos.pop();
	}
	*/

	//cout << "ID : " << ((Proceso)listos.top()).get_id() << endl;

	cout << "ID que se va a Ejecutar Primero : " << ((Proceso)listos.top()).get_id() << endl;
	Ejecutando ejecutando( ((Proceso)listos.top()) );
	listos.pop(); // Saca el Proceso de listos

	// ----- Ciclos del Programa (FOR principal) -----
	for (int i = 1; i <= ciclosProcesador; i++) {
		

		ejecutando.incrementarContador(); // El contador ira aumentando luego de cada ciclo

		if (ejecutando.listoParaBloquear() & estado) {
			bloqueados.emplace(ejecutando.get_proceso());
			ejecutando.set_proceso(listos.top());
			listos.pop();
			cout << "fui bloqueado" << endl;
			estado = false;
		}

		if (ejecutando.validarNumInstrucciones() & estado) {
				
				finalizados.push(ejecutando.get_proceso());
				ejecutando.set_proceso(listos.top());
				listos.pop();
				
				cout << "Terminados: " 
						<< ((Proceso)finalizados.front()).get_id() << endl;
				estado = false; // Evita que el programa continue con las demas instrucciones pero si que continue el for
		}

		if (i % 5 == 0 & estado) { // al llegar a los 5 ciclos, cambiara de proceso por otro

			ejecutando.incrementarSegmento();
		
			if(ejecutando.validarSegmentos()) {
				
				ejecutando.disminuirPrioridad();
			}

			listos.push(ejecutando.get_proceso());
			
			ejecutando.set_proceso(listos.top());

			listos.pop();
		}

		if (!bloqueados.empty()) {
			tamanio = bloqueados.size();
			cout << tamanio << endl;
			for (int i = 0; i < tamanio; i++) {
				temp = bloqueados.front();
				bloqueados.pop();

				temp.aumentarContador();
				if (!temp.estaBloqueado()) {
					listos.push(temp.getProceso());
				} else {
					bloqueados.push(temp);
				}

			}
		} // fin if bloqueados

		cout << "Ciclo: " << (i) << endl;
		estado = true;
	}

	listos.push(ejecutando.get_proceso());

	cout << "--------------------" << endl;
	cout << "Proceos que Si Cumplen los Requisitos:" << endl;
	while (!listos.empty()) { // El While funciona mientras listos no este vacio.
		cout << setfill('0') << setw(3) // Inserta el caracter dentro de setfill('') hasta el numero de veces que tiene setw().
				<< ((Proceso)listos.top()).get_id() << "/"
				<< ((Proceso)listos.top()).get_state() << "/" 
				<< ((Proceso)listos.top()).get_priority() << "/"
				<< setfill('0') << setw(3) // Inserta el caracter dentro de setfill('') hasta el numero de veces que tiene setw().
				<< ((Proceso)listos.top()).get_n_instruction() << "/"
				<< setfill('0') << setw(3) // Inserta el caracter dentro de setfill('') hasta el numero de veces que tiene setw().
				<< ((Proceso)listos.top()).get_lock_instruction() << "/"
				<< ((Proceso)listos.top()).get_lock_event() << "/"
				<< ((Proceso)listos.top()).get_contador() << endl;

		listos.pop();
	}

	while (!bloqueados.empty()) {
		cout << ((Proceso)bloqueados.front().getProceso()).get_id() << endl;
		bloqueados.pop();
	}

	cin >> parada; // Para que el .exe no se pare de un solo.

	return 0;
}

// -- Funcion encargada de abrir un archivo y guardar las lineas en una variable que luego se retorna. -- 
string abrirArchivo(void) {
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
	return data; // Todo la informacion del archivo se mantiene aqui y se retorna.
}

// -- Funcion encargada de dividir las cadenas (string data, char delimitador(Ejem:';')). --
queue<string> split(string str, const char delimiter){

	istringstream isstream(str);
	queue<string> cola;
	string word = "";

	while(std::getline(isstream, word, delimiter)) { // (data, palabra vacia, "/").
  		if (word != "\n"){ // Si word es diferente de salto de linea.
				cola.push(word);	        
  		}
  	}

  //cout << "Valor Enfrente: " << cola.front() << endl;
	return cola;
}

/* recibe la referencia de una cola de string y devuelve una cola de prioridad con.
todos los procesos que cumplen los requisitos para poder ejecutarse. */
//&nuevos llega con xxxx/x/x/xxx/xxx/x(varios procesos), &listos llega vacio.
void moverDeNuevosListos(queue<string> &nuevos, priority_queue<Proceso> &listos) 
{
	
	bool validarProceso(queue<string> cola); // Prototipo de Funcion que solo esta Funcion puede usar para validar los procesos.
	
	queue<string> temp; // Cola donde se almacenaran las cadenas resultantes depues de dividir los procesos.
	int count = nuevos.size(); // Variable que tiene el Tamaño de la Cola para poder ser usada en el ciclo.
	int code[6]; // Variable donde se guardaran temporalmente los datos de un proceso para despues poder ser insertados en la cola.

	for (int i = 0; i < count; i++)
	{
		// temp, contiene las "6" partes de un proceso correcto (podrian ser mas y ser un proceso Invalido ó tambien menos).
		temp = split(nuevos.front(), '/'); 
		
		if (validarProceso(temp)) // validacion de los procesos que retorna true ó false.
		{

			for (int i = 0; i < 6; i++)
			{
				// atoi convierte cadenas a enteros, luego del primer digito, cualquier simbolo/letra sera ignorado.
				code[i] = stoi(temp.front()); 
				temp.pop();
			}
			listos.emplace(code[0], code[1], code[2], code[3], code[4], code[5]);
		} else {
			cout << nuevos.front() << endl;
			nuevos.push(nuevos.front()); // Vuelve a meter los procesos al final de la cola
		}
		nuevos.pop(); // Saca cada unos de los varios procesos que tiene hasta que quede vacio.
	}
}

// -- Esta Funcion tiene el objetivo de validar los procesos --
bool validarProceso(queue<string> cola) {

	string temporal[6]; // Guarda cada parte de un proceso.
	static queue<string> hist_ids; // Variable estatica donde se guardara el historial de ids.
	
	int paso[6]; // Espacios que tienen cada unas de las partes de un Proceso.
	paso[0] = 4; // Id del Proceso.
	paso[1] = 1; // Estado del Proceso.
	paso[2] = 1; // Prioridad.
	paso[3] = 3; // Cantidad de Instrucciones.
	paso[4] = 3; // Numeros de instruccion donde se iniciara el bloqueo del proceso.
	paso[5] = 1; // Evento por el que espera (3 = E/S 13 ciclos, 5 = Disco duro 27 ciclos).

	// Comprueba si el Proceso consta de 6 partes separadas por "/".
	if(cola.size() != 6){
		cout << "El Proceso esta Incompleto:" << endl;
		return false;
	}

	// Comprueba si cada parte del Prooceso consta de el tamaño correcto de espacios(caracteres).
	for (int i = 0; i < 6; i++){
		if(cola.front().size() == paso[i]){
			
			// ** Es necesario volver a meter el valor al final de la cola para las proximas validaciones.
			cola.push(cola.front()); 
			cola.pop();
		} else {

			//cout << cola.front().size();
			cout << "El Espacio de una parte del Proceso es Incorrecto:" << endl;
			return false;
		}
	}

	// Comprueba si los procesos tienen caracteres invalidos (Letras o simbolos).
	// Se necesita que recorra las 6 partes del proceso para posibles errores.
	for(int i = 0; i < 6; i++){
		
		// Recorre cada una de las Partes del proceso en busca de un caracter invalido.
		for(int j = 0; j < paso[i]; j++){
			
			// Hace la comparacion para ver si cada caracter es un digito (0-9).
			if(!isdigit(cola.front()[j])){ // Si No es un numero.
				cout << "El Proceso no debe tener caracteres diferentes de un numero:" << endl;
				return false;
			}
		}
		//cout << i << ". Temporal: " << temporal[i] << endl;
		temporal[i] = cola.front();

		// Es necesario volver a meter el valor al final de la cola para las proximas validaciones.
		cola.push(cola.front());
		cola.pop(); // Se saca el valor enfrente para continuar con las demas partes.
	}

	// Se encarga de validar la prioridad (El valor debe estar entre 1 y 3).
	if(stoi(temporal[2]) < 1 || stoi(temporal[2]) > 3){ // stoi(str) - convierte una cadena a valor numerico.
		cout << "La prioridad de un proceso debe estar entre 1 y 3:" << endl;
		return false;
	}

	// Se encarga de validar que la Cantidad de Instrucciones deba de ser MAYOR a las de bloqueo.
	if(temporal[4] > temporal[3]){
		cout << "La Instruccion de Bloqueo No puede ser mayor que la Cantidad de Instrucciones:" << endl;
		return false;
	}

	// Se encarga de validar si lleva un evento conocido.
	if(!(stoi(temporal[5]) == 3 || stoi(temporal[5]) == 5)){ // stoi(str) - convierte una cadena a valor numerico.
		cout << "No es Evento conocido:" << endl;
		return false;
	}

	// Se encarga de verificar que no existan 2+ Ids Repetidos.
	if (!hist_ids.empty())
	{
		int count = hist_ids.size(); // variable encargada del numero de IDs validos

		for (int i = 0; i < count; i++)
		{
			if (temporal[0] != hist_ids.front()) { // Si el ID no es igual a los demas, se agregara a la lista
				hist_ids.push(temporal[0]);
			} else {
				cout << "El ID ya fue usado anteriormente:" << endl;
				return false;
			}
			hist_ids.push(hist_ids.front());
			hist_ids.pop();
		}
	} else {
		hist_ids.push(temporal[0]);
	}

	// Si no se encontro ningun error, la funcion retorna true.
	return true;
}