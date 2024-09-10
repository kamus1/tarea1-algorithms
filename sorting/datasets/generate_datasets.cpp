#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>
#include <random> //para std::shuffle

using namespace std;

//---------------------- PARÁMETROS ----------------------#
int nums = 10; //cantidad de los numeros a generar
int nums_size = 600000; //maximo tamaño de cada numero generado 
//!!importante nums_size >nums, debido a la funcion que genera numeros unicos
//de lo contrario solo generará un numero 0
//--------------------------------------------------------#



//funcion para generar el dataset de numeros random
vector<int> gen_random_dataset(int size) {
    vector<int> data(size);
    for (int &val : data) {
        val = rand() % nums_size;
    }
    return data;
}

// esta funcion ordena la mitad de los numeros de otro dataset que genera con gen_random_dataset
vector<int> gen_semisorted_dataset(int size) {
    vector<int> data = gen_random_dataset(size);
    sort(data.begin(), data.begin() + size / 2); //ordenar la primera mitad del inicio
    return data;
}

//funcion para generar un dataset de numeros random y ordenarlos
vector<int> gen_sorted_random_dataset(int size) {
    vector<int> data = gen_random_dataset(size);
    sort(data.begin(), data.end()); //ordenar el dataset completamente
    return data;
}


//ordena un porcentaje de los numeros al centro del vector
vector<int> gen_partially_sorted_dataset(int size, float percentage) {
    vector<int> data = gen_random_dataset(size);
    int mid = size / 2;
    
    //se calcula el porcentaje de numeros a ordenar
    int range_size = static_cast<int>(size * percentage / 100);
    
    //para que el rango de ordenación no se extienda fuera del vector
    int start_index = max(0, mid - range_size / 2);
    int end_index = min(size, mid + range_size / 2);
    
    //que end_index sea mayor que start_index
    if (end_index > start_index) {
        sort(data.begin() + start_index, data.begin() + end_index);
    }
    
    return data;
}


//esta funcion genera un dataset de numeros unicos usando un set; donde no se pueden repetir los nums
vector<int> gen_unique_random_dataset(int size) {

    if(nums > nums_size){
        cout << "ERROR: nums debe ser mayor que nums_size para generar numeros unicos" << endl;
        vector<int> error = {0};
        return error;
    }
    set<int> unique_numbers;
    vector<int> data;

    while (unique_numbers.size() < size) {
        unique_numbers.insert(rand() % nums_size);
    }

    data.assign(unique_numbers.begin(), unique_numbers.end());

    //desordenar el vector para que los números sean únicos pero no estén ordenados
    //ya que el set los almacena ordenadamente
    random_device rd;
    mt19937 g(rd());
    shuffle(data.begin(), data.end(), g);

    return data;
}

//funcion que solo crea los archivos .txt de los datasets
void dataset_to_file(const vector<int>& dataset, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int val : dataset) {
            file << val << " "; 
        }
        file.close();
    } else {
        cerr << "Error al crear el archivo: " << filename << endl;
    }
}

int main() {
    srand(time(0)); // inicializar el random con el tiempo

    //crear los vectores con lso numeros "aleatorios"
    vector<int> dataset_random = gen_random_dataset(nums);
    vector<int> dataset_semi_sorted = gen_semisorted_dataset(nums); //50% (la mitad) ordenado desde el inicio
    vector<int> dataset_sorted_random = gen_sorted_random_dataset(nums); // dataset completamente ordenado

    float percentage = 70.0; //porcentaje de elementos a ordenar
    vector<int> dataset_partially_sorted = gen_partially_sorted_dataset(nums, percentage); // 70% de n ordenado al medio
    vector<int> dataset_unique_random = gen_unique_random_dataset(nums);

    //crear los .txt de los dataset
    dataset_to_file(dataset_sorted_random, "sorted_random_dataset.txt");
    dataset_to_file(dataset_random, "random_dataset.txt");
    dataset_to_file(dataset_semi_sorted, "semisorted_dataset.txt");
    dataset_to_file(dataset_partially_sorted, "partially_sorted_dataset.txt");
    dataset_to_file(dataset_unique_random, "unique_random_dataset.txt");

    cout << "Datasets creados correctamente" << "\n";

    return 0;
}
