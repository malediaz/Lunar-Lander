#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "config.h"
#include "naves.h"
#include "terreno.h"
#include "dibujar.h"
#include "movimiento.h"

#define MENSAJES_ALTO 20
#define MARGEN_IZQUIERDO 150
#define MARGEN_DERECHO 650
#define ESPACIO 250
#define DT (1.0 / JUEGO_FPS)


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

	// El chorro de la nave:
	const float chorro_estatico[][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};
  
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
  size_t chorro_tam = sizeof(chorro_estatico) / sizeof(chorro_estatico[0]);
  size_t terreno_tam;
  
  /* Genero un terreno aleatorio en cada partida y convierto a vectores
     dinámicos las matrices de el chorro y la nave */
  srand(time(NULL));
  float **terreno = terreno_crear(&terreno_tam);
  float **nave = vector_desde_matriz(nave_grande, nave_tam);
  float **chorro = vector_desde_matriz(chorro_estatico, chorro_tam);

	// Queremos que todo se dibuje escalado por f:       
	float f = 1.5;
  double angulo = NAVE_ANGULO_INICIAL;

  //Estos son los mensajes de la información del juego que se verán en pantalla
  char *msj_izquierda[] = {"SCORE", "TIME", "FUEL"};
  char *msj_derecha[] = {"ALTITUDE", "HORIZONTAL SPEED", "VERTICAL SPEED"};
  char *flechas[] = {"<", "v"};
  
  // Tamaños
  size_t cant_msj_izq = sizeof(msj_izquierda) / sizeof(msj_izquierda[0]);
  size_t cant_msj_der = sizeof(msj_derecha) / sizeof(msj_derecha[0]);
  size_t cant_flechas = sizeof(flechas) / sizeof(flechas[0]);
 // char *valores[] = NULL;
  
  float posicion_y, velocidad_y;
  double dy, dx;
  
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
						// Agrandamos el dibujo del chorro y trasladamos la estructura:
            vector_trasladar(nave, nave_tam, cos(angulo), sin(angulo));
            vector_trasladar(chorro, chorro_tam, cos(angulo), sin(angulo));
						chorro[1][0] -= cos(angulo);
            chorro[1][1] -= sin(angulo);
						break;
            
					case SDLK_DOWN:
						// Achicamos el dibujo del chorro y trasladamos la estructura:
            vector_trasladar(nave, nave_tam, -cos(angulo), -sin(angulo));
            vector_trasladar(chorro, chorro_tam, -cos(angulo), -sin(angulo));
						chorro[1][0] += cos(angulo);
            chorro[1][1] += sin(angulo);
            break;
            
					case SDLK_RIGHT: 
            // Rotamos la estructura en un angulo positivo
            vector_rotar(nave, nave_tam, NAVE_ROTACION_PASO);
            vector_rotar(chorro, chorro_tam, NAVE_ROTACION_PASO);
            angulo += NAVE_ROTACION_PASO;                               // Guardamos el valor del ángulo actual
            break;
            
					case SDLK_LEFT: 
            // Rotamos la estructura en un angulo negativo 
            vector_rotar(nave, nave_tam, -NAVE_ROTACION_PASO);
            vector_rotar(chorro, chorro_tam, -NAVE_ROTACION_PASO);
            angulo -= NAVE_ROTACION_PASO;
						break;
				}
				// END código de la alumna


			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código de la alumna
    
    posicion_y = computar_posicion(NAVE_Y_INICIAL, NAVE_VY_INICIAL, DT);
    velocidad_y = computar_velocidad(posicion_y, -G, DT);
    
    dx = NAVE_VX_INICIAL * DT;
    dy = velocidad_y * DT;
    
    // Dibujo los mensajes que brindan la información del juego
    for (int i = 0; i < cant_msj_izq; i++)
      mensaje_dibujar(msj_izquierda[i], f, renderer, MARGEN_IZQUIERDO, MENSAJES_ALTO * i);
    
    for (int i = 0 ; i < cant_msj_der; i++)
      mensaje_dibujar(msj_derecha[i], f, renderer, MARGEN_DERECHO, MENSAJES_ALTO * i);
    
    for (int i = 0; i < cant_flechas; i++) 
      mensaje_dibujar(flechas[i], f, renderer, MARGEN_DERECHO + ESPACIO, MENSAJES_ALTO * (i + 1));

    // Dibujo los valores correspondientes cada mensaje
    /*double altitude = computar_posicion(NAVE_Y_INICIAL, NAVE_VY_INICIAL, JUEGO_FPS);
    double vertical_speed = computar_velocidad(NAVE_VY_INICIAL, G, JUEGO_FPS);
    double horizontal_speed = computar_velocidad(NAVE_X_INICIAL , 0, JUEGO_FPS); */
    
    //Dibujo el terreno aleatorio generado
    terreno_dibujar(terreno, renderer, terreno_tam);
    
    // Establezco la velocidad de la nave y el chorro en x, y luego los dibujo
    vector_trasladar(nave, nave_tam, dx, dy);
    figura_dibujar(nave, renderer, nave_tam, VENTANA_ANCHO / 2, VENTANA_ALTO / 2, f); 
		
    // Dibujamos el chorro escalado por f:
    vector_trasladar(chorro, chorro_tam, dx, dy);
    figura_dibujar(chorro, renderer, chorro_tam, VENTANA_ANCHO / 2, VENTANA_ALTO / 2, f);
    
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
    vector_destruir(terreno, terreno_tam, CANT_COLS);
    vector_destruir(nave, nave_tam, CANT_COLS);
    vector_destruir(chorro, chorro_tam, CANT_COLS);
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

