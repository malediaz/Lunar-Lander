#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "terreno.h"

#define COL 2


void vector_destruir(float **v ,size_t n ,size_t m) {
  for (int j = 0; j < n; j++)
      free(v[j]);
  
  free(v);
  v = NULL;                                    
}


/*Función auxiliar para la asignación de memoria de un vector dinámico de nCoordx2 que recibe 
  el vector, el número de elementos que tendrá y un mensaje a imprimir para especificar cuál 
  va a ser el vector a crear, y devuelve un puntero al primer elemento de dicho vector dinámico. 
  Precondición: el vector no debe tener un espacio de memoria asigndo previamente*/

float **asignar_memoria(size_t n, size_t m) {
  float **v = malloc(sizeof(float *) * n);

  if (v == NULL)
    return NULL;
  
  for (int i = 0; i < n; i++) {
    v[i] = malloc(sizeof(float) * m);
     
    if (v[i] == NULL) {
      vector_destruir(v, i, m);
      
      return NULL;
    }
  }
  
  return v;
}


// Genera un número random dento de un rango dado

float rand_float(float p0, float p1) {
  float random_float = ((float)rand() / (float)RAND_MAX);      //Genera un flotante aleatorio entre 0.0 y 1.0
  
  return  random_float * (p1 - p0);        
}


float **vector_desde_matriz(const float m[][2], size_t n) {
  float **v = NULL;

  if ((v = asignar_memoria(n, COL)) == NULL)
    return NULL;
   
  for (int i = 0; i < n; i++) { 
    for(int j = 0; j < COL; j++)
      v[i][j] = m[i][j];
  }
  
  return v;
}

// Función que intercambia las direcciones de memoria de dos punteros entre sí

void swap(float **v0, float **v1) { 
  float *auxiliar = NULL;

    auxiliar = *v1; 
    *v1 = *v0;
    *v0 = auxiliar;  
}

/* Función auxiliar que recibe un vector y su número de elementos y lo ordena 
   en forma creciente con respecto a sus coordenadas en x */
   
void vector_ordenar(float **v, size_t nn) {
    int i, j;
    
    for (i = 0; i < (nn - 1); i++) { 
      for (j = i + 1; j < nn; j++) { 
        if (v[j][0] < v[i][0]) { 
          swap(&v[i], &v[j]);
      } 
    }
  } 
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
    vRand[i][1] = v[i][1];
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
  
  if ((vDensif = asignar_memoria(nn, COL)) == NULL)
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


  

