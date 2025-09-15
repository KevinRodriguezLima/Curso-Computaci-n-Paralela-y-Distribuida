#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void clasica(const vector<vector<double>>& A,
             const vector<vector<double>>& B,
             vector<vector<double>>& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double s = 0.0;
            for (int k = 0; k < N; ++k) s += A[i][k] * B[k][j];
            C[i][j] = s;
        }
    }
}

void bloques(const vector<vector<double>>& A,
             const vector<vector<double>>& B,
             vector<vector<double>>& C, int N, int BS) {
    for (int ii = 0; ii < N; ii += BS)
        for (int jj = 0; jj < N; jj += BS)
            for (int kk = 0; kk < N; kk += BS)
                for (int i = ii; i < min(ii + BS, N); ++i)
                    for (int j = jj; j < min(jj + BS, N); ++j) {
                        double s = C[i][j];
                        for (int k = kk; k < min(kk + BS, N); ++k)
                            s += A[i][k] * B[k][j];
                        C[i][j] = s;
                    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Uso: ./mm <clasica|bloques> <N> [BS]\n";
        return 1;
    }
    string modo = argv[1];
    int N = stoi(argv[2]);
    int BS = (argc >= 4 ? stoi(argv[3]) : 64);

    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i + j) % 10;
            B[i][j] = (i - j) % 10;
        }

    auto t0 = steady_clock::now();
    if (modo == "clasica") {
        clasica(A, B, C, N);
    } else if (modo == "bloques") {
        bloques(A, B, C, N, BS);
    } else {
        cerr << "Multiplicacion: " << modo << "\n";
        return 2;
    }
    auto t1 = steady_clock::now();
    cout << "Multiplicacion " << modo << " N=" << N << " (BS =" << BS
         << ") tiempo =" << duration_cast<milliseconds>(t1 - t0).count()
         << " ms\n";
    return 0;
}
