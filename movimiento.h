#ifndef _MOVIMIENTO_H_
#define _MOVIMIENTO_H_


#define DT (1.0 / JUEGO_FPS)

/* Dada la velocidad actual vi, la aceleración a y el paso temporal dt 
  devuelve la velocidad del próximo instante */
double computar_velocidad(double vi ,double a ,double dt);

/* Dada la posición actual pi, la velocidad actual vi y el paso temporal
  dt devuelva la posición del próximo instante */
double computar_posicion(double pi, double vi ,double dt);

/* Recibe un vector de n coordenadas y devuelve un booleano dependiendo de
  si un punto de coordenadas (x, y) se encuentra por encima de la recta 
  delimitada por las coordenadas de v */
bool vector_esta_arriba(float **v, size_t n, float x, float y);

/* Dado un vector de coordenadas v modifica cada una de sus componentes 
  mediante la adición del par (dx, dy) */
void vector_trasladar(float **v, size_t n, float dx, float dy);

/* Dado un vector v de n coordenadas, rota cada una de ella rad radianes 
  con respecto al origen de coordenadas */
void vector_rotar(float **v, size_t n, double rad);


#endif // _MOVIMIENTO_H
