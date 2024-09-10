# Tarea 1 Algoritmos Dividir y Conquistar
Benjamín Camus Valdés
202173072-9

Para generar datasets de los algoritmos de ordenamiento usar: sorting/datasets/generate_datasets.cpp

En este archivo se pueden especificar los siguientes parámetros:
![image](https://github.com/user-attachments/assets/24c14fcc-51e9-455c-81b2-0d7523507c5b)

Para generar matrices usar el el archivo: matrix_multiplication/datasets/generate_matrix.cpp

Se pueden especificar los siguientes parámetros:
![image](https://github.com/user-attachments/assets/ccf726b3-49f8-421f-90c6-c80d51e4c691)

Una vez generados los datasets, se pueden ejecutar los archivos de los algoritmos correspondientes. Cada resultado será exportado en un archivo .txt:


Algoritmos de ordenamiento:

 • s_bubble sort.txt: Datos ordenados (sorted) luego de usar Bubble Sort.
 
 • s_selection sort.txt: Datos ordenados luego de usar Selection Sort.
 
 • s_merge sort.txt: Datos ordenados luego de usar Merge Sort.
 
 • s_quick sort.txt: Datos ordenados luego de usar Quick Sort.
 
 • s_cpp fun sort.txt: Datos ordenados luego de usar la función Sort de la librería estándar de C++.


 Algoritmos de Multiplicación de Matrices:
 
 • res_cubic_traditional.txt: Resultado de la multiplicación de matrices del algoritmo tradicional cúbico.
 
 • res_cubic_op.txt: Resultado de la multiplicación de matrices del algoritmo cúbico optimizado,
 sin considerar el tiempo de transponer la matriz B.
 
 • res_cubic_op_T.txt: Resultado de la multiplicación de matrices del algoritmo cúbico optimizado, considerando el tiempo de transponer la matriz B.

 • res_strassen_g4g.txt: Resultado de la multiplicación de matrices del algoritmo de Strassen.
 
 • res_strassen.txt: Resultado de la multiplicación de matrices del algoritmo de Strassen que usa
 hojas.
 
 • res_strassen_no_square.txt: Resultado de la multiplicación de matrices del algoritmo de Strassen
 adaptado a multiplicar matrices no cuadradas.
