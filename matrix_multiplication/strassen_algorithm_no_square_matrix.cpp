#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

//---------Tamaño de las hojas---------//
int leafsize = 1;
//-------------------------------------//

//funcion que lee las matrices de los archivos .txt 
//cada linea del archivo representa una fila de la matriz.
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
        while (iss >> numero) { fila.push_back(numero);}
        matriz.push_back(fila);// linea es una fila
    }
    file.close();
    return matriz;
}


//aqui solo se realizan declaraciones de funciones
void strassen(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, unsigned int n);
unsigned int nextPowerOfTwo(int n);
void strassenR(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam);
void suma(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam);
void resta(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam);
void printMatrix(const vector<vector<int>>& matrix, int n);
void leer(string filename, vector<vector<int>>& A, vector<vector<int>>& B);
int getMatrixSize(string filename);
void ikjalgorithm(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n);



//ikjalgorithm es el algoritmo que realiza la multiplicación de matrices de manera tradicional.
//solo se usa cuando el tamaño de la matriz es menor o igual a leafsize
void ikjalgorithm(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

//la funcion recursiva de strassen: divide las matrices A y B en submatrices de tamaño reducido A11, A12, ...
void strassenR(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam) {
    
    
    if(tam == 1){
        C[0][0] += A[0][0] * B[0][0];
        return;
    } else if  (tam <= leafsize) {
        //primero se verifica el tamaño de las hojas para ejecutar el algortimo ikj
        ikjalgorithm(A, B, C, tam);
        return;

    } else {
        int newTam = tam / 2; //nuevo tamaño de las sub matrices
        vector<int> inner(newTam); // se usa para inicializar las FILAS de las submatrices.
        
        //se definen al mismo tiempo todas las sub matrices y los producos P_i a calcular, así como los resultados
        vector<vector<int>> A11(newTam, inner), //ej: esta linea crea una matriz A11 con newTam filas, y cada fila es una copia del vector inner. entonces A11 es una matriz de newTam x newTam donde cada elemento está inicializado en 0
            A12(newTam, inner), //y lo mismo para las demas
            A21(newTam, inner),
            A22(newTam, inner),
            B11(newTam, inner), 
            B12(newTam, inner),
            B21(newTam, inner),
            B22(newTam, inner),
            C11(newTam, inner),
            C12(newTam, inner),
            C21(newTam, inner),
            C22(newTam, inner),
            P1(newTam, inner),
            P2(newTam, inner),
            P3(newTam, inner),
            P4(newTam, inner),
            P5(newTam, inner),
            P6(newTam, inner),
            P7(newTam, inner),
            aResult(newTam, inner),
            bResult(newTam, inner);
        
        // Dividiendo las matrices en 4 submatrices
        //se está dividiendo las matrices A y B en 4 submatrices mas pequeñas de tamaño newTam * newTam
        for (int i = 0; i < newTam; i++) { //i del for recorre las FILAS de las submatrices desde 0 hasta newTam
            for (int j = 0; j < newTam; j++) { // bucle for sobre las columnas j, que recorre las COLUMNAS de las submatrices de 0 hasta newTam
                /*
                A11 │ A12
                ────┼────
                A21 │ A22
                */
                A11[i][j] = A[i][j]; // elementos superiores-izquierdos de A que forman A11 
                A12[i][j] = A[i][j + newTam]; // elementos superiores-derechos de A que forman A12 (por eso se suma newtam a j, para llegar al otro cuadrante)

                A21[i][j] = A[i + newTam][j]; // elementos inferiores-izquierdos de A que forman A21
                A22[i][j] = A[i + newTam][j + newTam]; //lementos inferiores-derechos de A que forman A22

                //y se realiza lo mismo para B
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newTam];
                B21[i][j] = B[i + newTam][j];
                B22[i][j] = B[i + newTam][j + newTam];
            }
        }
        

        // a continuación se realizan los cálculos necesarios para aplicar el algoritmo de Strassen y obtener los siete productos intermedios de P1 a P7
        
        //----------------P1---------------------//
        suma(A11, A22, aResult, newTam); // suma de las submatrices A11 + A22 y el resultado se guarda en aResult
        suma(B11, B22, bResult, newTam); // suma de las submatrices B11 + B22 y el resultado se guarda en bResult

        // llama recursivamente a strassenR para multiplicar las sumas obtenidas en los pasos anteriores, es decir:
        //P1 = (A11 + A22) * (B11 + B22) Y almacena el resultado en P1
        strassenR(aResult, bResult, P1, newTam); 
        //---------------------------------------//
        
        //mismo procedimiento para los demas productos intermedios:
        //----------------P2---------------------//
        suma(A21, A22, aResult, newTam); 
        //P2 =(A21 + A22) * B11
        strassenR(aResult, B11, P2, newTam);
        //---------------------------------------//


        //----------------P3---------------------//
        resta(B12, B22, bResult, newTam); // B12 - B22
        // P3 = A11 * (B12 - B22)
        strassenR(A11, bResult, P3, newTam);
        //---------------------------------------//
        

        //----------------P4---------------------//
        resta(B21, B11, bResult, newTam);
        // P4 = A22 * (B21 - B11)
        strassenR(A22, bResult, P4, newTam);
        //---------------------------------------//


        //----------------P5---------------------//
        suma(A11, A12, aResult, newTam);
        //P5 = (A11 + A12) * B22
        strassenR(aResult, B22, P5, newTam);
        //---------------------------------------//


        //----------------P6---------------------//
        resta(A21, A11, aResult, newTam);
        suma(B11, B12, bResult, newTam);
        //P6 =(A21 - A11) * (B11 + B12)
        strassenR(aResult, bResult, P6, newTam);
        //---------------------------------------//


        //----------------P7---------------------//
        resta(A12, A22, aResult, newTam);
        suma(B21, B22, bResult, newTam);
        //P7 = (A12 - A22) * (B21 + B22)
        strassenR(aResult, bResult, P7, newTam);
        //---------------------------------------//



        // calculando C11, C12, C21, C22
        //este bloque de código utiliza los productos intermedios P1 a P7 calculados previamente con el algoritmo de Strassen
        //para ensamblar las submatrices C11, C12, C21, C22 que componen la matriz resultante
        suma(P3, P5, C12, newTam); // C12 = P3 + P5
        suma(P2, P4, C21, newTam); // C21 = P2 + P4

        suma(P1, P4, aResult, newTam); // aResult = P1 + P4 (suma intermedia)
        suma(aResult, P7, bResult, newTam); // bResult = aResult + P7
        resta(bResult, P5, C11, newTam); // C11 = P1+P4+P7 - P5

        suma(P1, P3, aResult, newTam); // aResult = P1 + P3 (suma intermedia)
        suma(aResult, P6, bResult, newTam); // bResult = aResult + P6
        resta(bResult, P2, C22, newTam); // C22 = P1+P3+P6 - P2

        // agrupa las submatrices C11, C12, C21, C22 en la matriz completa C 
        for (int i = 0; i < newTam; i++) {
            for (int j = 0; j < newTam; j++) {
                /*
                matriz C:
                C11 │ C12
                ────┼────
                C21 │ C22
                */
                C[i][j] = C11[i][j]; //C11  superior izquierda
                C[i][j + newTam] = C12[i][j]; // C12 superior derecha

                C[i + newTam][j] = C21[i][j]; //C21 inferior izquierda
                C[i + newTam][j + newTam] = C22[i][j]; //C22 inferior derecha
            }
        }
    }
}



//calcula la próxima potencia de 2, mayor o igual a un número dado
//se utiliza para asegurar que las matrices involucradas en la multiplicación tengan un tamaño que sea una potencia de 2

//se calcula el log_2(n), esto se redondea hacia arriba al entero mas cercano,
// y pow calcula 2 elevado al valor del exponente calculado previamente. Esto devuelve la potencia de dos más cercana que es mayor o igual a n
//ej pow(2, 3) = 2^3 = 8 que es la próxima potencia de dos mayor que 5
unsigned int nextPowerOfTwo(int n) {
    return pow(2, int(ceil(log2(n)))); 
}

//función principal que coordina la multiplicación de matrices utilizando el algoritmo de Strassen
void strassen(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, unsigned int n) {
    //aquí se calcula la siguiente potencia de dos mayor o igual al tamaño n de las matrices.
    //esto asegura que las matrices A y B puedan ser divididas de manera uniforme en submatrices durante la recursión del algoritmo.
    unsigned int m = nextPowerOfTwo(n);

    
    //inicialización de matrices auxiliares
    vector<int> inner(m); //vector de tamaño m
    vector<vector<int>> APrep(m, inner), BPrep(m, inner), CPrep(m, inner); //matrices m*m

    //copiar las matrices originales a las matrices expandidas:
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            APrep[i][j] = A[i][j];
            BPrep[i][j] = B[i][j];
        }
    }

    //llamada recursiva al algoritmo de Strassen
    strassenR(APrep, BPrep, CPrep, m); //resultado se guarda eb CPrep

    //copiar el resultado de vuelta a la matriz original
    //el resultado está almacenado en CPrep, se copian los valores relevantes (dentro de la región original de tamaño n×n) a la matriz C
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            C[i][j] = CPrep[i][j];
        }
    }
}



//función para sumar 2 matrices, se utiliza en strassenR
void suma(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

//función para restar 2 matrices, se utiliza en strassenR
void resta(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}



//función para leer el archivo de las matrices
void leer(string filename, vector<vector<int>>& A, vector<vector<int>>& B) {
    string line;
    ifstream matrixfile(filename);
    if (!matrixfile.is_open()) {
        cerr << "No se pudo leer el archivo " << filename << endl;
        return;
    }

    int i = 0, j, a;
    while (getline(matrixfile, line) && !line.empty()) {
        istringstream iss(line);
        j = 0;
        while (iss >> a) {
            A[i][j] = a;
            j++;
        }
        i++;
    }

    i = 0;
    while (getline(matrixfile, line)) {
        istringstream iss(line);
        j = 0;
        while (iss >> a) {
            B[i][j] = a;
            j++;
        }
        i++;
    }
}

//funcion para hacer un print por consola una matriz
void printMatrix(const vector<vector<int>>& matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != 0) {
                cout << "\t";
            }
            cout << matrix[i][j];
        }
        cout << endl;
    }
}


//función que exporta los datos la matrix a un archivo .txt
void exportar_matriz(const vector<vector<int>>& matriz, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para exportar la matriz." << endl;
        return;
    }

    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo.close();
}


//función para rellenar matrices con ceros hasta que sean del mismo tamaño
void rellenarMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    // buscar el número máximo de filas y columnas entre las dos matrices
    int maxFilas = max(A.size(), B.size());
    int maxColumnas = max(A[0].size(), B[0].size());

    //rellenar la matriz A con ceros
    for (auto& fila : A) {
        fila.resize(maxColumnas, 0);//ajustar el número de columnas
    }
    while (A.size() < maxFilas) {
        A.push_back(vector<int>(maxColumnas, 0));//agregar filas de ceros
    }

    //rellenar la matriz B con ceros
    for (auto& fila : B) {
        fila.resize(maxColumnas, 0);  
    }
    while (B.size() < maxFilas) {
        B.push_back(vector<int>(maxColumnas, 0)); 
    }
}

void ajustarTamañoMatriz(vector<vector<int>>& C, int filas_A, int columnas_B) {
    // Ajustar el tamaño de la matriz C para que coincida con las dimensiones originales
    // Reducir el número de filas si es necesario
    C.resize(filas_A);

    // Reducir el número de columnas en cada fila si es necesario
    for (auto& fila : C) {
        fila.resize(columnas_B);
    }
}

int main() {
    //leer los archivos de las matrices
    vector<vector<int>> A = leer_matriz("datasets/matriz_1.txt");
    vector<vector<int>> B = leer_matriz("datasets/matriz_2.txt");

    int filas_A = A.size();
    int n = filas_A;

    int columnas_A =A[0].size();
    int filas_B = B.size();
    int columnas_B = B[0].size();
    if(columnas_A != filas_B || filas_A != filas_B){
        rellenarMatrices(A, B);
    }
    vector<vector<int>> C(n, vector<int>(n));

    auto start = chrono::high_resolution_clock::now();
    strassen(A, B, C, n); // ejecutar el algoritmo de Strassen
    auto end = chrono::high_resolution_clock::now();


    chrono::duration<double, milli> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " ms" << endl;

    //ajustar tamaño de la matriz C al tamaño correcto antes de exportar
    //ya que podria contener valores de 0
    ajustarTamañoMatriz(C, filas_A, columnas_B);

    // exportar la matriz resultante a un archivo .txt
    exportar_matriz(C, "res_strassen_no_square.txt");
    return 0;
}
