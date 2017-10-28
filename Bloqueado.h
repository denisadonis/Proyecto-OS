#ifndef BLOQUEADO_H
#define BLOQUEADO_H

#include "Proceso.h"
#include <iostream>
using std::cout;

class Bloqueado
{

private:

	Proceso proceso;
	int tope;
	int contador;

public:

	Bloqueado() {};
	Bloqueado(Proceso);
	// ~Bloqueado(); // Destructor
	
	Proceso getProceso(void);
	void setProceso(Proceso);

	void aumentarContador(void);
	bool estaBloqueado(void);
	void verProceso(void);
};

Bloqueado::Bloqueado(Proceso proceso) {
	this->proceso = proceso;

	if (proceso.get_lock_event() == 3)
		this->tope = 13;
	else 
		this->tope = 27;

	this->contador = 0;
}

/*
Bloqueado::~Bloqueado() {
	delete &this->proceso;
}
*/
Proceso Bloqueado::getProceso(void) {
	this->proceso.set_state(1);
	return this->proceso;
}

void Bloqueado::setProceso(Proceso proceso) {
	this->proceso = proceso;
}

void Bloqueado::aumentarContador(void) {
	this->contador++;
}

bool Bloqueado::estaBloqueado(void) {
	return this->tope != this->contador;
}

void Bloqueado::verProceso(void) {
	this->proceso.verProceso();
	cout << ":" << this->contador << std::endl;
}

#endif