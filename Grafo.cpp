#include "Grafo.h"
#include <fstream>
#include <ctime>

Grafo::Grafo(int n) {
    inicializar(n);
}

void Grafo::inicializar(int n) {
    matriz.assign(n, std::vector<Ruta>(n, Ruta(INF, "Sin_ruta", true)));
    for (int i = 0; i < n; i++) {
        matriz[i][i] = Ruta(0, "Misma_ciudad", true);
    }
}

int Grafo::getCantidad() const { return ciudades.size(); }

Ciudad Grafo::getCiudad(int indice) const {
    if (indice >= 0 && indice < getCantidad()) {
        return ciudades[indice];
    }
    return Ciudad(-1, "Error");
}

int Grafo::getDistancia(int i, int j) const {
    if (i >= 0 && j >= 0 && i < getCantidad() && j < getCantidad()) {
        return matriz[i][j].getDistancia();
    }
    return INF;
}

std::string Grafo::getNombreRuta(int i, int j) const {
    if (i >= 0 && j >= 0 && i < getCantidad() && j < getCantidad()) {
        return matriz[i][j].getNombre();
    }
    return "Error";
}

std::string Grafo::agregarCiudad(std::string nombre, int x, int y) {
    int nuevoId = getCantidad();
    ciudades.push_back(Ciudad(nuevoId, nombre, x, y));

    int n = getCantidad();

    for (int i = 0; i < n - 1; i++) {
        matriz[i].push_back(Ruta(INF, "Sin_ruta", true));
    }

    std::vector<Ruta> nuevaFila(n, Ruta(INF, "Sin_ruta", true));
    nuevaFila[n - 1] = Ruta(0, "Misma_ciudad", true);
    matriz.push_back(nuevaFila);

    return "Ciudad '" + nombre + "' agregada con ID " + std::to_string(nuevoId);
}

std::string Grafo::agregarConexion(int i, int j, int distancia, std::string nombreRuta) {
    if (i < 0 || j < 0 || i >= getCantidad() || j >= getCantidad()) {
        return "Error: Indices invalidos";
    }
    matriz[i][j] = Ruta(distancia, nombreRuta, true);
    matriz[j][i] = Ruta(distancia, nombreRuta, true);
    return "Conexion agregada correctamente";
}

std::string Grafo::cortarRuta(int i, int j) {
    if (i < 0 || j < 0 || i >= getCantidad() || j >= getCantidad()) {
        return "Error: Indices invalidos";
    }
    matriz[i][j].setEstado(false);
    matriz[j][i].setEstado(false);
    return "Ruta cortada correctamente";
}

std::string Grafo::restaurarRuta(int i, int j) {
    if (i < 0 || j < 0 || i >= getCantidad() || j >= getCantidad()) {
        return "Error: Indices invalidos";
    }
    matriz[i][j].setEstado(true);
    matriz[j][i].setEstado(true);
    return "Ruta restaurada correctamente";
}

std::string Grafo::estadoCiudad(int id, bool nuevoEstado) {
    if (id < 0 || id >= getCantidad()) {
        return "Error: ID de ciudad invalido";
    }
    
    if (ciudades[id].getEstado() == nuevoEstado) {
        return "La ciudad ya esta en el estado deseado";
    } else {
        ciudades[id].setEstado(nuevoEstado);
        return "Ciudad con ID " + std::to_string(id) + " actualizada";
    }
}

std::string Grafo::modificarCiudad(int id, std::string nuevoNombre, int nuevaX, int nuevaY) {
    if (id < 0 || id >= getCantidad()) {
        return "Error: ID de ciudad invalido";
    }

    if (!ciudades[id].getEstado()) {
        return "Error: La ciudad esta dada de baja. Rehabilitela antes de modificarla.";
    }

    ciudades[id].setNombre(nuevoNombre);
    ciudades[id].setX(nuevaX);
    ciudades[id].setY(nuevaY);

    return "Ciudad modificada correctamente";
}

std::string Grafo::guardarArchivo() {
    std::ofstream f("grafo.txt");
    if (!f) {
        return "ERROR: No se pudo crear el archivo";
    }

    int n = getCantidad();
    f << n << std::endl;

    for (const auto& c : ciudades) {
        f << c.getId() << " " << c.getNombre() << " " << c.getX() << " " << c.getY() << " " << c.getEstado() << std::endl;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f << matriz[i][j].getDistancia() << " " 
              << matriz[i][j].getNombre() << " " 
              << matriz[i][j].getEstado() << " ";
        }
        f << std::endl;
    }

    f.close();
    return "Archivo guardado correctamente";
}

std::string Grafo::cargarArchivo() {
    std::ifstream f("grafo.txt");
    if (!f) {
        return "ERROR: No existe el archivo";
    }

    int n;
    f >> n;

    ciudades.clear();
    inicializar(n);

    for (int i = 0; i < n; i++) {
        int id, x, y;
        std::string nombre;
        bool estado;
        f >> id >> nombre >> x >> y >> estado;
        Ciudad c(id, nombre, x, y);
        c.setEstado(estado);
        ciudades.push_back(c);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dist;
            std::string nom;
            bool estado;
            f >> dist >> nom >> estado;
            matriz[i][j] = Ruta(dist, nom, estado);
        }
    }

    f.close();
    return "Archivo cargado correctamente";
}

void Grafo::guardarHistorial(const std::string& caminoStr, int distancia) {
    time_t ahora = time(0);
    std::string fechaStr = ctime(&ahora);
    if (!fechaStr.empty() && fechaStr.back() == '\n') {
        fechaStr.pop_back();
    }

    std::ofstream hist("historial.txt", std::ios::app);
    hist << "[" << fechaStr << "] " << caminoStr << " | " << distancia << " km" << std::endl;
    hist.close();
}

std::string Grafo::dijkstra(int origen, int destino) {
    int n = getCantidad();
    
    if (origen < 0 || destino < 0 || origen >= n || destino >= n) {
        return "Error: Indices invalidos";
    }

    std::vector<int> dist(n, INF);
    std::vector<bool> visitado(n, false);
    std::vector<int> previo(n, -1);

    dist[origen] = 0;
    
    if (ciudades[origen].getEstado() == false || ciudades[destino].getEstado() == false) {
        return "Error: Origen o destino inhabilitado";
    }
    
    for (int i = 0; i < n - 1; i++) {
        int minDist = INF, u = -1;

        for (int j = 0; j < n; j++) {
            if (ciudades[j].getEstado() == true && !visitado[j] && dist[j] <= minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        
        if (u != -1) {
            visitado[u] = true;

            for (int v = 0; v < n; v++) {
                if (ciudades[v].getEstado() == true) {
                    int peso = matriz[u][v].getDistancia();
                    
                    if (!visitado[v] && peso != INF && matriz[u][v].getEstado() == true && dist[u] + peso < dist[v]) {
                        dist[v] = dist[u] + peso;
                        previo[v] = u;
                    }
                }
            }
        }
    }

    if (dist[destino] == INF) {
        return "No hay ruta disponible";
    }

    std::vector<int> camino;
    int v = destino;
    while (v != -1) {
        camino.push_back(v);
        v = previo[v];
    }

    std::string caminoStr = ciudades[camino.back()].getNombre();
    for (int i = camino.size() - 2; i >= 0; i--) {
        int u = camino[i + 1];
        int nodoDestino = camino[i];
        caminoStr += " -> (" + matriz[u][nodoDestino].getNombre() + ") -> " + ciudades[nodoDestino].getNombre();
    }

    guardarHistorial(caminoStr, dist[destino]);
    
    return "Distancia minima: " + std::to_string(dist[destino]) + " km\nCamino: " + caminoStr;
}