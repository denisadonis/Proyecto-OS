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

public:
	Ejecutando(Proceso);
	~Ejecutando();

	void set_proceso(Proceso);
	void set_last_id(int);
	void set_n_segmentos(int);

	Proceso get_proceso(void);
	int get_last_id(void);
	int get_n_segmento(void);

	void incrementarContador(void);
};


Ejecutando::Ejecutando(Proceso proceso) {
	this->proceso = proceso;
	this->last_id = proceso.get_id();
	this->n_segmentos = 0;
}

Ejecutando::~Ejecutando() {
	delete &proceso;
}

void Ejecutando::set_proceso(Proceso proceso) {
	this->proceso = proceso;
}

void Ejecutando::set_last_id(int id) {
	this->last_id = id;
}

void Ejecutando::set_n_segmentos(int n) {
	this->n_segmentos = n;
}

Proceso Ejecutando::get_proceso(void) {
	return this->proceso;
}

int Ejecutando::get_n_segmento(void) {
	return this->n_segmentos;
}

int Ejecutando::get_last_id(void) {
	return this->last_id;
}

void Ejecutando::incrementarContador(void) {
	this->proceso.incrementarContador();
}

#endif