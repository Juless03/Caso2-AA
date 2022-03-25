/* ITCR. Ing.Computación.
   Análisis de algoritmos. GR 1
   Caso #2. Quicksort logarítmico y cuadrático
   Autora: Juleisy Porras Diaz.
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

#define test1 //arrays con diferentes numeros de elementos para pruebas
    int arr1[1000];
    int arr2[2000];
    int arr3[3000];
    int arr4[4000];
    int arr5[5000];
    int arr6[6000];
    int arr7[7000];
    int arr8[8000];
    int arr9[9000];
    int arr10[10000];
    vector<int> tams = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    vector<int *> arrays = {arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9, arr10};
    int arrayNum = 10;

void simpleSort(int arr[], int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int particionar(int arr[], int imin, int imax) {

    int pivot = imin;
    int i = imin;   // i es el índice de inicio que retorna para luego "dividir" la colección en mitades
    int j = i+1;    // indice de fin
    while (j <= imax) {
        if (arr[j] < arr[pivot]) { 
            i++;    // aumente el indice de retorno
            swap(arr[i], arr[j]);
        }
        j++;    // aumente el indice final
    }
    swap(arr[i], arr[pivot]);   // pivote ordenado en su posicion final
    return i;  
}

int particionarRandom(int arr[], int imin, int imax) {
    srand(time(NULL));
    int random = imin + rand() % (imax - imin);
    swap(arr[random], arr[imin]);
    return particionar(arr, imin, imax);
}

int particionarMediana(int arr[], int imin, int imax) {
    int tab[] = {imin, (imax - imin) / 2, imax};
    simpleSort(tab, 3);
    int ind = 3 / 2;
    int mediana = tab[ind];
    swap(arr[mediana], arr[imin]);
    return particionar(arr, imin, imax);

}

void quickSort(int arr[], int imin, int imax, int pivotType) {
    int k;
    if (imin >= imax) { 
        return; 
    } // condicion de parada
    switch (pivotType) {
    case 0:
        k = particionar(arr, imin, imax);
        break;
    case 1:
        k = particionarMediana(arr, imin, imax);
        break;
    case 2:
        k = particionarRandom(arr, imin, imax);
        break;
    default:
        k = particionar(arr, imin, imax);
        break;
    }
    quickSort(arr, imin, k-1, pivotType); // mitad izquierda
    quickSort(arr, k+1, imax, pivotType); // mitad derecha
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << to_string(a[i]) << " ";
    cout << endl;
}

int main() {
    test1
    cout << "Quicksort logaritmico: " << endl << endl;

    for(int i = 0; i < arrays.size(); i++){
       clock_t t;
        t = clock();
        quickSort(arrays[i], 0, tams[i], 1);
        t = clock();
        cout << "Medida en segundos: " << ((double)t) / CLOCKS_PER_SEC << endl << endl;
    }

    cout << "Quicksort cuadratico: " << endl << endl;

    for(int i = 0; i < arrays.size(); i++){
        clock_t t;
        t = clock();
        quickSort(arrays[i], 0, tams[i], 2);
        t = clock();
        cout << "Medida en segundos: " << ((double)t) / CLOCKS_PER_SEC << endl << endl;
    }

    return 0;
}