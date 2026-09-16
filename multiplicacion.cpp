#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

double mult_mat(const vector<vector<double>>& matriz_1, const vector<vector<double>>& matriz_2, vector<vector<double>>& res, int N) {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            res[i][j] = 0.0;
        }
    }
        
 
    auto start = chrono::high_resolution_clock::now();
 
    for (int i = 0; i < N; i++) {          
        for (int j = 0; j < N; j++) {      
            double suma = 0.0;
            for (int k = 0; k < N; k++) {  
                suma += matriz_1[i][k] * matriz_2[k][j];
            }
            res[i][j] = suma;
        }
    }
 
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

int main(){
    size_t MAX = 500;

    mt19937 gen(42);
    uniform_real_distribution<double> dist(0.0, 10.0);


    vector<vector<double>> matriz_1(MAX, vector<double>(MAX));
    vector<vector<double>> matriz_2(MAX, vector<double>(MAX));
    vector<vector<double>> resultado(MAX, vector<double>(MAX));

    for (size_t i = 0; i < MAX; ++i) {
        for (size_t j = 0; j < MAX; ++j) {
            matriz_1[i][j] = dist(gen);
            matriz_2[i][j] = dist(gen);
        }
    }

    double t_mult = mult_mat(matriz_1, matriz_2, resultado, MAX);
    cout << "MAX: " << MAX << endl;
    cout << "Duracion " << t_mult << endl;


    return 0;
}
