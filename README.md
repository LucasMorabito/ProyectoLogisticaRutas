# 🚚 Proyecto Logística con Grafos (C++)

Este proyecto implementa un sistema básico de logística utilizando grafos y el algoritmo de Dijkstra para calcular rutas mínimas entre ciudades.

## 🧠 Algoritmo utilizado

Se implementa el algoritmo de Dijkstra para encontrar el camino más corto entre dos ciudades dentro del grafo.

## 🏙️ Ciudades incluidas
* Corrientes
* Goya
* Libres
* Mercedes

## ⚙️ Funcionalidades del sistema
* Ver ciudades disponibles
* Mostrar matriz de conexiones
* Calcular ruta mínima
* Cortar una ruta (simulación de bloqueo)
* Guardar grafo en archivo
* Cargar grafo desde archivo

## 💾 Archivos generados
* `C:\grafo.txt` → guarda el estado del grafo
* `C:\historial.txt` → guarda las rutas calculadas

## ▶️ Cómo ejecutar

**Compilar:**
```bash
g++ main.cpp -o programa