#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "terreno.h"
#include "vector.h"
#include "movimiento.h"



float rand_float(float p0, float p1) {
  float random_float = ((float)rand() / (float)RAND_MAX);      //Genera un flotante aleatorio entre 0.0 y 1.0
  
  return  random_float * (p1 - p0) + p0;        
}


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


void generar_coordenadas_random(float **v, float **vRand, size_t nv, size_t nn, float margen) {
  float y;
  float x0 = v[0][0], xf = v[nv - 1][0];
  
  for(int i = nv; i < nn; i++){
    vRand[i][0] = rand_float(x0, xf);
    
    y = obtener_coordenadas_y(v, nv, vRand[i][0]);
    
    vRand[i][1] = rand_float(y - margen, y + margen);
  }
}


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
  for (size_t i = 1; i < 40; i++) {
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

float **estrellas_crear(float **terreno, size_t terreno_tam, size_t *n) {
  float **estrellas = vector_asignar_memoria(36, CANT_COLS);

  if (estrellas == NULL)
    return NULL;
  
  int i = 0;
  
  while (i < 36) {
    float estrella_x = rand_float(0, VENTANA_ANCHO);
    float estrella_y = rand_float(0, VENTANA_ALTO);
    
    if (!vector_esta_arriba(terreno, terreno_tam, estrella_x, estrella_y))
      continue;
      
    estrellas[i][0] = estrella_x;
    estrellas[i][1] = estrella_y;
    
    i++;
  }
  
  *n = i;
  
  return estrellas;
}

