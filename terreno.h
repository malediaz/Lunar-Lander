#ifndef _TERRENO_H_
#define _TERRENO_H_


/* Función que recibe el vector con las coordenadas originales de la matriz,
  el número de coordenadas y la posición actual en x para obtener el punto de la recta 
  que corresponde al valor random de x obtenido*/
float obtener_coordenadas_y(float **v, size_t nv, float x);

/* Función para generar un número acotado de coordenadas aleatorias por segmento, recibe 
  un vector v con las coordenadas originales, un vector vRand con las mismas coordenadas que v
  y memoria asignada previmente (donde se guardarán las nuevas coordenadas random), el numero de 
  coordenadas originales, el numero de coordenadas a generar y el margen dento del cual deben 
  * estar las mismas */
void generar_coordenadas_random(float **v, float **vRand, size_t nv, size_t nn, float margen);

// Devuelve un vector que representa el terreno y su tamaño n.
float **terreno_crear(size_t *n);

/* Devuelve un vector que representa las coordenadas de las estrellas y devuelve por 
  interfaz el numero de estrellas. Recibe un vector terreno y su tamaño y guarda las coordenadas 
  random de las estrellas generadas solo s se encuentran por arriba del terreno */
float **estrellas_crear(float **terreno, size_t terreno_tam, size_t *n);


#endif // _TERRENO_H_
