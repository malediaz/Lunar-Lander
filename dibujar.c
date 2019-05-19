#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "dibujar.h"
#include "caracteres.h"
#include "diccionario.h"
#include "config.h"
#include "vector.h"

#define MARGEN_SUP 30
#define MAX_CADENA 9999

/* Dado ua cadena, con su posicion inicial, su escala y el espacio que separa cada letra,
  se imprimen los caracteres correspondientes en pantalla */

void mensaje_dibujar(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio) {
  size_t largo_cadena = strlen(cadena);
  
  for (size_t j = 0; j < largo_cadena; j++) {
    vectores_t letra_vector = conversion_a_vector(cadena[j]);
    size_t letra_longitud = conversion_a_longitud(cadena[j]);
      
    for (size_t i = 1; i < letra_longitud; i++)
      SDL_RenderDrawLine(
        renderer, 
        letra_vector[i - 1][0] * escala + posicion_x + espacio * j, 
       -letra_vector[i - 1][1] * escala + posicion_y + MARGEN_SUP,     
        letra_vector[i][0] * escala + posicion_x + espacio * j, 
       -letra_vector[i][1] * escala + posicion_y + MARGEN_SUP
      );      
  }
}


/* Dado un putero a punteros a floats que representa las coordenadas de un terreno 
  con la cantidad de puntos que lo representan, se lo imprime en pantalla */

void terreno_dibujar(float **terreno, SDL_Renderer *renderer, size_t n_puntos) {
  for (size_t i = 1; i < n_puntos; i++) {
      SDL_RenderDrawLine(
        renderer, 
        terreno[i - 1][0], 
       -terreno[i - 1][1] + VENTANA_ALTO, 
        terreno[i][0], 
       -terreno[i][1] + VENTANA_ALTO
     );
  }
}

/* Dado un putero a punteros a floats que representa las coordenadas de una figura, 
  con su posicion inicial y su escala, se imprime la figura correspondiente en pantalla */

void figura_dibujar(float **figura, SDL_Renderer *renderer, size_t nave_tam, int posicion_x, int posicion_y, float escala) {
  for(int i = 1; i < nave_tam; i++) //Dsps debería reemplazar VENTANA_ANCHO por la posicion de la nave
    SDL_RenderDrawLine(
			renderer,
			figura[i - 1][0] * escala + posicion_x, //ESTA ES LA X
     -figura[i - 1][1] * escala - posicion_y + VENTANA_ALTO,      //ESTA ES LA Y
			figura[i][0] * escala + posicion_x,
     -figura[i][1] * escala - posicion_y + VENTANA_ALTO
		);
}


/* Dado un valor, con su posicion inicial, su cantidad mínima de dígitos y su escala,
   y se imprimen los caracteres correspondientes en pantalla */

void valores_dibujar(int valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio, int min_digit) {
  char aux[MAX_CADENA];
  itoa(valor, aux, 10, min_digit);
  
  mensaje_dibujar(aux, escala, renderer, posicion_x, posicion_y, espacio);
}


/* Dado un tiempo en segundos, con su posicion inicial y su escala, se convierte 
   a formato min : seg y se imprimen los caracteres correspondientes en pantalla */

void tiempo_dibujar(time_t tiempo_en_segundos, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio) {
  time_t minutos = tiempo_en_segundos / 60;
  valores_dibujar(minutos, escala, renderer, posicion_x, posicion_y, espacio, 2);
  
  time_t segundos = tiempo_en_segundos % 60;
  valores_dibujar(segundos, escala, renderer, posicion_x + espacio * 3, posicion_y, espacio, 2);
}
  
  
  

