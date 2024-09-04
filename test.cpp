#include <bits/stdc++.h>

using namespace std;


int main(){

    //vecotr de filas
    vector<vector<int>> matriz_1 = {{1,2,3},{2,4,6},{9,7,4}};
    vector<vector<int>> matriz_2 = {{1,2,3},{2,4,6},{9,7,4}};

    vector<vector<int>> matriz_3 = {{0,0,0},{0,0,0},{0,0,0}};

    int valor_total = matriz_1[0].size();
    int total_filas = matriz_1.size();
    int total_columnas = matriz_1[0].size();

    for(int fila_1= 0; fila_1 < total_filas; fila_1++){
        for(int columna_2=0; columna_2 < total_columnas; columna_2++){
            for(int valor = 0; valor< valor_total; valor++){
                matriz_3[fila_1][columna_2] += matriz_1[fila_1][valor] * matriz_2[valor][columna_2];
            }
        }
    }

    //print

    for(auto fila : matriz_3){
        for(int num :fila){
            cout << num << " ";
        }
        cout << endl;
    }
        cout << endl;

    return 0;
}