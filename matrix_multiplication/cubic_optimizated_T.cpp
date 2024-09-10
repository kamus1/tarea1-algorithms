#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>


using namespace std;

//esta funcion lee los datos del archivo .txt de las m atrices generaras
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
        
        matriz.push_back(fila);// linea es una fila
    }

    file.close();
    return matriz;
}

//funcion para la multiplicacion de matrices
vector<vector<int>> multiplicar_matrices_optimizado(
    const vector<vector<int>>& aMatrix,
    const vector<vector<int>>& bMatrix,
    int filas_A, 
    int columnas_A,
    int columnas_B //considerar las columnas de B (caso cuando las matrices no son de iguales tamaños)
    ) {


    //transponer la segunda matriz antes, considerando dimentsiones de columnas_a y columnas de b
    vector<vector<int>> bMatrix_T(columnas_B, vector<int>(columnas_A));
    for (int i = 0; i < columnas_A; ++i) {
        for (int j = 0; j < columnas_B; ++j) {
            bMatrix_T[j][i] = bMatrix[i][j];
        }
    }

    //la matriz de producto con dimensiones n x m
    //[fila_a][columna_a] * [fila_b][columna_b] --> resultante de la multiplicacion es [fila_a][columna_b]
    vector<vector<int>> producto(filas_A, vector<int>(columnas_B, 0)); //inicializar con ceros con tamaño de la columna b

    for (int row = 0; row < filas_A; ++row) {
        for (int col = 0; col < columnas_B; ++col) {
            for (int valor = 0; valor < columnas_A; ++valor) {
                producto[row][col] += aMatrix[row][valor] * bMatrix_T[col][valor]; // solo este ultimo cambia, en el normal es [valor][col]
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



void exportar_matriz(const vector<vector<int>>& matriz, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para exportar la matriz." << endl;
        return;
    }

    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo.close();
}

int main() {
    //leer los archivos de las matrices
    vector<vector<int>> matriz_1 = leer_matriz("datasets/matriz_1.txt");
    vector<vector<int>> matriz_2 = leer_matriz("datasets/matriz_2.txt");

    int filas_A = matriz_1.size();
    int columnas_A = matriz_1[0].size();
    int filas_B = matriz_2.size();
    int columnas_B = matriz_2[0].size();

    if (columnas_A != filas_B) {
        cerr << "Las dimensiones no compatibles para multiplicación." << endl;
        return 1;
    }



    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> producto = multiplicar_matrices_optimizado(matriz_1, matriz_2,filas_A, columnas_A, columnas_B);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " ms" << endl;


    //Print
    //cout << "Matriz 1" << endl;
    //imprimir_matriz(matriz_1);
    //cout << endl;

    //cout << "Matriz 2" << endl;
    //imprimir_matriz(matriz_2);
    //cout << endl;

    //cout << "Producto" << endl;
    //imprimir_matriz(producto);

    // Exportar la matriz resultante a un archivo .txt
    exportar_matriz(producto, "res_cubic_op_T.txt");
    return 0;
}
