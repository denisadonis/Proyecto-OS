#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue>
#include <cstdlib>

#include "Proceso.h"

using namespace std;

string abrirArchivo(void);
queue<string> split(string, const char);
priority_queue<Proceso> saltoNuevosAListos(queue<string> &);

int main()
{
	string s = abrirArchivo();
	queue<string> nuevos = split(s, ';');
	priority_queue<Proceso> listos = saltoNuevosAListos(nuevos);
	cout << listos.size() << endl;

	while (!listos.empty()) {
		cout << ((Proceso)listos.top()).get_priority() << endl; //Cuidado con la forma de sacar objetos de la cola
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

priority_queue<Proceso> saltoNuevosAListos(queue<string> & nuevos)
{
	queue<string> temp;
	priority_queue<Proceso> listos;
	int count = nuevos.size();
	int code[6];

	for (int i = 0; i < count; ++i)
	{
		temp = split(nuevos.front(), '/');
		if (temp.size() == 6)
		{
			for (int i = 0; i < 6; ++i)
			{
				code[i] = atoi(temp.front().c_str());
				temp.pop();
			}
			listos.emplace(code[0], code[1], code[2], code[3], code[4], code[5]);
		}
		nuevos.pop();
	}

	return listos;
}
