#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
//muy lento

//--------------------------- Merge Sort -------------------------------------------------//
vector<int> merge(const vector<int>& vec_a, const vector<int>& vec_b) {
    vector<int> vec_c;
    int i = 0, j = 0;

    while (i < vec_a.size() && j < vec_b.size()) {
        if (vec_a[i] <= vec_b[j]) {
            vec_c.push_back(vec_a[i]);
            i++;
        } else {
            vec_c.push_back(vec_b[j]);
            j++;
        }
    }

    //agregar el resto de vec_a (si es que queda algún elemento)
    while (i < vec_a.size()) {
        vec_c.push_back(vec_a[i]);
        i++;
    }

    //agregar el resto de vec_b (si es que queda algún elemento)
    while (j < vec_b.size()) {
        vec_c.push_back(vec_b[j]);
        j++;
    }

    return vec_c;
}

vector<int> merge_sort(vector<int>& lista_nums) {
    int n = lista_nums.size();
    if (n <= 1) {
        return lista_nums;
    }

    // dividir en sub-vectores
    int mid = n / 2;
    vector<int> vector_one(lista_nums.begin(), lista_nums.begin() + mid);
    vector<int> vector_two(lista_nums.begin() + mid, lista_nums.end());

    //hacer la recursión de los vectores
    vector<int> sortedOne = merge_sort(vector_one);
    vector<int> sortedTwo = merge_sort(vector_two);

    //mezclar los vec
    return merge(sortedOne, sortedTwo);
}
//----------------------------------------------------------------------------------------//



int main(){
    string nombreArchivo = "datasets/random_dataset.txt";
    ifstream archivo(nombreArchivo.c_str());

    vector<int> listado;
    
    string num;
    //leer y guardar numeros del .txt
    while (getline(archivo, num, ' ')) {
        if (!num.empty()) listado.push_back(stoi(num));
    }

    vector<int> listado_ordenado;

    auto start = chrono::high_resolution_clock::now();
    listado_ordenado = merge_sort(listado);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> elapsed = end - start;
    cout << "time: " << elapsed.count() << " ms" << endl;
    
    //in seconds
    //chrono::duration<double, milli> elapsed = end - start;
    //cout << "t transcurrido: " << elapsed.count() << " segundos" << endl;

    for (int e: listado){
        cout << e << ' ';
    }
    cout << endl;

    return 0;
}
