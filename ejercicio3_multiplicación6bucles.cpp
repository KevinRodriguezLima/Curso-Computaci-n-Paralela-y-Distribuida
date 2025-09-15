#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// Multiplicacion clasica
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

// Multiplicacion por bloques
void multiplicacionBloques(const vector<vector<double>>& A, const vector<vector<double>>& B,
                           vector<vector<double>>& C, int N, int tamBS) {
    for (int ii = 0; ii < N; ii += tamBS) {
        for (int jj = 0; jj < N; jj += tamBS) {
            for (int kk = 0; kk < N; kk += tamBS) {
                for (int i = ii; i < min(ii + tamBS, N); i++) {
                    for (int j = jj; j < min(jj + tamBS, N); j++) {
                        for (int k = kk; k < min(kk + tamBS, N); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int tamanios[] = {500, 1000, 2000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);
    int tamBS = 64; // tamaño del bloque

    for (int t = 0; t < num_tamanios; t++) {
        int N = tamanios[t];
        cout << "\nProbando con N = " << N << endl;
        vector<vector<double>> A(N, vector<double>(N));
        vector<vector<double>> B(N, vector<double>(N));
        vector<vector<double>> C(N, vector<double>(N, 0.0));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (i + j) % 10;
                B[i][j] = (i - j) % 10;
            }
        }

        //Mul clasica
        fill(C.begin(), C.end(), vector<double>(N, 0.0));
        auto inicio1 = steady_clock::now();
        multiplicacionClasica(A, B, C, N);
        auto fin1 = steady_clock::now();
        long long tiempoClasica = duration_cast<milliseconds>(fin1 - inicio1).count();

        //Por bloques
        fill(C.begin(), C.end(), vector<double>(N, 0.0));
        auto inicio2 = steady_clock::now();
        multiplicacionBloques(A, B, C, N, tamBS);
        auto fin2 = steady_clock::now();
        long long tiempoBloques = duration_cast<milliseconds>(fin2 - inicio2).count();

        cout << "Tiempo clasica: " << tiempoClasica << " ms" << endl;
        cout << "Tiempo bloques: "<< tiempoBloques << " ms" << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}
