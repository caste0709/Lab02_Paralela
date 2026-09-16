# Lab02_Paralela

Laboratorio sobre localidad de caché y jerarquía de memoria, curso de Computación Paralela y Distribuida (UNSA). Se estudia cómo el patrón de acceso a memoria afecta el rendimiento real de un programa, aunque la complejidad algorítmica sea la misma, usando como ejemplos bucles anidados y multiplicación de matrices (clásica vs. por bloques).

## Contenido del repositorio

| Archivo | Qué contiene |
|---|---|
| `Bucles_a.cpp` | Ejercicio 1: compara dos formas de recorrer una matriz con bucles anidados (orden por filas vs. por columnas), midiendo tiempos para distintos tamaños. |
| `Mult_mat.cpp` | Ejercicio 2: implementación de la multiplicación clásica de matrices (tres bucles anidados), con medición de tiempos para distintos tamaños de matriz. |
| `Mult_por_bloq.cpp` | Ejercicio 3: implementación de la multiplicación por bloques (seis bucles anidados) junto con la clásica, comparando ambas para distintos tamaños de matriz y de bloque. |
| `multiplicacion.cpp` | Versión aislada de la multiplicación clásica, usada para analizarla individualmente con Valgrind/Cachegrind en el ejercicio 5. |
| `bloques.cpp` | Versión aislada de la multiplicación por bloques, usada para analizarla individualmente con Valgrind/Cachegrind en el ejercicio 5. |

## Requisitos

- Compilador **g++** con soporte para C++17.
-  **Valgrind** con la herramienta **Cachegrind**, y **KCachegrind** para visualizar los resultados:
  ```bash
  sudo apt update
  sudo apt install valgrind kcachegrind g++
  ```

## Compilación y ejecución

Todos los archivos son independientes entre sí: cada uno se compila y se ejecuta por separado con el mismo patrón.

**Compilación normal (mediciones de tiempo con `chrono`):**
```bash
g++ -O2 -std=c++17 Bucles_a.cpp -o bucles
./bucles

g++ -O2 -std=c++17 Mult_mat.cpp -o mult_clasica
./mult_clasica

g++ -O2 -std=c++17 Mult_por_bloq.cpp -o mult_bloques
./mult_bloques
```
Cada programa imprime en consola los tiempos de ejecución para los distintos tamaños de entrada (y, en el caso de `Mult_por_bloq.cpp`, para distintos tamaños de bloque) ya definidos dentro del código.

**Compilación para análisis con Valgrind/Cachegrind:**
```bash
g++ -O0 -g -std=c++17 multiplicacion.cpp -o mcl
g++ -O0 -g -std=c++17 bloques.cpp -o bl
```
Se usa `-O0 -g` para que el análisis refleje el algoritmo tal cual está escrito y para que Cachegrind pueda mostrar el costo línea por línea del código fuente.

## Instrucciones para el análisis con Valgrind y KCachegrind (ejercicio 5)

```bash
valgrind --tool=cachegrind --cache-sim=yes --branch-sim=no --cachegrind-out-file=mcl.out ./mcl
valgrind --tool=cachegrind --cache-sim=yes --branch-sim=no --cachegrind-out-file=bl.out  ./bl
```

Al terminar, la terminal imprime un resumen con instrucciones ejecutadas, accesos a memoria y fallos de caché (L1 y de último nivel). Para explorar los resultados por función y por línea de código:

```bash
kcachegrind mcl.out
kcachegrind bl.out
```

Dentro de KCachegrind: escribir el nombre de la función (`mult_mat` o `mult_por_bloqs`) en el campo "Buscar", seleccionarla, y abrir la pestaña "Código fuente" para ver el costo asociado a cada línea.
