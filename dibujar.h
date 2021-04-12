#ifndef _DIBUJAR_H_
#define _DIBUJAR_H_


#define MAX_CADENA 9999
#define MARGEN_SUP 30
#define FLECHAS_ESPACIO 230
#define VALORES_ESPACIO 210
#define VALORES_MARGEN_IZQ (MSJ_INFO_MARGEN_IZQ + VALORES_ESPACIO / 2)
#define VALORES_MARGEN_DER (MSJ_INFO_MARGEN_DER + VALORES_ESPACIO)
#define FIGURA_ESCALA 1
#define MSJ_ALTO 20
#define MSJ_INFO_MARGEN_IZQ 180
#define MSJ_INFO_MARGEN_DER 600
#define MSJ_INFO_ESCALA 1.5
#define MSJ_INFO_ESPACIO 10
#define MSJ_FIN_PARTIDA_MARGEN 150
#define MSJ_DESTR_ESCALA 12
#define MSJ_DESTR_ESPACIO 30
#define MSJ_ATERRIZAJE_ESCALA 8
#define MSJ_ATERRIZAJE_ESPACIO 23
#define MSJ_FIN_PARTIDA_ALTO 350
#define MSJ_DER_MIN_DIGIT 0
#define MSJ_IZQ_MIN_DIGIT 4


/* Dado ua cadena, con su posicion inicial, su escala y el espacio que separa cada letra,
  se imprimen los caracteres correspondientes en pantalla, a partir de un margen superior 
  fijo para la impresion de los caracteres, alineandolos a la izquierda */
void msj_dibujar_izq(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio);

/* Dado ua cadena, con su posicion inicial, su escala y el espacio que separa cada letra,
  se imprimen los caracteres correspondientes en pantalla, a partir de un margen superior 
  fijo para la impresion de los caracteres, alineándolos a la derecha */
void msj_dibujar_der(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio);

/* Dado un valor, con su posicion inicial, su cantidad mínima de dígitos y su escala,
   y se imprimen los caracteres correspondientes en pantalla, a partir de un margen
   superior fijo, alineándolos a la izquierda */
void valores_dibujar_izq(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio, int min_digit);

/* Dado un valor, con su posicion inicial, su cantidad mínima de dígitos y su escala,
   y se imprimen los caracteres correspondientes en pantalla, a partir de un margen
   superior fijo, alineándolos a la derecha */
void valores_dibujar_der(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio, int min_digit);

/* Dado un tiempo en segundos, con su posicion inicial y su escala, se convierte 
   a formato min : seg y se imprimen los caracteres correspondientes en pantalla, 
   a partir de un margen superior fijo, alineándolos a la izquierda */
void tiempo_dibujar(time_t tiempo_en_segundos, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio);

/* Dado un puntero a punteros a floats que representa las coordenadas de una figura, 
  con su posicion inicial y su escala, se imprime la figura correspondiente en pantalla */
void figura_dibujar(float **figura, float escala, SDL_Renderer *renderer, size_t nave_tam, int posicion_x, int posicion_y);

/* Dado un puntero a punteros a floats que representa las coordenadas de un terreno 
  con la cantidad de puntos que lo representan, se lo imprime en pantalla */
void terreno_dibujar(float **terreno, SDL_Renderer *renderer, size_t n_puntos);

/* Recibe un vector dinámico donde se encuentran las coordenadas de las estrellas y 
  el numero de estrellas n_estrellas y las dibuja */
void estrellas_dibujar(float **estrellas, SDL_Renderer *renderer, size_t n_estrellas);


#endif // _DIBUJAR_H_
