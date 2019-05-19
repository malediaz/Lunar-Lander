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
#include "vector.h"

#define MENSAJES_ALTO 20
#define MARGEN_IZQ 150
#define MARGEN_DER 650
#define FLECHAS_ESPACIO 250
#define VALORES_ESPACIO 200
#define DT (1.0 / JUEGO_FPS)
#define MSJ_INFO_ESPACIO 10
#define MSJ_FIN_PARTIDA_ESPACIO 30
#define FIGURA_ESCALA 1
#define MSJ_INFO_ESCALA 1.5
#define MSJ_FIN_PARTIDA_ESCALA 10
#define MSJ_FIN_PARTIDA_ALTO 400


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
  
  float **chorro;
  float **nave;
  
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
  size_t chorro_tam = sizeof(chorro_estatico) / sizeof(chorro_estatico[0]);
  size_t terreno_tam;
  
  /* Genero un terreno aleatorio en cada partida y convierto a vectores
     dinámicos las matrices de el chorro y la nave */
  srand(time(NULL));
  float **terreno = terreno_crear(&terreno_tam);


  //Estos son los mensajes de la información del juego que se verán en pantalla
  char *msj_izquierda[] = {"SCORE", "TIME", "FUEL"};
  char *msj_derecha[] = {"ALTITUDE", "HORIZONTAL SPEED", "VERTICAL SPEED"};
  char *aterrizaje_bueno = "YOU HAVE LANDED";
  char *aterrizaje_violento = "YOU LANDED HARD";
  char *destruccion = "DESTROYED";
  char *arriba = "^", *abajo = "v", *derecha = ">", *izquierda = "<";
  
  // Tamaños
  size_t cant_msj_izq = sizeof(msj_izquierda) / sizeof(msj_izquierda[0]);
  size_t cant_msj_der = sizeof(msj_derecha) / sizeof(msj_derecha[0]);
 // char *valores[] = NULL;
  

  double angulo = NAVE_ANGULO_INICIAL;
  double px = NAVE_X_INICIAL, py = NAVE_Y_INICIAL;
  double  vy = NAVE_VY_INICIAL, vx = NAVE_VX_INICIAL;
  double dx = 0, dy = 0;
  int potencia = NAVE_POTENCIA_INICIAL;
  int combustible = JUEGO_COMBUSTIBLE_INICIAL;
  time_t segundos = 0, tracker = 0;
  
	// END código de la alumna

    
	unsigned int ticks = SDL_GetTicks();
	while(1) {   
    nave = vector_desde_matriz(nave_grande, nave_tam); 
    if (nave == NULL)
      return EXIT_FAILURE;
    
    chorro = vector_desde_matriz(chorro_estatico, chorro_tam);
    if (chorro == NULL)
      return EXIT_FAILURE;
    
      
    if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
    
				switch(event.key.keysym.sym) {
					case SDLK_UP:
            if (potencia < NAVE_MAX_POTENCIA) {
              // Agrandamos el dibujo del chorro y trasladamos la estructura:
              potencia++;
            }
						break;

					case SDLK_DOWN:
						if (potencia > 0) {
              // Achicamos el dibujo del chorro y trasladamos la estructura:
              potencia--;
            }
            break;

					case SDLK_RIGHT: 
            if (angulo <= PI / 2) {              
              combustible -= JUEGO_COMBUSTIBLE_RADIANES;
              angulo += NAVE_ROTACION_PASO;                     // Guardamos el valor del ángulo actual
            }
            break;

					case SDLK_LEFT: 
            if (angulo >= -PI / 2) {
              combustible -= JUEGO_COMBUSTIBLE_RADIANES;
              angulo -= NAVE_ROTACION_PASO;
            }
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
    
    if (tracker % JUEGO_FPS == 0) {
      segundos++;
      combustible -= JUEGO_COMBUSTIBLE_POT_X_SEG * potencia;
    }
    tracker++;
    
    chorro[1][1] -= potencia;
    vy = computar_velocidad(vy * cos (angulo), -G, DT);
    py = computar_posicion(py, vy, DT);
    px = computar_posicion(px, vx, DT);
    dx = vx * DT;
    dy = vy * DT;
    
    // Dibujo los mensajes que brindan la información del juego con sus respectivos valores
    for (int i = 0; i < cant_msj_izq; i++) {
      mensaje_dibujar(msj_izquierda[i], MSJ_INFO_ESCALA, renderer, MARGEN_IZQ, MENSAJES_ALTO * i, POSICION);
    }
    
    for (int i = 0 ; i < cant_msj_der; i++) {
      mensaje_dibujar(msj_derecha[i], MSJ_INFO_ESCALA, renderer, MARGEN_DER, MENSAJES_ALTO * i, POSICION);
    }

    if (vx < 0)
      mensaje_dibujar(izquierda, MSJ_INFO_ESCALA, renderer, MARGEN_DER + FLECHAS_ESPACIO, MENSAJES_ALTO, POSICION);
    if (vx > 0)
      mensaje_dibujar(derecha, MSJ_INFO_ESCALA, renderer, MARGEN_DER + FLECHAS_ESPACIO, MENSAJES_ALTO, POSICION);
      
    if (vy < 0)
      mensaje_dibujar(abajo, MSJ_INFO_ESCALA, renderer, MARGEN_DER + FLECHAS_ESPACIO, MENSAJES_ALTO * 2, POSICION);
    if (vy > 0)
      mensaje_dibujar(arriba, MSJ_INFO_ESCALA, renderer, MARGEN_DER + FLECHAS_ESPACIO, MENSAJES_ALTO * 2, POSICION);
        

    // Dibujo los valores correspondientes cada mensaje
    //double vertical_speed = computar_velocidad(NAVE_VY_INICIAL, G, JUEGO_FPS);
    //double horizontal_speed = computar_velocidad(NAVE_X_INICIAL , 0, JUEGO_FPS); 
    tiempo_dibujar(segundos, MSJ_INFO_ESCALA, renderer, MARGEN_IZQ + VALORES_ESPACIO, MENSAJES_ALTO * 1, MSJ_INFO_ESPACIO);
    valores_dibujar(combustible, MSJ_INFO_ESCALA, renderer, MARGEN_IZQ + VALORES_ESPACIO, MENSAJES_ALTO * 2, MSJ_INFO_ESPACIO, 4);
    
    valores_dibujar(py, MSJ_INFO_ESCALA, renderer, MARGEN_DER + VALORES_ESPACIO, 0, MSJ_INFO_ESPACIO, 0);
    valores_dibujar(vx, MSJ_INFO_ESCALA, renderer, MARGEN_DER + VALORES_ESPACIO, MENSAJES_ALTO * 1, MSJ_INFO_ESPACIO, 0);
    valores_dibujar(vy, MSJ_INFO_ESCALA, renderer, MARGEN_DER + VALORES_ESPACIO, MENSAJES_ALTO * 2, MSJ_INFO_ESPACIO, 0);
    
    vector_rotar(nave, nave_tam, angulo);
    vector_rotar(chorro, chorro_tam, angulo);
    vector_trasladar(nave, nave_tam, dx, dy);
    vector_trasladar(chorro, chorro_tam, dx, dy);
    
    mensaje_dibujar("SEND HELP", MSJ_INFO_ESCALA, renderer, MARGEN_IZQ*2, VENTANA_ANCHO/2, POSICION);
    
    if (px < 0) 
    px = VENTANA_ANCHO; 
      
    if (px > VENTANA_ANCHO)
    px = 0;    
    
    //Dibujo el terreno aleatorio generado
    terreno_dibujar(terreno, renderer, terreno_tam);
    
    // Establezco la velocidad de la nave y el chorro en x, y luego los dibujo
    figura_dibujar(nave, renderer, nave_tam, px, py, FIGURA_ESCALA); 
		
    // Dibujamos el chorro escalado por f:
    figura_dibujar(chorro, renderer, chorro_tam, px, py, FIGURA_ESCALA);
    
    
    if (!vector_esta_arriba(terreno, terreno_tam, px, py)) {
      if (vx > -1 && vx < 1 && vy > -10 && vy < 10 && angulo > -0.01 && angulo < 0.01 )
        mensaje_dibujar(aterrizaje_bueno, MSJ_FIN_PARTIDA_ESCALA, renderer, MARGEN_IZQ * 1.5, MSJ_FIN_PARTIDA_ALTO, MSJ_FIN_PARTIDA_ESPACIO * 2);
     
      if (vx > -2 && vx < 2 && vy > -20 && vy < 20 && angulo > -0.01 && angulo < 0.01)
        mensaje_dibujar(aterrizaje_violento, MSJ_FIN_PARTIDA_ESCALA, renderer, MARGEN_IZQ * 1.5, MSJ_FIN_PARTIDA_ALTO, MSJ_FIN_PARTIDA_ESPACIO * 2);
     
      else
        mensaje_dibujar(destruccion, MSJ_FIN_PARTIDA_ESCALA, renderer, MARGEN_IZQ * 1.5, MSJ_FIN_PARTIDA_ALTO, MSJ_FIN_PARTIDA_ESPACIO * 2);
      
      dormir = 1000;
      px = NAVE_X_INICIAL;
      py = NAVE_Y_INICIAL;
      angulo = NAVE_ANGULO_INICIAL;
      vx = NAVE_VX_INICIAL;
      vy = NAVE_VY_INICIAL;
      potencia = NAVE_POTENCIA_INICIAL;
      terreno = terreno_crear(&terreno_tam);
    }
    
    if (combustible <= 0)
      break;
    
    
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
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

