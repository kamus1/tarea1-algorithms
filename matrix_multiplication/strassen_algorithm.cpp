#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <cmath>

using namespace std;

//función para ajustar el tamaño de la matriz para que sea del tipo 2^n
vector<vector<int>> ajustar_matriz(const vector<vector<int>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    
    //se busaca la siguiente potencia de 2 más grande
    int max_dim = max(filas, columnas);
    int nueva_dim = pow(2, ceil(log2(max_dim)));
    
	// si la matriz ya es del tamaño correcto, devolverla sin cambios
    if (nueva_dim == max_dim) {
        return matriz;
    }
    
    //crear la nueva matriz que va a tneer tamaño nueva_dim x nueva_dim y llenarla con ceros
    vector<vector<int>> matriz_ajustada(nueva_dim, vector<int>(nueva_dim, 0));
    
    // y copiar los elementos de la matriz original a la nueva matriz ajustada
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz_ajustada[i][j] = matriz[i][j];
        }
    }
    
    return matriz_ajustada;
}


//esta funcion lee los datos del archivo .txt de las matrices generaras
vector<vector<int>> leer_matriz(const string& archivoEntrada) {
    ifstream file(archivoEntrada);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1); //terminar si no se pude encontrar el archivo
    }

    vector<vector<int>> matriz;
    string linea;
    
    while (getline(file, linea)) { //leer por linea
        istringstream iss(linea);
        vector<int> fila;
        int numero;
        
        while (iss >> numero) {
            fila.push_back(numero);
        }
        
        matriz.push_back(fila);
    }

    file.close();
    return matriz;
}

//funciones para la multiplicacion de matrices Metodo de Strassen
vector<vector<int> >
add_matrix(vector<vector<int> > matrix_A,
           vector<vector<int> > matrix_B, int split_index,
           int multiplier = 1)
{
    for (auto i = 0; i < split_index; i++)
        for (auto j = 0; j < split_index; j++)
            matrix_A[i][j]
                = matrix_A[i][j]
                  + (multiplier * matrix_B[i][j]);
    return matrix_A;
}
 
vector<vector<int> >
multiply_matrix(
	vector<vector<int> > matrix_A,
    vector<vector<int> > matrix_B
	)
{
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();
 
    if (col_1 != row_2) {
		cout << "ERROR: El numero de las columas en la matriz A debe de ser igual al numero de filas en la matriz b" << endl;
        return {};
    }
 
    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int> > result_matrix(row_1,result_matrix_row);
 
    if (col_1 == 1)
        result_matrix[0][0]
            = matrix_A[0][0] * matrix_B[0][0];
    else {
        int split_index = col_1 / 2;
 
        vector<int> row_vector(split_index, 0);
 
        vector<vector<int> > a00(split_index, row_vector);
        vector<vector<int> > a01(split_index, row_vector);
        vector<vector<int> > a10(split_index, row_vector);
        vector<vector<int> > a11(split_index, row_vector);
        vector<vector<int> > b00(split_index, row_vector);
        vector<vector<int> > b01(split_index, row_vector);
        vector<vector<int> > b10(split_index, row_vector);
        vector<vector<int> > b11(split_index, row_vector);
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index]
                                    [j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index]
                                    [j + split_index];
            }
 
        vector<vector<int> > p(multiply_matrix(
            a00, add_matrix(b01, b11, split_index, -1)));
        vector<vector<int> > q(multiply_matrix(
            add_matrix(a00, a01, split_index), b11));
        vector<vector<int> > r(multiply_matrix(
            add_matrix(a10, a11, split_index), b00));
        vector<vector<int> > s(multiply_matrix(
            a11, add_matrix(b10, b00, split_index, -1)));
        vector<vector<int> > t(multiply_matrix(
            add_matrix(a00, a11, split_index),
            add_matrix(b00, b11, split_index)));
        vector<vector<int> > u(multiply_matrix(
            add_matrix(a01, a11, split_index, -1),
            add_matrix(b10, b11, split_index)));
        vector<vector<int> > v(multiply_matrix(
            add_matrix(a00, a10, split_index, -1),
            add_matrix(b00, b01, split_index)));
 
        vector<vector<int> > result_matrix_00(add_matrix(
            add_matrix(add_matrix(t, s, split_index), u,
                       split_index),
            q, split_index, -1));
        vector<vector<int> > result_matrix_01(
            add_matrix(p, q, split_index));
        vector<vector<int> > result_matrix_10(
            add_matrix(r, s, split_index));
        vector<vector<int> > result_matrix_11(add_matrix(
            add_matrix(add_matrix(t, p, split_index), r,
                       split_index, -1),
            v, split_index, -1));
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                result_matrix[i][j]
                    = result_matrix_00[i][j];
                result_matrix[i][j + split_index]
                    = result_matrix_01[i][j];
                result_matrix[split_index + i][j]
                    = result_matrix_10[i][j];
                result_matrix[i + split_index]
                             [j + split_index]
                    = result_matrix_11[i][j];
            }
 
        a00.clear();
        a01.clear();
        a10.clear();
        a11.clear();
        b00.clear();
        b01.clear();
        b10.clear();
        b11.clear();
        p.clear();
        q.clear();
        r.clear();
        s.clear();
        t.clear();
        u.clear();
        v.clear();
        result_matrix_00.clear();
        result_matrix_01.clear();
        result_matrix_10.clear();
        result_matrix_11.clear();
    }
    return result_matrix;
}

//para ahorarse el codigo del print de la matriz
void imprimir_matriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int numero : fila) {
            cout << numero << " ";
        }
        cout << endl;
    }
}

int main() {
    //leer los archivos de las matrices
    vector<vector<int>> matriz_1 = leer_matriz("datasets/matriz_1.txt");
    vector<vector<int>> matriz_2 = leer_matriz("datasets/matriz_2.txt");

    int filas_A = matriz_1.size();
    int columnas_A = matriz_1[0].size();
    int filas_B = matriz_2.size();
    int columnas_B = matriz_2[0].size();

    if (columnas_A != filas_B) {
        cerr << "Las dimensiones no compatibles para multiplicación." << endl;
        return 1;
    }

	//se ajustan las matrices a la siguiente potencia de 2 (rellenar con ceros)
    vector<vector<int>> matriz_1_ajustada = ajustar_matriz(matriz_1);
    vector<vector<int>> matriz_2_ajustada = ajustar_matriz(matriz_2);

    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> producto = multiply_matrix(matriz_1_ajustada, matriz_2_ajustada);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " ms" << endl;


    //Print
    cout << "Matriz 1" << endl;
    //imprimir_matriz(matriz_1);
    cout << endl;

    cout << "Matriz 2" << endl;
    //imprimir_matriz(matriz_2);
    cout << endl;

    cout << "Producto" << endl;
    //imprimir_matriz(producto);

    return 0;
}
