#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

int main(){
    vector<string> nombres_archivos = {
        "datasets/random_dataset.txt",
        "datasets/partially_sorted_dataset.txt",
        "datasets/semisorted_dataset.txt",
        "datasets/unique_random_dataset.txt",
    };

    cout << "Merge Sort" << endl;
    for( string nombreArchivo : nombres_archivos){
        ifstream archivo(nombreArchivo.c_str());

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


        //for (int e: listado){cout << e << ' ';} cout << endl;
    }
    return 0;
}