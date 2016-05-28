#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <list>

using namespace std;

void ColocaComensales(short int** matriz, int n_comensales, list<int>& resultado_final)
{
  //Recorro la lista de resultados para ver el mejor lugar para insertar el siguiente comensal.
  //El índice i es el comensal actual y el j es el que recorre la lista resultado_final.
  for(int i = 0; i < n_comensales; ++i)
  {
    list<int>::iterator mejor_posicion = resultado_final.begin();
    int mejor_afinidad = 0;

    for(list<int>::iterator iter = resultado_final.begin(); iter != resultado_final.end(); ++iter)
    {

      //Hallo el iterador de antes de end.
      list<int>::iterator antes_end = resultado_final.begin();
      for(list<int>::iterator iter = resultado_final.begin(); iter!=resultado_final.end(); ++iter)
      {
        list<int>::iterator aux = iter;
        ++aux;
        if(aux!=resultado_final.end())
          antes_end = aux;
      }

      //Asigno los pesos de cada comensal para sus acompañantes a izquierdas y derechas.
      int afinidad_izq = 0, afinidad_der = 0;
      if(iter == resultado_final.begin())
      {
        afinidad_izq = 100;
        afinidad_der = ((int)resultado_final.size()==1)?100:matriz[i][*iter];
      }
      else if (iter == antes_end)
      {
        afinidad_izq = ((int)resultado_final.size()==1)?100:matriz[i][*iter];
        afinidad_der = 100;
      }
      else
      {
        list<int>::iterator aux = iter;
        ++aux;
        afinidad_izq = matriz[i][*iter];
        afinidad_der = matriz[i][*aux];
      }

      //Cambio mejor afinidad y mejor posicion si he encontrado un lugar mejor donde insertar;
      int puntuacion = afinidad_der + afinidad_izq;
      if(puntuacion>mejor_afinidad)
        mejor_posicion = iter;
      if(puntuacion==200)
        break;
    }

    resultado_final.insert(mejor_posicion,i);
  }
}

int main(int argc, char*argv[])
{
  if(argc<2)
  {
    cout << "El formato es <numero comensales>" << endl;
    exit(1);
  }

  //Inicialización de la matriz de adyacencia de comensales.

  int num_comensales = atoi(argv[1]);
  short int** matriz_adyacencia = new short int*[num_comensales];
  for(int i = 0; i < num_comensales;++i)
    matriz_adyacencia[i] = new short int[num_comensales];

  //Rellenando la maatriz de adyacencia.

  srand(time(NULL));
  for(int i = 0; i < num_comensales; ++i)
    for(int j = 0; j < num_comensales; ++j)
      matriz_adyacencia[i][j] = rand() % 101;

  //Resolución del problema.
  list<int> mesa_comensales;
  ColocaComensales(matriz_adyacencia,num_comensales,mesa_comensales);
  


}
