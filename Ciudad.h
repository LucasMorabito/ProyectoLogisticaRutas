#ifndef CIUDAD_H
#define CIUDAD_H

#include <string>

class Ciudad {
private:
    int id;
    std::string nombre;
    int x, y;
    bool estado;

public:
    Ciudad(int id = 0, std::string nombre = "", int x = 0, int y = 0);

    int getId() const;
    std::string getNombre() const;
    int getX() const;
    int getY() const;

    void setId(int id);
    void setNombre(std::string nombre);
    void setX(int x);
    void setY(int y);

    void setEstado(bool nuevoEstado);
    bool getEstado() const;
};

#endif