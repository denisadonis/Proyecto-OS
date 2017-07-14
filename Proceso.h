#ifndef PROCESO_H
#define PROCESO_H 

#include <string>
using std::string;

class Proceso
{
public:
	Proceso(int,int,int,int,int,int);
	~Proceso() {};
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
private:
	int id;
	int state; 
	int priority;
	int n_instruction;
	int lock_instrution;
	int lock_event;
};

Proceso::Proceso(int id, int state, int priority, int n_ins, int lock_i, int lock_e) {
	this->id = id;
	this->state = state;
	this->priority = priority;
	this->n_instruction = n_ins;
	this->lock_instrution = lock_i;
	this->lock_event = lock_e;
}
bool Proceso::operator<(const Proceso &element) const {
	return this->priority < element.priority;
}
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