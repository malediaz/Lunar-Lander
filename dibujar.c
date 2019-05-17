#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "dibujar.h"
#include "caracteres.h"
#include "diccionario.h"
#include "config.h"
#include "terreno.h"
#include "naves.h"

#define POSICION 10
#define MARGEN_SUP 30


void mensaje_dibujar(char *cadena, float f, SDL_Renderer *renderer, int posicion_x, int posicion_y) {
  size_t largo_cadena = strlen(cadena);
  
  for (size_t j = 0; j < largo_cadena; j++) {
    vectores_t letra_vector = conversion_a_vector(cadena[j]);
    size_t letra_longitud = conversion_a_longitud(cadena[j]);
      
    for (size_t i = 1; i < letra_longitud; i++)
      SDL_RenderDrawLine(
        renderer, 
        letra_vector[i - 1][0] * f + posicion_x + POSICION * j, 
       -letra_vector[i - 1][1] * f + posicion_y + MARGEN_SUP,     
        letra_vector[i][0] * f + posicion_x + POSICION * j, 
       -letra_vector[i][1] * f + posicion_y + MARGEN_SUP
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

//void dibujar_numero(double numero, float f, SDL_Renderer *renderer, int posicion_x, int posicion_y) {

void figura_dibujar(float **figura, SDL_Renderer *renderer, size_t nave_tam, int posicion_x, int posicion_y, float escala) {
  for(int i = 1; i < nave_tam; i++) //Dsps debería reemplazar VENTANA_ANCHO por la posicion de la nave
    SDL_RenderDrawLine(
			renderer,
			figura[i - 1][0] * escala + posicion_x, //ESTA ES LA X
     -figura[i - 1][1] * escala + posicion_y,      //ESTA ES LA Y
			figura[i][0] * escala + posicion_x,
     -figura[i][1] * escala + posicion_y
		);
}


/*void chorro_dibujar(float chorro[3][2], SDL_Renderer *renderer, int posicion_x, int posicion_y, float escala) {
  for(int i = 0; i < 3 - 1; i++) //Dsps debería reemplazar VENTANA_ANCHO por la posicion de la nave
    SDL_RenderDrawLine(
			renderer,
			chorro[i][0] * escala + posicion_x, //ESTA ES LA X
     -chorro[i][1] * escala + posicion_y,      //ESTA ES LA Y
			chorro[i+1][0] * escala + posicion_x,
     -chorro[i+1][1] * escala + posicion_y
		);
}
*/
