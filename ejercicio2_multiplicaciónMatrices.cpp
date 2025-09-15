#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

// multiplicacion  con 3 bucles
void multiplicacionClasica(const vector<vector<double>>& A, const vector<vector<double>>& B,
                           vector<vector<double>>& C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int tamanios[] = {250, 500, 1000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);

    for (int t = 0; t < num_tamanios; t++) {
        int N = tamanios[t];
        vector<vector<double>> A(N, vector<double>(N));
        vector<vector<double>> B(N, vector<double>(N));
        vector<vector<double>> C(N, vector<double>(N));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (i + j) % 10;
                B[i][j] = (i - j) % 10; //modulo para tener numeros pequenios
            }
        }

        auto inicio = steady_clock::now();
        multiplicacionClasica(A, B, C, N);
        auto fin = steady_clock::now();

        long long tiempo = duration_cast<milliseconds>(fin - inicio).count();
        cout << "Tiempo con  N :" << N
             << " : " << tiempo << " ms" << endl;
    }

    return 0;
}
