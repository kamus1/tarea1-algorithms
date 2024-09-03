#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

int partition(vector<int>& vec, int low, int high) {
    int pivot = vec[high]; //ultimo elemento escogido como pivot
    int i = low - 1; // i mantiene la posicion del ultimo elemento menor que el pivot
    // i inicialmente apunta antes del primer elemento del vector 

    //recorrer desde low hasta hight-1 para completar el pivot
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec[i], vec[j]); //colocar el elemento menor al pivote 
        }
    }
    //colocar al pivote en su posición correcta y se devuelve su index
    swap(vec[i + 1], vec[high]);  
    return i + 1;
}

void quickSort(vector<int>& vec, int low, int high) {
  
    if (low < high) {
      
        //se obtiene el índice del pivote después de particionar el vec
        int pivot_index = partition(vec, low, high);

        //ordenar recursivamente los sub vectores menores y mayores
        quickSort(vec, low, pivot_index - 1);
        quickSort(vec, pivot_index + 1, high);
    }
}


int main(){
    vector<string> nombres_archivos = {
        "datasets/random_dataset.txt",
        "datasets/partially_sorted_dataset.txt",
        "datasets/semisorted_dataset.txt",
        "datasets/unique_random_dataset.txt",
    };

    cout << "Quick Sort" << endl;
    for( string nombreArchivo : nombres_archivos){
        ifstream archivo(nombreArchivo.c_str());

        vector<int> listado;
        string num;
        //leer y guardar numeros del .txt
        while (getline(archivo, num, ' ')) {
            if (!num.empty()) listado.push_back(stoi(num));
        }

        int n = listado.size();
        auto start = chrono::high_resolution_clock::now();
        quickSort(listado, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        cout << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;
        
        //for (int e: listado){cout << e << ' ';} cout << endl;
    }
    return 0;
}