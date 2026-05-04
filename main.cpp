#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int INF = 999999;

// ================= CIUDAD =================
class Ciudad {
public:
    int id;
    string nombre;
    int x, y;

    Ciudad(int id = 0, string nombre = "", int x = 0, int y = 0) {
        this->id = id;
        this->nombre = nombre;
        this->x = x;
        this->y = y;
    }
};

// ================= GRAFO =================
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
        for (int i = 0; i < n; i++)
            matriz[i][i] = 0;
    }

    void agregarCiudad(Ciudad c) {
        ciudades.push_back(c);
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
        for (int i = 0; i < ciudades.size(); i++) {
            cout << i << " - " << ciudades[i].nombre << endl;
        }
    }

    void mostrarMatriz() {
        cout << "\n--- MATRIZ ---\n";
        for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz.size(); j++) {
                if (matriz[i][j] == INF)
                    cout << "INF ";
                else
                    cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }

    // ===== GUARDAR (ARREGLADO) =====
    void guardarArchivo() {
        ofstream f("C:\\grafo.txt");

        if (!f) {
            cout << "ERROR: No se pudo crear el archivo\n";
            return;
        }

        int n = ciudades.size();
        f << n << endl;

        for (auto &c : ciudades) {
            f << c.id << " " << c.nombre << " " << c.x << " " << c.y << endl;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                f << matriz[i][j] << " ";
            }
            f << endl;
        }

        f.close();
        cout << "Archivo guardado en C:\\grafo.txt\n";
    }

    // ===== CARGAR (ARREGLADO) =====
    void cargarArchivo() {
        ifstream f("C:\\grafo.txt");

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

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f >> matriz[i][j];

        f.close();
        cout << "Archivo cargado correctamente\n";
    }

    // ===== DIJKSTRA =====
    void dijkstra(int origen, int destino) {
        int n = matriz.size();

        vector<int> dist(n, INF);
        vector<bool> visitado(n, false);
        vector<int> previo(n, -1);

        dist[origen] = 0;

        for (int i = 0; i < n - 1; i++) {
            int min = INF, u = -1;

            for (int j = 0; j < n; j++) {
                if (!visitado[j] && dist[j] <= min) {
                    min = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;

            visitado[u] = true;

            for (int v = 0; v < n; v++) {
                if (!visitado[v] &&
                    matriz[u][v] != INF &&
                    dist[u] + matriz[u][v] < dist[v]) {

                    dist[v] = dist[u] + matriz[u][v];
                    previo[v] = u;
                }
            }
        }

        if (dist[destino] == INF) {
            cout << "No hay ruta disponible\n";
            return;
        }

        cout << "\nDistancia minima: " << dist[destino] << " km\n";

        vector<int> camino;
        for (int v = destino; v != -1; v = previo[v])
            camino.push_back(v);

        cout << "Camino: ";
        for (int i = camino.size() - 1; i >= 0; i--) {
            cout << ciudades[camino[i]].nombre;
            if (i != 0) cout << " -> ";
        }
        cout << endl;

        ofstream hist("C:\\historial.txt", ios::app);
        hist << "Ruta: ";
        for (int i = camino.size() - 1; i >= 0; i--) {
            hist << ciudades[camino[i]].nombre;
            if (i != 0) hist << " -> ";
        }
        hist << " | Distancia: " << dist[destino] << " km\n";
        hist.close();
    }
};

// ================= MAIN =================
int main() {

    Grafo g(4);

    // CIUDADES
    g.agregarCiudad(Ciudad(0, "Corrientes", 10, 10));
    g.agregarCiudad(Ciudad(1, "Goya", 50, 60));
    g.agregarCiudad(Ciudad(2, "Libres", 80, 20));
    g.agregarCiudad(Ciudad(3, "Mercedes", 40, 30));

    // CONEXIONES
    g.agregarConexion(0, 1, 220);
    g.agregarConexion(0, 2, 350);
    g.agregarConexion(0, 3, 250);
    g.agregarConexion(1, 2, 300);
    g.agregarConexion(1, 3, 120);
    g.agregarConexion(2, 3, 200);

    int op;

    do {
        cout << "\n====== SISTEMA LOGISTICO ======\n";
        cout << "1. Ver ciudades\n";
        cout << "2. Ver matriz\n";
        cout << "3. Calcular ruta\n";
        cout << "4. Cortar ruta\n";
        cout << "5. Guardar\n";
        cout << "6. Cargar\n";
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

            cout << "Origen: ";
            cin >> o;
            cout << "Destino: ";
            cin >> d;

            if (o < 0 || d < 0 || o >= 4 || d >= 4) {
                cout << "Error de indices\n";
                break;
            }

            g.dijkstra(o, d);
            break;
        }

        case 4: {
            int a, b;
            g.mostrarCiudades();

            cout << "Ingrese dos ciudades (ej: 0 2): ";
            cin >> a >> b;

            if (a < 0 || b < 0 || a >= 4 || b >= 4) {
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

        }

    } while (op != 0);

    return 0;
}