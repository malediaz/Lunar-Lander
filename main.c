#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "naves.h"
#include "terreno.h"
#include "dibujar.h"
#include "movimiento.h"

#define ALTO_MENSAJES 20
#define MARGEN_IZQUIERDO 150
#define MARGEN_DERECHO 650
#define ESPACIO 250


int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;

	// BEGIN código de la alumna
	// Mi nave:
	nave_t nave = nave_grande;
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);

	// El chorro de la nave:
	float chorro[3][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};

	// Queremos que todo se dibuje escalado por f:       
	float f = 1.5;
  
  size_t n_puntos;
  
  //Genero un terreno aleatorio en cada partida
  srand(time(NULL));
  float **terreno = terreno_crear(&n_puntos);


  //Estos son los mensajes de la información del juego que se verán en pantalla
  char *msj_izquierda[] = {"SCORE", "TIME", "FUEL"};
  char *msj_derecha[] = {"ALTITUDE", "HORIZONTAL SPEED", "VERTICAL SPEED"};
  char *flechas[] = {"<", "v"};
  
  size_t cant_msj_izq = sizeof(msj_izquierda) / sizeof(msj_izquierda[0]);
  size_t cant_msj_der = sizeof(msj_derecha) / sizeof(msj_derecha[0]);
  size_t cant_flechas = sizeof(flechas) / sizeof(flechas[0]);
 // char *valores[] = NULL;
  
	// END código de la alumna

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						// Agrandamos el dibujo del chorro:
						chorro[1][1] -= 1;
            
						break;
					case SDLK_DOWN:
						// Achicamos el dibujo del chorro:
						chorro[1][1] += 1;
					case SDLK_RIGHT:
                
            nave_dibujar(nave, renderer, nave_tam, VENTANA_ANCHO/2, VENTANA_ALTO/2, f); 
					case SDLK_LEFT:
          
						break;
				}
				// END código del alumno


			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código de la alumna
    
    //Dibujo el terreno aleatorio generado
    terreno_dibujar(terreno, renderer, n_puntos);
    
    // Dibujo los mensajes que brindan la información del juego
    
    for (int i = 0; i < cant_msj_izq; i++)
      mensaje_dibujar(msj_izquierda[i], f, renderer, MARGEN_IZQUIERDO, ALTO_MENSAJES * i);
    
    for (int i = 0 ; i < cant_msj_der; i++)
      mensaje_dibujar(msj_derecha[i], f, renderer, MARGEN_DERECHO, ALTO_MENSAJES * i);
    
    for (int i = 0; i < cant_flechas; i++) 
      mensaje_dibujar(flechas[i], f, renderer, MARGEN_DERECHO + ESPACIO, ALTO_MENSAJES * (i + 1));

    // Dibujo los valores correspondientes cada mensaje
    /*double altitude = computar_posicion(NAVE_Y_INICIAL, NAVE_VY_INICIAL, JUEGO_FPS);
    double vertical_speed = computar_velocidad(NAVE_VY_INICIAL, G, JUEGO_FPS);
    double horizontal_speed = computar_velocidad(NAVE_X_INICIAL , 0, JUEGO_FPS); */
    
    //Dibujo el terreno aleatorio generado
    terreno_dibujar(terreno, renderer, n_puntos);
    
    nave_dibujar(nave, renderer, nave_tam, VENTANA_ANCHO/2, VENTANA_ALTO/2, f); 
		
    // Dibujamos el chorro escalado por f:
    chorro_dibujar(chorro, renderer, VENTANA_ANCHO/2, VENTANA_ALTO/2, f);
    
    
		// END código del alumno


        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
    vector_destruir(terreno, n_puntos, 2);
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

