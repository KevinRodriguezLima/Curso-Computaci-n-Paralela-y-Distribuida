#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define TAM 9000
#define REPETICIONES 16 //vamos a probar varias veces para sacar un promedio

int main() {
    static double matriz[TAM][TAM];
    static double vector[TAM];
    static double resultado[TAM];

    // Inicializamos
    for (int fila = 0; fila < TAM; fila++) {
        vector[fila] = 1.0;
        resultado[fila] = 0.0;
        for (int columna = 0; columna < TAM; columna++) {
            matriz[fila][columna] = (fila + columna) % 10;
        }
    }

    long long acumulado1 = 0;
    long long acumulado2 = 0;

    for (int rep = 0; rep < REPETICIONES; rep++) {
        for (int fila = 0; fila < TAM; fila++) {
            resultado[fila] = 0.0;
        }

        //recorriendo por filas
        auto inicio1 = steady_clock::now();

        for (int fila = 0; fila < TAM; fila++) {
            for (int columna = 0; columna < TAM; columna++) {
                resultado[fila] += matriz[fila][columna] * vector[columna];
            }
        }

        auto fin1 = steady_clock::now();
        long long tiempo1 = duration_cast<milliseconds>(fin1 - inicio1).count();
        acumulado1 += tiempo1;

        for (int fila = 0; fila < TAM; fila++) {
            resultado[fila] = 0.0;
        }

        // recorriendo por columnas
        auto inicio2 = steady_clock::now();

        for (int columna = 0; columna < TAM; columna++) {
            for (int fila = 0; fila < TAM; fila++) {
                resultado[fila] += matriz[fila][columna] * vector[columna];
            }
        }

        auto fin2 = steady_clock::now();
        long long tiempo2 = duration_cast<milliseconds>(fin2 - inicio2).count();
        acumulado2 += tiempo2;

        cout << "Repetición " << rep+1
             << " : fila primero: " << tiempo1 << " ms, "
             << "columna primero: " << tiempo2 << " ms" << endl;
    }

    cout << "\nPromedio fila primero = " << acumulado1 / REPETICIONES << " ms" << endl;
    cout << "Promedio columna primero = " << acumulado2 / REPETICIONES << " ms" << endl;

    return 0;
}
