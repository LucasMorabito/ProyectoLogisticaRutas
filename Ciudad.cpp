#include "Ciudad.h"

Ciudad::Ciudad(int id, std::string nombre, int x, int y) {
    this->id = id;
    this->nombre = nombre;
    this->x = x;
    this->y = y;
    this->estado = true;
}

int Ciudad::getId() const { return id; }
std::string Ciudad::getNombre() const { return nombre; }
int Ciudad::getX() const { return x; }
int Ciudad::getY() const { return y; }

void Ciudad::setId(int id) { this->id = id; }
void Ciudad::setNombre(std::string nombre) { this->nombre = nombre; }
void Ciudad::setX(int x) { this->x = x; }
void Ciudad::setY(int y) { this->y = y; }

void Ciudad::setEstado(bool nuevoEstado) { estado = nuevoEstado; }
bool Ciudad::getEstado() const { return estado; }