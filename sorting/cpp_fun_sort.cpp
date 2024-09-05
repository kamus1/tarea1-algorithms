#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

int main(){
    //nombres de los archivos con los datos a ordenar
    vector<string> nombres_archivos = {
        "datasets/random_dataset.txt",
        "datasets/partially_sorted_dataset.txt",
        "datasets/semisorted_dataset.txt",
        "datasets/unique_random_dataset.txt",
        "datasets/sorted_random_dataset.txt"
    };

    //archivo para escribir los resultados
    ofstream archivo_salida("s_cpp_fun_sort.txt");
    if (!archivo_salida) {
        cerr << "Error al abrir el archivo s_cpp_fun_sort.txt para escritura." << endl;
        return 1;
    }

    cout << "C++ Sort Function" << endl;
    for( string nombreArchivo : nombres_archivos){
        ifstream archivo(nombreArchivo.c_str());
        if (!archivo) {cerr << "Error al abrir el archivo " << nombreArchivo << endl; continue; }

        vector<int> listado;
        string num;
        //leer y guardar numeros del .txt
        while (getline(archivo, num, ' ')) {
            if (!num.empty()) listado.push_back(stoi(num));
        }


        auto start = chrono::high_resolution_clock::now();
        sort(listado.begin(), listado.end());
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> elapsed = end - start;
            cout << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;

        // escribir los valores ordenados en el archivo s_cpp_fun_sort.txt
        archivo_salida << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;
        for (const int& e : listado) {
            archivo_salida << e << ' ';
        }
        archivo_salida << endl << endl;

    }

    archivo_salida.close();
    return 0;
}