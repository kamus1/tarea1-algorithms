#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

void bubbleSort(vector<int>& v) {
    int n = v.size();

    //bucle externeo que corresponde al número de elementos a ordenar
    for (int i = 0; i < n - 1; i++) {
        //los ultimos i elementos ya están en su lugar
        for (int j = 0; j < n - i - 1; j++) {
          
            //se comparan los elementos adyacentes
            if (v[j] > v[j + 1])
                  //se hae un swap si es que estaban en el orden incorrecto
                swap(v[j], v[j + 1]);
        }
    }
}


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
    ofstream archivo_salida("s_bubble_sort.txt");
    if (!archivo_salida) {
        cerr << "Error al abrir el archivo s_bubble_sort.txt para escritura." << endl;
        return 1;
    }


    cout << "Bubble Sort" << endl;
    for( string nombreArchivo : nombres_archivos){
        ifstream archivo(nombreArchivo.c_str());
        if (!archivo) {cerr << "Error al abrir el archivo " << nombreArchivo << endl; continue; }


        vector<int> listado;
        string num;
        //leer y guardar numeros del .txt
        while (getline(archivo, num, ' ')) {
            if (!num.empty()) listado.push_back(stoi(num));
        }


        //mediciones del tiempo
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(listado);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> elapsed = end - start;
        cout << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;



        // exportar los valores ordenados en el archivo s_bubble_sort.txt
        archivo_salida << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;
        for (const int& e : listado) {
            archivo_salida << e << ' ';
        }
        archivo_salida << endl << endl;

    }

    archivo_salida.close();
    return 0;
}