#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

double mult_por_bloqs(const vector<vector<double>>& matriz_1,  const vector<vector<double>>& matriz_2,  vector<vector<double>>& resultado,
                                 int N, int tam_b) {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            resultado[i][j] = 0.0;
        }            
    }        
 
    auto start = chrono::high_resolution_clock::now();
 
    for (int ii = 0; ii < N; ii += tam_b) {
        for (int jj = 0; jj < N; jj += tam_b) {
            for (int kk = 0; kk < N; kk += tam_b) {
 
                int iMax = min(ii + tam_b, N);
                int jMax = min(jj + tam_b, N);
                int kMax = min(kk + tam_b, N);
 
                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        double suma = resultado[i][j];
                        for (int k = kk; k < kMax; k++) {
                            suma += matriz_1[i][k] * matriz_2[k][j];
                        }
                        resultado[i][j] = suma;
                    }
                }
            }
        }
    }
 
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

int main(){
    size_t MAX [4] = {100, 500, 1000, 2000};
    vector<int> tam_b = {8, 16, 32, 64, 128};

    mt19937 gen(42);
    uniform_real_distribution<double> dist(0.0, 10.0);

     for(int m = 0; m < 4; m++){
        vector<vector<double>> matriz_1(MAX[m], vector<double>(MAX[m]));
        vector<vector<double>> matriz_2(MAX[m], vector<double>(MAX[m]));
        vector<vector<double>> resultado(MAX[m], vector<double>(MAX[m]));

        for (size_t i = 0; i < MAX[m]; ++i) {
            for (size_t j = 0; j < MAX[m]; ++j) {
                matriz_1[i][j] = dist(gen);
                matriz_2[i][j] = dist(gen);
            }
        }

        for(int b = 0; b < tam_b.size(); b++){
            double t_mult = mult_por_bloqs(matriz_1, matriz_2, resultado, MAX[m], tam_b[b]);
            cout << "Tamano: " << MAX[m] << endl;
            cout<< "Numero de bloques " << tam_b[b] << endl;
            cout << "Duracion " << t_mult << endl;
        }       

    }

    return 0;
}
