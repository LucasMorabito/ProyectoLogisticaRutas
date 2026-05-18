#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

const int INF = 999999;

class Ciudad {
private:
    int id;
    string nombre;
    int x, y;

public:
    Ciudad(int id = 0, string nombre = "", int x = 0, int y = 0) {
        this->id = id;
        this->nombre = nombre;
        this->x = x;
        this->y = y;
    }

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    void imprimir() const {
        cout << id << " - " << nombre << endl;
    }
};

class Conexion {
private:
    int distNacional;
    int distProvincial;
    int distRural;

public:
    Conexion(int n = INF, int p = INF, int r = INF) {
        distNacional   = n;
        distProvincial = p;
        distRural      = r;
    }

    int getDistNacional()   const { return distNacional; }
    int getDistProvincial() const { return distProvincial; }
    int getDistRural()      const { return distRural; }

    void setDistNacional(int d)   { distNacional   = d; }
    void setDistProvincial(int d) { distProvincial = d; }
    void setDistRural(int d)      { distRural      = d; }

    int getMejorDistancia() const {
        int mejor = INF;
        if (distNacional   < mejor) mejor = distNacional;
        if (distProvincial < mejor) mejor = distProvincial;
        if (distRural      < mejor) mejor = distRural;
        return mejor;
    }

    string getMejorTipo() const {
        if (distNacional == INF && distProvincial == INF && distRural == INF)
            return "Ninguna";

        if (distNacional <= distProvincial && distNacional <= distRural)
            return "Nacional";

        if (distProvincial <= distNacional && distProvincial <= distRural)
            return "Provincial";

        return "Rural";
    }
};

class Grafo {
private:
    vector<Ciudad>            ciudades;
    vector<vector<Conexion>>  matriz;

public:
    Grafo(int n = 0) {
        inicializar(n);
    }

    void inicializar(int n) {
        matriz.assign(n, vector<Conexion>(n));
        for (int i = 0; i < n; i++)
            matriz[i][i] = Conexion(0, 0, 0);
    }

    int getCantidad() const { return ciudades.size(); }

    void agregarCiudad(string nombre, int x, int y) {
        int nuevoId = getCantidad();
        ciudades.push_back(Ciudad(nuevoId, nombre, x, y));

        int n = getCantidad();

        for (int i = 0; i < n - 1; i++) {
            matriz[i].push_back(Conexion());
        }

        vector<Conexion> nuevaFila(n);
        nuevaFila[n - 1] = Conexion(0, 0, 0);
        matriz.push_back(nuevaFila);

        cout << "Ciudad '" << nombre << "' agregada con ID " << nuevoId << "\n";
    }

    void agregarConexion(int i, int j, int distancia, string tipo) {
        if (tipo == "Nacional") {
            matriz[i][j].setDistNacional(distancia);
            matriz[j][i].setDistNacional(distancia);
        } else if (tipo == "Provincial") {
            matriz[i][j].setDistProvincial(distancia);
            matriz[j][i].setDistProvincial(distancia);
        } else if (tipo == "Rural") {
            matriz[i][j].setDistRural(distancia);
            matriz[j][i].setDistRural(distancia);
        } else {
            cout << "Tipo invalido. Use Nacional, Provincial o Rural.\n";
        }
    }

    void cortarRuta(int i, int j, string tipo) {
        if (tipo == "Nacional") {
            matriz[i][j].setDistNacional(INF);
            matriz[j][i].setDistNacional(INF);
        } else if (tipo == "Provincial") {
            matriz[i][j].setDistProvincial(INF);
            matriz[j][i].setDistProvincial(INF);
        } else if (tipo == "Rural") {
            matriz[i][j].setDistRural(INF);
            matriz[j][i].setDistRural(INF);
        } else {
            cout << "Tipo invalido. Use Nacional, Provincial o Rural.\n";
        }
    }

    void mostrarCiudades() {
        cout << "\n--- CIUDADES ---\n";
        for (int i = 0; i < getCantidad(); i++)
            ciudades[i].imprimir();
    }

    void mostrarMatriz() {
        cout << "\n--- MATRIZ (mejor distancia) ---\n";
        for (int i = 0; i < getCantidad(); i++) {
            for (int j = 0; j < getCantidad(); j++) {
                int d = matriz[i][j].getMejorDistancia();
                if (d == INF)
                    cout << "INF\t";
                else
                    cout << d << "\t";
            }
            cout << endl;
        }
    }

    void guardarArchivo() {
        ofstream f("grafo.txt");
        if (!f) {
            cout << "ERROR: No se pudo crear el archivo\n";
            return;
        }

        int n = getCantidad();
        f << n << endl;

        for (int i = 0; i < ciudades.size(); i++) {
            Ciudad& c = ciudades[i];
            f << c.getId() << " " << c.getNombre() << " " << c.getX() << " " << c.getY() << endl;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                f << matriz[i][j].getDistNacional()   << " "
                  << matriz[i][j].getDistProvincial() << " "
                  << matriz[i][j].getDistRural()      << " ";
            f << endl;
        }

        f.close();
        cout << "Archivo guardado correctamente\n";
    }

    void cargarArchivo() {
        ifstream f("grafo.txt");
        if (!f) {
            cout << "ERROR: No existe el archivo\n";
            return;
        }

        int n;
        f >> n;

        ciudades.clear();
        inicializar(n);

        for (int i = 0; i < n; i++) {
            int id, x, y;
            string nombre;
            f >> id >> nombre >> x >> y;
            ciudades.push_back(Ciudad(id, nombre, x, y));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int dn, dp, dr;
                f >> dn >> dp >> dr;
                matriz[i][j] = Conexion(dn, dp, dr);
            }
        }

        f.close();
        cout << "Archivo cargado correctamente\n";
    }

    void guardarHistorial(const string& caminoStr, int distancia) {
        time_t ahora = time(0);
        string fechaStr = ctime(&ahora);
        if (!fechaStr.empty() && fechaStr.back() == '\n') {
            fechaStr.pop_back();
        }

        ofstream hist("historial.txt", ios::app);
        hist << "[" << fechaStr << "] " << caminoStr << " | " << distancia << " km" << endl;
        hist.close();
    }

    void dijkstra(int origen, int destino) {
        int n = getCantidad();

        vector<int>  dist(n, INF);
        vector<bool> visitado(n, false);
        vector<int>  previo(n, -1);

        dist[origen] = 0;

        for (int i = 0; i < n - 1; i++) {
            int minDist = INF, u = -1;

            // encuentra nodo no visitado con menor distancia
            for (int j = 0; j < n; j++) {
                if (!visitado[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }
            
            if (u == -1) break;
            visitado[u] = true;

            // conexiones desde u
            for (int v = 0; v < n; v++) {
                int peso = matriz[u][v].getMejorDistancia();
                if (!visitado[v] && peso != INF && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    previo[v] = u;
                }
            }
        }

        if (dist[destino] == INF) {
            cout << "No hay ruta disponible\n";
            return;
        }

        // reconstruye camino desde destino a origen
        vector<int> camino;

        int v = destino;
        while (v != -1) {
            camino.push_back(v);
            v = previo[v];
        }

        // formatea camino para mostrarlo
        string caminoStr = "";
        for (int i = camino.size() - 1; i >= 0; i--) {
            caminoStr += ciudades[camino[i]].getNombre();
            if (i != 0) {
                int desde = camino[i];
                int hasta = camino[i - 1];
                caminoStr += " -[" + matriz[desde][hasta].getMejorTipo() + "]-> ";
            }
        }

        cout << "\nDistancia minima: " << dist[destino] << " km\n";
        cout << "Camino: " << caminoStr << endl;

        guardarHistorial(caminoStr, dist[destino]);
    }
};

int main() {

    Grafo g(0);

    // g.agregarCiudad("Corrientes",  10,  10);
    // g.agregarCiudad("Goya",        20, 50);
    // g.agregarCiudad("Mercedes",    50, 30);

    // // Conexión A: Corrientes (0) <-> Goya (1)
    // g.agregarConexion(0, 1, 225, "Nacional");
    // g.agregarConexion(0, 1, 240, "Provincial");
    // g.agregarConexion(0, 1, 260, "Rural");

    // // Conexión B: Goya (1) <-> Mercedes (2)
    // g.agregarConexion(1, 2, 146, "Nacional");
    // g.agregarConexion(1, 2, 160, "Provincial");
    // g.agregarConexion(1, 2, 180, "Rural");

    int op;

    do {
        cout << "\n====== SISTEMA LOGISTICO - CORRIENTES ======\n";
        cout << "1. Ver ciudades\n";
        cout << "2. Ver matriz\n";
        cout << "3. Calcular ruta\n";
        cout << "4. Cortar ruta\n";
        cout << "5. Guardar\n";
        cout << "6. Cargar\n";
        cout << "7. Agregar ciudad\n";
        cout << "8. Agregar conexion\n";
        cout << "0. Salir\n";
        cin >> op;

        switch (op) {

        case 1:
            g.mostrarCiudades();
            break;

        case 2:
            g.mostrarMatriz();
            break;

        case 3: {
            int o, d;
            g.mostrarCiudades();
            cout << "Origen: ";  cin >> o;
            cout << "Destino: "; cin >> d;
            if (o < 0 || d < 0 || o >= g.getCantidad() || d >= g.getCantidad()) {
                cout << "Indices invalidos\n";
                break;
            }
            g.dijkstra(o, d);
            break;
        }

        case 4: {
            int a, b;
            string tipo;
            g.mostrarCiudades();
            cout << "Ingrese dos ciudades (ej: 0 2): ";
            cin >> a >> b;
            if (a < 0 || b < 0 || a >= g.getCantidad() || b >= g.getCantidad()) {
                cout << "Indices invalidos\n";
                break;
            }
            cout << "Tipo de ruta a cortar (Nacional, Provincial, Rural): ";
            cin >> tipo;
            g.cortarRuta(a, b, tipo);
            cout << "Ruta cortada correctamente\n";
            break;
        }

        case 5:
            g.guardarArchivo();
            break;

        case 6:
            g.cargarArchivo();
            break;

        case 7: {
            string nombre;
            int x, y;
            cout << "Nombre de la ciudad: "; cin >> nombre;
            cout << "Coordenada X: ";        cin >> x;
            cout << "Coordenada Y: ";        cin >> y;
            g.agregarCiudad(nombre, x, y);
            break;
        }

        case 8: {
            int a, b, dist;
            string tipo;
            g.mostrarCiudades();
            cout << "Ciudad origen: ";  cin >> a;
            cout << "Ciudad destino: "; cin >> b;
            if (a < 0 || b < 0 || a >= g.getCantidad() || b >= g.getCantidad()) {
                cout << "Indices invalidos\n";
                break;
            }
            cout << "Distancia (km): "; cin >> dist;
            cout << "Tipo (Nacional, Provincial, Rural): "; cin >> tipo;
            g.agregarConexion(a, b, dist, tipo);
            cout << "Conexion agregada correctamente\n";
            break;
        }
        }

    } while (op != 0);

    return 0;
}