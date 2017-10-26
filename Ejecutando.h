#ifndef EJECUTANDO_H
#define EJECUTANDO_H 

#include "Proceso.h"
#include <string>

class Ejecutando
{

private:
	
	Proceso proceso;
	int last_id;
	int n_segmentos;
	bool estado;

public:
	
	Ejecutando(Proceso); // Constructor
	~Ejecutando(); // Destructor

	void set_proceso(Proceso);
	void set_last_id(int);
	void set_n_segmentos(int);
	void set_estado(bool);

	Proceso get_proceso(bool);
	int get_last_id(void);
	int get_n_segmento(void);
	bool get_estado(void);

	void incrementarContador(void);
	void incrementarSegmento(void);
	bool validarSegmentos();
	void disminuirPrioridad();
	bool validarNumInstrucciones();
	bool listoParaBloquear(void);
};

// Constructor
Ejecutando::Ejecutando(Proceso proceso) {
	this->proceso = proceso;
	this->proceso.set_state(2);
	this->last_id = proceso.get_id();
	this->n_segmentos = 0;
	this->estado = true;
}

// Destructor
Ejecutando::~Ejecutando() {
	delete &proceso;
}


// Metodos Set
void Ejecutando::set_proceso(Proceso proceso) {
	this->proceso = proceso;
	this->proceso.set_state(2);
	
	if(proceso.get_id() != last_id){
		this->n_segmentos = 0;
		this->last_id = proceso.get_id();
	}

	estado = true;
}

void Ejecutando::set_last_id(int id) {
	this->last_id = id;
}

void Ejecutando::set_n_segmentos(int n) {
	this->n_segmentos = n;
}

void Ejecutando::set_estado(bool estado) {
	this->estado = estado;
}


// Metodos Get
Proceso Ejecutando::get_proceso(bool temp = false) {
	if (listoParaBloquear())
		this->proceso.set_state(3);
	else if (validarNumInstrucciones())
		this->proceso.set_state(4);

	if (temp)
		this->proceso.set_state(1);

	return this->proceso;
}

int Ejecutando::get_n_segmento(void) {
	return this->n_segmentos;
}

int Ejecutando::get_last_id(void) {
	return this->last_id;
}

bool Ejecutando::get_estado(void) {
	return this->estado;
}

// Funciones
void Ejecutando::incrementarContador(void) {
	this->proceso.incrementarContador();
}

void Ejecutando::incrementarSegmento(void) {
	if(n_segmentos <= 3){
		this->n_segmentos++;
	}
}

bool Ejecutando::validarSegmentos(void) {
	return n_segmentos == 3;
}

void Ejecutando::disminuirPrioridad(void){
	this->proceso.disminuirPrioridad();
}

bool Ejecutando::validarNumInstrucciones(void) {
	return this->proceso.get_contador() == this->proceso.get_n_instruction();
}

bool Ejecutando::listoParaBloquear(void) {
	return this->proceso.get_contador() == this->proceso.get_lock_instruction();
}

#endif