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


int main(void) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;
   
	// BEGIN código de la alumna

	// El chorro de la nave grande:
  const float chorro_grande[][2] = {
    {-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
    {0, NAVE_GRANDE_TOBERA_Y},
    {NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};
  
  // El chorro de la nave chica
  const float chorro_chico[][2] = {
    {-NAVE_CHICA_TOBERA_X, -NAVE_CHICA_TOBERA_Y},
    {0, -NAVE_CHICA_TOBERA_Y},
    {NAVE_CHICA_TOBERA_X, -NAVE_CHICA_TOBERA_Y}
  };
  
  float **nave_aterrizaje = NULL, **nave_vuelo = NULL;
  float **chorro_aterrizaje = NULL, **chorro_vuelo = NULL;
  
  //Tamaños
	size_t nave_aterrizaje_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
  size_t nave_vuelo_tam = sizeof(nave_chica) / sizeof(nave_chica[0]);
  size_t chorro_aterrizaje_tam = sizeof(chorro_grande) / sizeof(chorro_grande[0]);
  size_t chorro_vuelo_tam = sizeof(chorro_chico) / sizeof(chorro_chico[0]);
  size_t terreno_tam, estrellas_tam;
  
  
  /* Genero un terreno y una distribución de estrellas aleatoria en cada partida */
  srand(time(NULL));
  
  float **terreno = terreno_crear(&terreno_tam);
  float **estrellas = estrellas_crear(terreno, terreno_tam, &estrellas_tam);
  
  
  if (terreno == NULL) {   
    vector_destruir(estrellas, estrellas_tam, CANT_COLS);
    
    return EXIT_FAILURE;
  }
  
  if (estrellas == NULL) {   
    vector_destruir(terreno, terreno_tam, CANT_COLS);
    
    return EXIT_FAILURE;
  }
  
  
  // Variables 
  double px = NAVE_X_INICIAL, py = NAVE_Y_INICIAL;
  double  vy = NAVE_VY_INICIAL, vx = NAVE_VX_INICIAL;
  double dx = 0, dy = 0;
  double angulo = NAVE_ANGULO_INICIAL;
  double angulo_tracker = 0;
  double altitude = 0;
  float potencia = NAVE_POTENCIA_INICIAL;
  float fuel = JUEGO_COMBUSTIBLE_INICIAL;
  float score = 0;
  long long tracker = 0;
  time_t segundos = 0;


  // Mensajes de la información del juego que se verán en pantalla
  char *msj_izquierda[] = {"SCORE", "TIME", "FUEL"};
  char *msj_derecha[] = {"ALTITUDE", "HORIZONTAL SPEED", "VERTICAL SPEED"};
  char *aterrizaje_bueno = "YOU HAVE LANDED";
  char *aterrizaje_violento = "YOU LANDED HARD";
  char *destruccion = "DESTROYED";
  char *arriba = "^", *abajo = "v", *derecha = ">", *izquierda = "<";
  
  // Variables de los valores de la información del juego
  double *valores_der[] = {&altitude, &vx, &vy};
  float *valores_izq[] = {&score, &fuel};
  
  // Tamaños
  size_t cant_msj_izq = sizeof(msj_izquierda) / sizeof(msj_izquierda[0]);
  size_t cant_msj_der = sizeof(msj_derecha) / sizeof(msj_derecha[0]);
  size_t cant_valores_izq = sizeof(valores_izq) / sizeof(valores_izq[0]);
  size_t cant_valores_der = sizeof(valores_der) / sizeof(valores_der[0]);
  
  
	// END código de la alumna

    
	unsigned int ticks = SDL_GetTicks();
	while(1) {   
      
    if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				
        // BEGIN código de la alumna
				switch(event.key.keysym.sym) {
					case SDLK_UP:          
            if (potencia < NAVE_MAX_POTENCIA)
              potencia++;                                       // Incrementamos el valor de la potencia
           
            break;

					case SDLK_DOWN:
						if (potencia > 0)
              potencia--;                                        // Decrementamos el valor de la potencia
        
            break;

					case SDLK_LEFT: 
            if (angulo < PI / 2) {              
              fuel -= NAVE_ROTACION_PASO * JUEGO_COMBUSTIBLE_RADIANES;        // Decrementamos el valor del combustible 
              angulo_tracker += NAVE_ROTACION_PASO;
              angulo += NAVE_ROTACION_PASO;                     // Decrementamos el valor del ángulo
            }
            break;

					case SDLK_RIGHT: 
            if (angulo > -PI / 2) {
              fuel -= NAVE_ROTACION_PASO * JUEGO_COMBUSTIBLE_RADIANES;          // Decrementamos el valor del combustible 
              angulo -= NAVE_ROTACION_PASO;                      // Incrementamos el valor del ángulo 
              angulo_tracker += NAVE_ROTACION_PASO;
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
    
    
    /* Al estar sincronizado el ciclo de while y las FPS, cuando nuestra variable
      tracker tome el valor de JUEGO_FPS, habrá transcurrido 1 segundo */
       
    if (tracker != 0 && tracker % JUEGO_FPS == 0) {
      segundos++;                                                 // Tiempo del juego transcurrido
      fuel -= JUEGO_COMBUSTIBLE_POT_X_SEG * potencia;      // Descremento del combustible por segudo
    }
    tracker++;                                                    // Levamos la cuenta de las FPS totales
    

    // Variables de estado
    
    vx = computar_velocidad(vx, -potencia * sin(angulo), DT);      
    vy = computar_velocidad(vy, -G + potencia * cos(angulo), DT);
    py = computar_posicion(py, vy, DT);
    px = computar_posicion(px, vx, DT);
    dx = vx * DT;
    dy = vy * DT;
    altitude = py + NAVE_GRANDE_TOBERA_Y - obtener_coordenadas_y(terreno, terreno_tam, px);
    
    
    
    // Dibujo los mensajes que brindan la información del juego
    
    for (int i = 0; i < cant_msj_izq; i++) 
      msj_dibujar_izq(msj_izquierda[i], 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_IZQ,
                  MSJ_ALTO * i, 
                  MSJ_INFO_ESPACIO
      );
    
    for (int i = 0 ; i < cant_msj_der; i++) 
      msj_dibujar_izq(msj_derecha[i], 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_DER, 
                  MSJ_ALTO * i, 
                  MSJ_INFO_ESPACIO
      );



    // Dibujo los valores correspondientes cada mensaje
    
    // Valores de los mensajes de la derecha
    for (int i = 0; i < cant_valores_izq; i++)
      valores_dibujar_izq(*valores_izq[i], 
                      MSJ_INFO_ESCALA, 
                      renderer, 
                      VALORES_MARGEN_IZQ, 
                      MSJ_ALTO * 2 * i, 
                      MSJ_INFO_ESPACIO, 
                      MSJ_IZQ_MIN_DIGIT
      );
    
    // Tiempo transcurrido
    tiempo_dibujar(segundos, 
                   MSJ_INFO_ESCALA, 
                   renderer, 
                   VALORES_MARGEN_IZQ, 
                   MSJ_ALTO * 1, 
                   MSJ_INFO_ESPACIO
     );
    
    // Valores de los mensajes de la izquierda
    for (int i = 0; i < cant_valores_der; i++)
      valores_dibujar_der(*valores_der[i], 
                          MSJ_INFO_ESCALA, 
                          renderer, 
                          VALORES_MARGEN_DER, 
                          MSJ_ALTO * i, 
                          MSJ_INFO_ESPACIO, 
                          MSJ_DER_MIN_DIGIT
      );
    


    // Dibujo las flechas dependiendo del sentido de las velocidades
    
    // Izquierda/Derecha
    if (vx < 0)
      msj_dibujar_izq(izquierda, 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_DER + FLECHAS_ESPACIO, 
                  MSJ_ALTO, 
                  MSJ_INFO_ESPACIO
      );
    
    if (vx > 0)
      msj_dibujar_izq(derecha, 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_DER + FLECHAS_ESPACIO, 
                  MSJ_ALTO, 
                  MSJ_INFO_ESPACIO
      );
      
    // Abajo/Arriba
    if (vy < 0)
      msj_dibujar_izq(abajo, 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_DER + FLECHAS_ESPACIO, 
                  MSJ_ALTO * 2, 
                  MSJ_INFO_ESPACIO
      );
    
    if (vy > 0)
      msj_dibujar_izq(arriba, 
                  MSJ_INFO_ESCALA, 
                  renderer, 
                  MSJ_INFO_MARGEN_DER + FLECHAS_ESPACIO, 
                  MSJ_ALTO * 2, 
                  MSJ_INFO_ESPACIO
      );

    
    
    // El mundo es cilíndrico
    
    if (px < 0) 
      px = VENTANA_ANCHO; 
      
    if (px > VENTANA_ANCHO)
      px = 0;    
    
    
    /* Cuando la nave se encuentre en una posición cercana al terreno y con un 
      ángulo poco pronunciado, se desplegarán las patas para el aterrizaje 
      (nave grande), caso contrario se dibujará la nave sin las patas (nave chica) */
    
    
    //ATERRIZAJE
    if (altitude < 50 && fabs(angulo) <= NAVE_ROTACION_PASO) {
      
      nave_aterrizaje = vector_desde_matriz(nave_grande, nave_aterrizaje_tam); 
      
      if (nave_aterrizaje == NULL) {
        vector_destruir(terreno, terreno_tam, CANT_COLS);
        vector_destruir(estrellas, estrellas_tam, CANT_COLS);
        
        return EXIT_FAILURE;
      }
      
    
      chorro_aterrizaje = vector_desde_matriz(chorro_grande, chorro_aterrizaje_tam);
      
      if (chorro_aterrizaje == NULL) {
        vector_destruir(nave_aterrizaje, nave_aterrizaje_tam, CANT_COLS);
        vector_destruir(terreno, terreno_tam, CANT_COLS);
        vector_destruir(estrellas, estrellas_tam, CANT_COLS);
        
        return EXIT_FAILURE;
      }
      
      chorro_aterrizaje[1][1] -= potencia;                     // Representamos la potencia actual en el chorro
      
      // Roto y luego traslado la nave y el chorro a su posicion correspondiente
      vector_rotar(nave_aterrizaje, nave_aterrizaje_tam, angulo);
      vector_trasladar(nave_aterrizaje, nave_aterrizaje_tam, dx, dy);
      vector_rotar(chorro_aterrizaje, chorro_aterrizaje_tam, angulo);
      vector_trasladar(chorro_aterrizaje, chorro_aterrizaje_tam, dx, dy);
      
      // Dibujamos la nave y el chorro
      figura_dibujar(nave_aterrizaje, 
                      FIGURA_ESCALA,
                      renderer, 
                      nave_aterrizaje_tam, 
                      px, 
                      py                      
      );
      
      figura_dibujar(chorro_aterrizaje, 
                      FIGURA_ESCALA,
                      renderer, 
                      chorro_aterrizaje_tam, 
                      px, 
                      py
      );
      
      
      // Liberamos la memoria utilizada
      vector_destruir(nave_aterrizaje, nave_aterrizaje_tam, CANT_COLS);
      vector_destruir(chorro_aterrizaje, chorro_aterrizaje_tam, CANT_COLS);
    }
    
    
    // VUELO
    else {
      nave_vuelo = vector_desde_matriz(nave_chica, nave_vuelo_tam); 
      
      if (nave_vuelo == NULL) {
        vector_destruir(terreno, terreno_tam, CANT_COLS);
        vector_destruir(estrellas, estrellas_tam, CANT_COLS);
          
        return EXIT_FAILURE;
      }
      
        
      chorro_vuelo = vector_desde_matriz(chorro_chico, chorro_vuelo_tam);
      
      if (chorro_chico == NULL) {
        vector_destruir(nave_vuelo, nave_vuelo_tam, CANT_COLS);
        vector_destruir(terreno, terreno_tam, CANT_COLS);
        vector_destruir(estrellas, estrellas_tam, CANT_COLS);
        
        return EXIT_FAILURE;
      }
      
      
      chorro_vuelo[1][1] -= potencia;                     // Representamos la potencia actual en el chorro
      
      // Roto y luego traslado la nave y el chorro a su posicion correspondiente
      vector_rotar(nave_vuelo, nave_vuelo_tam, angulo);
      vector_rotar(chorro_vuelo, chorro_vuelo_tam, angulo);
      vector_trasladar(nave_vuelo, nave_vuelo_tam, dx, dy);
      vector_trasladar(chorro_vuelo, chorro_vuelo_tam, dx, dy);
      
      // Dibujamos la nave y el chorro
      figura_dibujar(nave_vuelo, 
                     FIGURA_ESCALA,
                     renderer, 
                     nave_vuelo_tam, 
                     px, 
                     py
      );
      
      figura_dibujar(chorro_vuelo, 
                     FIGURA_ESCALA,
                     renderer, 
                     chorro_vuelo_tam, 
                     px, 
                     py
      );
      
      // Liberamos la memoria utilizada
      vector_destruir(nave_vuelo, nave_vuelo_tam, CANT_COLS);
      vector_destruir(chorro_vuelo, chorro_vuelo_tam, CANT_COLS);
      
    }
    
    
    // Dibujo el terreno aleatorio generado en la partida junto con la nave y el chorro
    terreno_dibujar(terreno, renderer, terreno_tam);
    estrellas_dibujar(estrellas, renderer, estrellas_tam);

    
    // Mensajes de fin de partida
    if (!vector_esta_arriba(terreno, terreno_tam, px, py + NAVE_GRANDE_TOBERA_Y)) {
      // Buen aterrizaje
      if (fabs(vx) < 1 && fabs(vy) < 10 && fabs(angulo) < 0.01) {
        msj_dibujar_izq(aterrizaje_bueno, 
                    MSJ_ATERRIZAJE_ESCALA, 
                    renderer, 
                    MSJ_FIN_PARTIDA_MARGEN, 
                    MSJ_FIN_PARTIDA_ALTO, 
                    MSJ_ATERRIZAJE_ESPACIO * 2
        );
        score += 50;
      }
      
      else {
        // Aterrizaje violento
        if (fabs(vx) < 2 && fabs(vy) < 20 && fabs(angulo) < 0.01) {
          msj_dibujar_izq(aterrizaje_violento, 
                      MSJ_ATERRIZAJE_ESCALA, 
                      renderer, 
                      MSJ_FIN_PARTIDA_MARGEN, 
                      MSJ_FIN_PARTIDA_ALTO, 
                      MSJ_ATERRIZAJE_ESPACIO * 2
          );
          score += 15;
        }
        
        else {
          // Destrucción
          msj_dibujar_izq(destruccion, 
                      MSJ_DESTR_ESCALA, 
                      renderer, 
                      MSJ_FIN_PARTIDA_MARGEN * 1.5, 
                      MSJ_FIN_PARTIDA_ALTO, 
                      MSJ_DESTR_ESPACIO * 2
          );
          score += 5;
          fuel -= 250;
        }
      }
      
      
      // Establezco la pausa correspondiente al final de la partida
      dormir = 1000;
      
      // Condiciones iniciales para el inicio de una nueva partida
      px = NAVE_X_INICIAL;
      py = NAVE_Y_INICIAL;
      vx = NAVE_VX_INICIAL;
      vy = NAVE_VY_INICIAL;
      angulo = NAVE_ANGULO_INICIAL;
      potencia = NAVE_POTENCIA_INICIAL;
      
      vector_destruir(terreno, terreno_tam, CANT_COLS);
      terreno = terreno_crear(&terreno_tam);
      estrellas = estrellas_crear(terreno, terreno_tam, &estrellas_tam);
    }
    
    
    // Condición del fin del juego
    if (fuel <= 0)       
      break;
  

		// END código del alumno

        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
    
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else 
      if(ticks < 1000 / JUEGO_FPS)
        SDL_Delay(1000 / JUEGO_FPS - ticks);
		
    ticks = SDL_GetTicks();
	}


	// BEGIN código del alumno
  
   // Doy la información del puntaje obtenido por stdout
   printf("\nGAME OVER\n\nSCORE: %0.f\n\n", score);
  
   // Destruyo los vectores dinámicos utilizados
   vector_destruir(terreno, terreno_tam, CANT_COLS);
   vector_destruir(estrellas, estrellas_tam, CANT_COLS);
    
	// END código del alumno


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
   
	return 0;
}

