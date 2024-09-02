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
    string nombreArchivo = "datasets/random_dataset.txt";
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
