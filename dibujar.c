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


void msj_dibujar_izq(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio) {
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


void figura_dibujar(float **figura, float escala, SDL_Renderer *renderer, size_t nave_tam, int posicion_x, int posicion_y) {
  for(int i = 1; i < nave_tam; i++) 
    SDL_RenderDrawLine(
			renderer,
			figura[i - 1][0] * escala + posicion_x,
     -figura[i - 1][1] * escala - posicion_y + VENTANA_ALTO, 
			figura[i][0] * escala + posicion_x,
     -figura[i][1] * escala - posicion_y + VENTANA_ALTO
		);
}


void valores_dibujar_izq(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio, int min_digit) {
  char aux[MAX_CADENA];
  itoa(valor, aux, 10, min_digit);
  
  msj_dibujar_izq(aux, escala, renderer, posicion_x, posicion_y, espacio);
}


void tiempo_dibujar(time_t tiempo_en_segundos, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio) {
  time_t minutos = tiempo_en_segundos / 60;
  valores_dibujar_izq(minutos, escala, renderer, posicion_x, posicion_y, espacio, 2);
  
  time_t segundos = tiempo_en_segundos % 60;
  valores_dibujar_izq(segundos, escala, renderer, posicion_x + espacio * 3, posicion_y, espacio, 2);
}

  
void msj_dibujar_der(char *cadena, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio) {
  size_t largo_cadena = strlen(cadena);
  invertir_cadena(cadena, largo_cadena);
  
  for (int j = largo_cadena - 1; j >= 0; j--) {
    vectores_t letra_vector = conversion_a_vector(cadena[j]);
    size_t letra_longitud = conversion_a_longitud(cadena[j]);
      
    for (size_t i = 1; i < letra_longitud; i++)
      SDL_RenderDrawLine(
        renderer, 
        letra_vector[i - 1][0] * escala + posicion_x - espacio * j, 
       -letra_vector[i - 1][1] * escala + posicion_y + MARGEN_SUP,     
        letra_vector[i][0] * escala + posicion_x - espacio * j, 
       -letra_vector[i][1] * escala + posicion_y + MARGEN_SUP
      );      
  }
}

   
void valores_dibujar_der(float valor, float escala, SDL_Renderer *renderer, int posicion_x, int posicion_y, int espacio, int min_digit) {
  char aux[MAX_CADENA];
  itoa(valor, aux, 10, min_digit);

  msj_dibujar_der(aux, escala, renderer, posicion_x, posicion_y, espacio);
}


void estrellas_dibujar(float **estrellas, SDL_Renderer *renderer, size_t n_estrellas) {
  for (int i = 0; i < n_estrellas; i++)
    msj_dibujar_izq("*", 1, renderer, estrellas[i][0], VENTANA_ALTO - MARGEN_SUP - estrellas[i][1], 0);
}
