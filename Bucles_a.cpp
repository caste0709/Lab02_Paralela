#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

double primer_p_bucles(const vector<vector<double>>& matriz, const vector<double>& vec, vector<double>& res, long long& iteraciones){
    size_t MAX = matriz.size();

    for (size_t i = 0; i < MAX; ++i) {
        res[i] = 0.0;
    }

    auto start = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < MAX; i++) {
        for (size_t j = 0; j < MAX; j++) {
            res[i] += matriz[i][j] * vec[j];
            iteraciones++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

double segundo_p_bucles(const vector<vector<double>>& matriz, const vector<double>& vec, vector<double>& res, long long& iteraciones){
    size_t MAX = matriz.size();

    for (size_t i = 0; i < MAX; ++i) {
        res[i] = 0.0;
    }

    auto start = chrono::high_resolution_clock::now();

    for (size_t j = 0; j < MAX; j++) {
        for (size_t i = 0; i < MAX; i++) {
            res[i] += matriz[i][j] * vec[j];
            iteraciones++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

int main(){

    size_t MAX [5] = {100, 500, 1000, 2000, 4000};

    mt19937 gen(42);
    uniform_real_distribution<double> dist(0.0, 10.0);


    for(int m = 0; m < 5; m++){
        vector<vector<double>> matriz(MAX[m], vector<double>(MAX[m]));
        vector<double> vec(MAX[m]), res1(MAX[m]), res2(MAX[m]);        

        for (size_t i = 0; i < MAX[m]; ++i) {
            for (size_t j = 0; j < MAX[m]; ++j) {
                matriz[i][j] = dist(gen);
            }
        }

        for(size_t i = 0; i < MAX[m]; i++){
            vec[i] = dist(gen);
        }

        long long iter1 = 0, iter2 = 0;
        double t_primer_par = primer_p_bucles(matriz, vec, res1, iter1);
        double t_segundo_par = segundo_p_bucles(matriz, vec, res2, iter2);

        double diff_max = 0.0;
        for (size_t i = 0; i < MAX[m]; i++) {
            diff_max = max(diff_max, abs(res1[i] - res2[i]));
        }


        cout << "MAX = " << MAX[m] << endl;
        cout << "Iteraciones primer par:  " << iter1 << endl;
        cout << "Iteraciones segundo par: " << iter2 << endl;
        cout << "Tiempo de ejecucion primer par: " << t_primer_par << endl;
        cout << "Tiempo de ejecucion segundo par: " << t_segundo_par << endl;
        cout << "Diferencia maxima entre resultados: " << diff_max << endl;
    }   

    return 0;
}