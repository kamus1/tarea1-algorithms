#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

//------------------------------- Selection Sort ----------------------------------------//
void selection_sort(vector<int> &lista_nums){
    //en el primer for recorrer el vector, el segundo for busca el minimo hacia el lado derecho
    //luego hace un swap del valor minimo con el i
    for(int i= 0; i< lista_nums.size(); i++){
        int current_min = i;
        for(int j= i; j< lista_nums.size(); j++){
            int current_item = j;
            if(lista_nums[current_item] < lista_nums[current_min]){
                current_min = current_item;
            }
        }
        //swap
        swap(lista_nums[i], lista_nums[current_min]);

    }
}
//----------------------------------------------------------------------------------------//

int main(){
    vector<string> nombres_archivos = {
        "datasets/random_dataset.txt",
        "datasets/partially_sorted_dataset.txt",
        "datasets/semisorted_dataset.txt",
        "datasets/unique_random_dataset.txt",
    };

    cout << "Selection Sort" << endl;
    for( string nombreArchivo : nombres_archivos){

        ifstream archivo(nombreArchivo.c_str());
        vector<int> listado;
        
        string num;
        //leer y guardar numeros del .txt
        while (getline(archivo, num, ' ')) {
            if (!num.empty()) listado.push_back(stoi(num));
        }

        auto start = chrono::high_resolution_clock::now();
        selection_sort(listado);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> elapsed = end - start;
        //cout << nombreArchivo << " --- " << "Time: " << elapsed.count() << " ms" << endl;
        cout << "Time: " << elapsed.count() << " ms" << " | File: " << nombreArchivo << endl;
        
        //in seconds
        //chrono::duration<double, milli> elapsed = end - start;
        //cout << "t transcurrido: " << elapsed.count() << " segundos" << endl;
    }

    return 0;
}
