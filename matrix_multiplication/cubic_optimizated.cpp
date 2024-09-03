#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>


using namespace std;

//esta funcion lee los datos del archivo .txt de las matrices generaras
vector<vector<int>> leer_matriz(const string& archivoEntrada) {
    ifstream file(archivoEntrada);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1); //terminar si no se pude encontrar el archivo
    }

    vector<vector<int>> matriz;
    string linea;
    
    while (getline(file, linea)) { //leer por linea
        istringstream iss(linea);
        vector<int> fila;
        int numero;
        
        while (iss >> numero) {
            fila.push_back(numero);
        }
        
        matriz.push_back(fila);
    }

    file.close();
    return matriz;
}

//funcion para la multiplicacion de matrices
vector<vector<int>> multiplicar_matrices_optimizado(
    const vector<vector<int>>& aMatrix,
    const vector<vector<int>>& bMatrix,
    int filas_A, 
    int columnas_A
    ) {

    //transponer la segunda matriz
    vector<vector<int>> bMatrix_T(columnas_A, vector<int>(filas_A));
    for (int i = 0; i < filas_A; ++i) {
        for (int j = 0; j < columnas_A; ++j) {
            bMatrix_T[j][i] = bMatrix[i][j];
        }
    }

    vector<vector<int>> producto(filas_A, vector<int>(columnas_A, 0));

    for (int row = 0; row < filas_A; ++row) {
        for (int col = 0; col < columnas_A; ++col) {
            for (int inner = 0; inner < columnas_A; ++inner) {
                producto[row][col] += aMatrix[row][inner] * bMatrix_T[col][inner];
            }
        }
    }

    return producto;
}
//para ahorarse sl codigo del print de la matriz
void imprimir_matriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int numero : fila) {
            cout << numero << " ";
        }
        cout << endl;
    }
}

int main() {
    //leer los archivos de las matrices
    vector<vector<int>> matriz_1 = leer_matriz("datasets/matriz_1.txt");
    vector<vector<int>> matriz_2 = leer_matriz("datasets/matriz_2.txt");

    int filas_A = matriz_1.size();
    int columnas_A = matriz_1[0].size();
    //int columnas_B = matriz_2[0].size();


    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> producto = multiplicar_matrices_optimizado(matriz_1, matriz_2,filas_A, columnas_A);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " ms" << endl;


    //Print
    cout << "Matriz 1" << endl;
    //imprimir_matriz(matriz_1);
    cout << endl;

    cout << "Matriz 2" << endl;
    //imprimir_matriz(matriz_2);
    cout << endl;

    cout << "Producto" << endl;
    //imprimir_matriz(producto);

    return 0;
}
