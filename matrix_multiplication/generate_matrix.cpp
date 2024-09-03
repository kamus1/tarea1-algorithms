#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>  
#include <fstream>
#include <filesystem> //std::filesystem

using namespace std;
namespace fs = std::filesystem;

//funcion que genera una matriz de números random
vector<vector<int>> generar_matriz(int filas, int columnas, int rango_min, int rango_max) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    
    //rellenar la matriz con los numeros random
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = rand() % (rango_max - rango_min + 1) + rango_min;
        }
    }

    return matriz;
}

//función para guardar la matriz en un archivo
void guardar_matriz_en_archivo(const vector<vector<int>>& matriz, const string& nombre_archivo) {
    fs::path dir = "datasets";
    if (!fs::exists(dir)) {
        fs::create_directory(dir); //crear la carpeta si no existe
    }

    fs::path filepath = dir / nombre_archivo;
    ofstream archivo(filepath);
    if (archivo.is_open()) {
        for (const auto& fila : matriz) {
            for (int valor : fila) {
                archivo << valor << " ";
            }
            archivo << "\n";
        }
        archivo.close();
    } else {
        cerr << "Error al crear el archivo: " << filepath << endl;
    }
}

int main() {
    srand(time(0));

    //parámetros de la matriz
    int filas = 400;
    int columnas = 400;
    int rango_min = 1;
    int rango_max = 1000;
    string nombre_archivo_1 = "matriz_1.txt";
    string nombre_archivo_2 = "matriz_2.txt";

    //gen matriz 1
    auto matriz = generar_matriz(filas, columnas, rango_min, rango_max);
    guardar_matriz_en_archivo(matriz, nombre_archivo_1);

    //gen matriz 2
    auto matriz_2 = generar_matriz(filas, columnas, rango_min, rango_max);
    guardar_matriz_en_archivo(matriz_2, nombre_archivo_2);

    
    return 0;
}
