/* ITCR. Ing.Computación.
   Análisis de algoritmos. GR 1
   Caso #2. Freetext Search
   Autora: Juleisy Porras Diaz.
*/

#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;

#define d 256 //numero de caracteres en el alfabeto

class Tiempos{
public: 
   int total;
   int forIter;
   int ifIter;
   clock_t ticks;
   Tiempos(){
      total = forIter = ifIter = 0;
   }

   void reset(){
      total = forIter = ifIter = ticks = 0;
   }
};

void rabinKarp(char pattern[], char text[], int q, Tiempos *T){
   int M = strlen(pattern);
   int N = strlen(text);
   int i, j;
   int p = 0; //valor hash para el patrón
   int t = 0; //valor hash para el texto
   int h = 1;

   clock_t t1;
   t1 = clock();
   for (i = 0; i < M - 1; i++)
      h = (h * d) % q;
      T->forIter++;

   for (i = 0; i < M; i++){
      p = (d * p + pattern[i]) % q;
      t = (d * t + text[i]) % q;
      T->forIter++;
   }
 
   for (i = 0; i <= N - M; i++){
      T->forIter++;
      if ( p == t ){
         T->ifIter++;    
         for (j = 0; j < M; j++){
            T->forIter++;
            if (text[i + j] != pattern[j])
               T->ifIter++;
               break;
         }
         if (j == M)
            T->ifIter++;
            cout << "Pattern found at index " << i << endl;
      }

      if ( i < N-M ){
         T->ifIter++;
         t = (d*(t - text[i]*h) + text[i+M])%q;

         if (t < 0)
            T->ifIter++;
            t = (t + q);
        }
   }
   clock_t t2 = clock() - t1;
   T->ticks = t2;
   T->total = T->forIter + T->ifIter;
   return;
}
 
int main(){
   char text[];
   FILE *fichero;
   int i=0;
   fichero = fopen("WarPeace.txt", "r");
   while(!feof(fichero))
      fscanf(fichero, "%s", text[i++]);
   fclose(fichero);

   char pattern[] = "and";
   int q = 101;

   Tiempos* T = new Tiempos();

   rabinKarp(pattern, text, q, T);

   cout << "Cantidad de for: " << T->forIter << endl;
   cout << "Cantidad de if: " << T->ifIter << endl;
   cout << "Medida en ticks: " << (T->ticks) << endl;
   cout << "Medida en segundos: " << (float(T->ticks) / CLOCKS_PER_SEC) << endl << endl;
   T->reset();
   
   return 0;

}