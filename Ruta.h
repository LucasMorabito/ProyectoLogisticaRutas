#ifndef RUTA_H
#define RUTA_H

#include <string>

const int INF = 999999;

class Ruta {
private:
    int distancia;
    std::string nombre;
    bool estado;

public:
    Ruta(int distancia = INF, std::string nombre = "Sin_ruta", bool estado = true);

    int getDistancia() const;
    std::string getNombre() const;
    bool getEstado() const;

    void setDistancia(int distancia);
    void setNombre(std::string nombre);
    void setEstado(bool estado);
};

#endif