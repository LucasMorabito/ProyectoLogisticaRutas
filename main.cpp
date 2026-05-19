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


class Grafo {
private:
    vector<Ciudad> ciudades;
    vector<vector<int>> matriz;

public:
    Grafo(int n = 0) {
        inicializar(n);
    }

    void inicializar(int n) {
        matriz.assign(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            matriz[i][i] = 0;
        }
    }

    int getCantidad() const { return ciudades.size(); }

    void agregarCiudad(string nombre, int x, int y) {
        int nuevoId = getCantidad();
        ciudades.push_back(Ciudad(nuevoId, nombre, x, y));

        int n = getCantidad();

        for (int i = 0; i < n - 1; i++) {
            matriz[i].push_back(INF);
        }

        vector<int> nuevaFila(n, INF);
        nuevaFila[n - 1] = 0;
        matriz.push_back(nuevaFila);

        cout << "Ciudad '" << nombre << "' agregada con ID " << nuevoId << "\n";
    }

    void agregarConexion(int i, int j, int distancia) {
        matriz[i][j] = distancia;
        matriz[j][i] = distancia;
    }

    void cortarRuta(int i, int j) {
        matriz[i][j] = INF;
        matriz[j][i] = INF;
    }

    void mostrarCiudades() {
        cout << "\n--- CIUDADES ---\n";
        for (int i = 0; i < getCantidad(); i++)
            ciudades[i].imprimir();
    }

    void mostrarMatriz() {
        cout << "\n--- MATRIZ ---\n";
        for (int i = 0; i < getCantidad(); i++) {
            for (int j = 0; j < getCantidad(); j++) {
                if (matriz[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << matriz[i][j] << "\t";
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
            for (int j = 0; j < n; j++) {
                f << matriz[i][j] << " ";
            }
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
                f >> matriz[i][j];
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

            for (int j = 0; j < n; j++) {
                if (!visitado[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }
            
            if (u == -1) break;
            visitado[u] = true;

            for (int v = 0; v < n; v++) {
                int peso = matriz[u][v];
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

        vector<int> camino;
        int v = destino;
        while (v != -1) {
            camino.push_back(v);
            v = previo[v];
        }

        string caminoStr = "";
        for (int i = camino.size() - 1; i >= 0; i--) {
            caminoStr += ciudades[camino[i]].getNombre();
            if (i != 0) {
                caminoStr += " -> ";
            }
        }

        cout << "\nDistancia minima: " << dist[destino] << " km\n";
        cout << "Camino: " << caminoStr << endl;

        guardarHistorial(caminoStr, dist[destino]);
    }
};


int main() {

    Grafo g(0);

    // Ciudades
    // g.agregarCiudad("Corrientes_Capital", 10, 10); // ID 0
    // g.agregarCiudad("Goya",               20, 50); // ID 1
    // g.agregarCiudad("Mercedes",           50, 30); // ID 2
    // g.agregarCiudad("Paso_de_los_Libres", 80, 60); // ID 3
    // g.agregarCiudad("Sauce",              70, 80); // ID 4

    // // Conexiones
    // g.agregarConexion(1, 0, 225); // Goya <-> Corrientes Capital
    // g.agregarConexion(0, 2, 245); // Corrientes Capital <-> Mercedes
    // g.agregarConexion(0, 3, 370); // Corrientes Capital <-> Paso de los Libres
    // g.agregarConexion(1, 2, 146); // Goya <-> Mercedes
    // g.agregarConexion(1, 4, 171); // Goya <-> Sauce
    // g.agregarConexion(2, 3, 127); // Mercedes <-> Paso de los Libres
    // g.agregarConexion(2, 4, 161); // Mercedes <-> Sauce
    // g.agregarConexion(3, 4, 267); // Paso de los Libres <-> Sauce

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
            g.mostrarCiudades();
            cout << "Ingrese dos ciudades a desconectar (ej: 0 2): ";
            cin >> a >> b;
            if (a < 0 || b < 0 || a >= g.getCantidad() || b >= g.getCantidad()) {
                cout << "Indices invalidos\n";
                break;
            }
            g.cortarRuta(a, b);
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
            cout << "Nombre de la ciudad (sin espacios): "; cin >> nombre;
            cout << "Coordenada X: ";        cin >> x;
            cout << "Coordenada Y: ";        cin >> y;
            g.agregarCiudad(nombre, x, y);
            break;
        }

        case 8: {
            int a, b, dist;
            g.mostrarCiudades();
            cout << "Ciudad origen: ";  cin >> a;
            cout << "Ciudad destino: "; cin >> b;
            if (a < 0 || b < 0 || a >= g.getCantidad() || b >= g.getCantidad()) {
                cout << "Indices invalidos\n";
                break;
            }
            cout << "Distancia (km): "; cin >> dist;
            g.agregarConexion(a, b, dist);
            cout << "Conexion agregada correctamente\n";
            break;
        }
        }

    } while (op != 0);

    return 0;
}