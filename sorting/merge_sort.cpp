#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

void merge(vector<int>& vec, int left, int mid, int right){
    int n1 = mid - left + 1; // tamaño primera mitad
    int n2 = right - mid;    // tamaño segunda mitad

    //vectores temporales para guardar las mitades
    vector<int> leftVec(n1);
    vector<int> rightVec(n2);

    //copiar los datos a los vectores temporales
    for (int i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    //idices para recorrer los vectores temporales y el vector original
    int index_1 = 0, index_2 = 0, k = left; // k is initial index of merged array
    //k es el index inicial del array a la izquierda, por lo tanto es el index minimo del array completo a mergear


    // hacer el merge de los vectores, combinarlos de vuelta en el vector original
    while (index_1 < n1 && index_2 < n2) {
    //va comparando los valores de los 2 vectores al mismo tiempo y el menor de los 2 valores lo cambia en el vec original
    //y aumenta el index del vecotor correspondiente, de cualquier forma aumenta la posicion k que es donde va colocando los valores de los vec comparados
        if (leftVec[index_1] <= rightVec[index_2]) {
            vec[k] = leftVec[index_1];
            index_1++;
        } else {
            vec[k] = rightVec[index_2];
            index_2++;
        }
        k++;
    }

    //solo hace uno de los dos while siguientes
    //agregar el resto de leftVec (si es que queda algún elemento)
    while (index_1 < n1) {
        vec[k] = leftVec[index_1];
        index_1++;
        k++;
    }

    //agregar el resto de rightVec (si es que queda algún elemento)
    while (index_2 < n2) {
        vec[k] = rightVec[index_2];
        index_2++;
        k++;
    }

}

void merge_sort(vector<int>& lista_nums, int begin, int end) {
    if (begin >= end)
        return; 

    int mid = begin + (end - begin) / 2;

    //ordenar la primera y segunda mitad
    merge_sort(lista_nums, begin, mid);
    merge_sort(lista_nums, mid + 1, end);

    // combinar las mitades ordenadas
    merge(lista_nums, begin, mid, end);
    
}

//----------------------------------------------------------------------------------------//


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
        
        int n = listado.size();
        auto start = chrono::high_resolution_clock::now();
        merge_sort(listado, 0, n -1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        cout << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;

        //for (int e: listado){cout << e << ' ';}cout << endl;
    }
    return 0;
}