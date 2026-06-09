#include "Ruta.h"

Ruta::Ruta(int distancia, std::string nombre, bool estado) {
    this->distancia = distancia;
    this->nombre = nombre;
    this->estado = estado;
}

int Ruta::getDistancia() const { return distancia; }
std::string Ruta::getNombre() const { return nombre; }
bool Ruta::getEstado() const { return estado; }

void Ruta::setDistancia(int distancia) { this->distancia = distancia; }
void Ruta::setNombre(std::string nombre) { this->nombre = nombre; }
void Ruta::setEstado(bool estado) { this->estado = estado; }