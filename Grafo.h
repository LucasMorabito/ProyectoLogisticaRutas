#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include "Ciudad.h"
#include "Ruta.h"

class Grafo {
private:
    std::vector<Ciudad> ciudades;
    std::vector<std::vector<Ruta>> matriz;

public:
    Grafo(int n = 0);

    void inicializar(int n);
    int getCantidad() const;
    Ciudad getCiudad(int indice) const;
    int getDistancia(int i, int j) const;
    std::string getNombreRuta(int i, int j) const;

    std::string agregarCiudad(std::string nombre, int x, int y);
    std::string agregarConexion(int i, int j, int distancia, std::string nombreRuta);
    std::string cortarRuta(int i, int j);
    std::string restaurarRuta(int i, int j);
    std::string estadoCiudad(int id, bool nuevoEstado);
    std::string modificarCiudad(int id, std::string nuevoNombre, int nuevaX, int nuevaY);
    
    std::string guardarArchivo();
    std::string cargarArchivo();
    void guardarHistorial(const std::string& caminoStr, int distancia);
    std::string dijkstra(int origen, int destino);
};

#endif