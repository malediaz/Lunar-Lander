#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "terreno.h"
#include "vector.h"


// Genera un número random dento de un rango dado

float rand_float(float p0, float p1) {
  float random_float = ((float)rand() / (float)RAND_MAX);      //Genera un flotante aleatorio entre 0.0 y 1.0
  
  return  random_float * (p1 - p0);        
}


/*Función que recibe el vector con las coordenadas originales de la matriz,
  el número de coordenadas y la posición actual en x para obtener el punto de la recta 
  que corresponde al valor random de x obtenido*/
  
float obtener_coordenadas_y(float **v, size_t nv, float x) {
  for (size_t i = 1; i < nv; i++) {
    if (x >= v[i - 1][0] && x <= v[i][0]) {
      float x0 = v[i - 1][0], x1 = v[i][0];
      float y0 = v[i - 1][1], y1 = v[i][1];

      return ((y1 - y0) / (x1 - x0)) * (x - x0) + y0;
    }
  }
  
  return 0;
}  


/* Función para generar un número acotado de coordenadas aleatorias por segmento, recibe 
  un vector v con las coordenadas originales, un vector vRand donde se guardarán las nuevas
  coordenadas, el numero de coordenadas originales, el numero de coordenadas a generar y el 
  margen en el que deben estar las mismas */
  
void generar_coordenadas_random(float **v, float **vRand, size_t nv, size_t nn, float margen) {
  int i = 0;
  float y;
  float x0 = v[0][0], xf = v[nv - 1][0];
  
  for(; i < nv; i++) {
    vRand[i][0] = v[i][0];
    vRand[i][1] = v[i][1];          //Funcion copiar vector en densificar
  }
  
  for(; i < nn; i++){
    vRand[i][0] = rand_float(x0, xf);
    
    y = obtener_coordenadas_y(v, nv, vRand[i][0]);
    
    vRand[i][1] =  y + rand_float(y - margen, y + margen);
  }
}


/* Precondición: el vector en el que se grabarán las nuevas coordenadas no
   debe tener un lugar de memoria asignado proviamente */

float **vector_densificar(float **v, size_t nv, size_t nn, float margen) {
  float **vDensif = NULL;
  
  if ((vDensif = vector_asignar_memoria(nn, CANT_COLS)) == NULL)
    return NULL;
 
  generar_coordenadas_random(v, vDensif, nv, nn, margen);
  
  vector_ordenar(vDensif, nn);
  
  return vDensif;
}


// Devuelve un vector que representa el terreno y su tamaño n.

float **terreno_crear(size_t *n) {  
  const float terreno_estatico[][2] = {
    {0, 100},
    {-1, VENTANA_ALTO * 2.0 / 3},
    {VENTANA_ANCHO, 100}
  };

  size_t nt = 3;
  float **terreno = vector_desde_matriz(terreno_estatico, nt);

  if (terreno == NULL)
    return NULL;

  // Asignamos la coordenda del medio aleatoriamente_
  terreno[1][0]  = (float)(rand() % VENTANA_ANCHO);
  
  // Iterativamente densificamos 30 veces achicando el margen cada vez:
  for (size_t i = 1; i < 30; i++) {
    float **aux;
    aux = vector_densificar(terreno, nt, 2 * (i + 5), 100 / i);
    vector_destruir(terreno, nt, 2);

    if (aux == NULL)
      return NULL;

    terreno = aux;
    nt = 2 * (i + 5);
  }
  *n = nt;

  return terreno;
}


  

