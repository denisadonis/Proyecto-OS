#ifndef BLOQUEADO_H
#define BLOQUEADO_H

#include "Proceso.h"

class Bloqueado
{
private:
	Proceso proceso;
	int tope;
	int contador;

public:
	Bloqueado() {};
	Bloqueado(Proceso);
	// ~Bloqueado();
	
	Proceso getProceso(void);
	void setProceso(Proceso);

	void aumentarContador(void);
	bool estaBloqueado(void);
};

Bloqueado::Bloqueado(Proceso proceso) {
	this->proceso = proceso;

	if (proceso.get_lock_event() == 3)
		this->tope = 13;
	else 
		this->tope = 27;

	this->contador = 0;
}

/*Bloqueado::~Bloqueado() {
	delete &this->proceso;
}
*/
Proceso Bloqueado::getProceso(void) {
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

#endif