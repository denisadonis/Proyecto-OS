#ifndef PROCESO_H
#define PROCESO_H 

#include <string>
using std::string;
#include <iostream>

class Proceso
{

	private:
	
		int id;
		int state; 
		int priority;
		int n_instruction;
		int lock_instrution;
		int lock_event;

	public:

		Proceso(int,int,int,int,int,int);
		~Proceso() {}; // Destructor

		bool operator<(const Proceso &element) const;

		void set_id(int);
		void set_state(int);
		void set_priority(int);
		void set_n_instruction(int);
		void set_lock_instruction(int);
		void set_lock_event(int);

		int get_id(void);
		int get_state(void);
		int get_priority(void);
		int get_n_instruction(void);
		int get_lock_instruction(void);
		int get_lock_event(void);
};

// 4444 Id del proceso, 1 estado del proceso, 1 prioridad del proceso, 333 cantidad de instrucciones
// 333 Numero de instrucciones donde se iniciara el bloquado del proceso, 1 evento por el que espera
Proceso::Proceso(int id, int state, int priority, int n_ins, int lock_i, int lock_e) {
	this->id = id;
	this->state = state;
	this->priority = priority;
	this->n_instruction = n_ins;
	this->lock_instrution = lock_i;
	this->lock_event = lock_e;
}

bool Proceso::operator < (const Proceso &element) const {
	return this->priority > element.priority;
}

// Metodos Set
void Proceso::set_id(int id) {
	this->id = id;
}
void Proceso::set_state(int state) {
	this->state = state;
}
void Proceso::set_priority(int priority) {
	this->priority = priority;
}
void Proceso::set_n_instruction(int n_instruction) {
	this->n_instruction = n_instruction;
}
void Proceso::set_lock_instruction(int lock_instrution) {
	this->lock_instrution = lock_instrution;
}
void Proceso::set_lock_event(int get_lock_event) {
	this->lock_event = lock_event;
}

// Metodos Get
int Proceso::get_id(void) {
	return this->id;
}
int Proceso::get_state(void) {
	return this->state;
}
int Proceso::get_priority(void) {
	return this->priority;
}
int Proceso::get_n_instruction(void) {
	return this->n_instruction;
}
int Proceso::get_lock_instruction(void) {
	return this->lock_instrution;
}
int Proceso::get_lock_event(void) {
	return this->lock_event;
}

#endif