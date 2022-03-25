/* ITCR. Ing.Computación.
   Análisis de algoritmos. GR 1
   Caso #2. Insertion Sort lineal y cuadrático
   Autora: Juleisy Porras Diaz.
*/

#include <iostream>
#include <vector>
#include <ctime>

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

class Tiempos{
public: 
    int total;
    int forIter;
    int whileIter;
    clock_t ticks;
    Tiempos(){
        total = forIter = whileIter = 0;
    }

    void reset(){
        total = forIter = whileIter = ticks = 0;
    }
};

void insertionSort(int *array, int numElements, Tiempos *T){
    int actualElement, previousElement;
    clock_t t1;
    t1 = clock();
    for(int i = 1; i < numElements; i++){
        actualElement = array[i];
        previousElement =  i - 1;
        T->forIter++;
        while(previousElement >= 0 && array[previousElement] > actualElement){
            array[previousElement + 1] = array[previousElement];
            previousElement--;
            T->whileIter++;
        }
        array[previousElement + 1] = actualElement;
    }
    clock_t t2 = clock() - t1;
    T->ticks = t2;
    T->total = T->forIter + T->whileIter;
    return;
}

int main(){
    test1
    Tiempos* T = new Tiempos();

    cout << "Comportamiento lineal: " << endl;
    for(int i = 0; i < 5; i++){
        insertionSort(arrays[i], tams[i], T);
        cout << "Medida en ticks: " << (T->ticks) << endl;
        cout << "Medida en segundos: " << (float(T->ticks) / CLOCKS_PER_SEC) << endl << endl;
        T->reset();
    }

    int value = 1;
    for(int i = 0; i < arrayNum; i++){ //peor caso
        for(int j = tams[i] - 1; j > 0; j--){
            arrays[i][j] = value;
            value++;
        }
        value = 1;
    }

    T->reset();

    cout << "Comportamiento cuadratico: " << endl;
    for(int i = 6; i < 10; i++){
        insertionSort(arrays[i], tams[i], T);
        cout << "Cantidad de for: " << T->forIter << endl;
        cout << "Cantidad de while: " << T->whileIter << endl;
        cout << "Medida en ticks: " << (T->ticks) << endl;
        cout << "Medida en segundos: " << (float(T->ticks) / CLOCKS_PER_SEC) << endl << endl;
        T->reset();
    }

    return 0;
}