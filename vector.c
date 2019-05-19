#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"
#include "terreno.h"

#define CANT_COLS 2


void vector_destruir(float **v ,size_t n ,size_t m) {
  for (int j = 0; j < n; j++)
      free(v[j]);
  
  free(v);
  v = NULL;                                    
}


/*Función auxiliar para la asignación de memoria de un vector dinámico de nCoordx2 que recibe 
  el vector, el número de elementos que tendrá y un mensaje a imprimir para especificar cuál 
  va a ser el vector a crear, y devuelve un puntero al primer elemento de dicho vector dinámico. 
  Precondición: el vector no debe tener un espacio de memoria asigndo previamente*/

float **vector_asignar_memoria(size_t n, size_t m) {
  float **v = malloc(sizeof(float *) * n);

  if (v == NULL)
    return NULL;
  
  for (int i = 0; i < n; i++) {
    v[i] = malloc(sizeof(float) * m);
     
    if (v[i] == NULL) {
      vector_destruir(v, i, m);
      
      return NULL;
    }
  }
  
  return v;
}



float **vector_desde_matriz(const float m[][2], size_t n) {
  float **v = NULL;

  if ((v = vector_asignar_memoria(n, CANT_COLS)) == NULL)
    return NULL;
   
  for (int i = 0; i < n; i++) { 
    for(int j = 0; j < CANT_COLS; j++)
      v[i][j] = m[i][j];
  }
  
  return v;
}

// Función que intercambia las direcciones de memoria de dos punteros entre sí

void swap_coordenadas(float **v0, float **v1) { 
  float *auxiliar = NULL;

    auxiliar = *v1; 
    *v1 = *v0;
    *v0 = auxiliar;  
}

void swap_elementos(char *elemento0, char *elemento1) { 
  char auxiliar;

    auxiliar = *elemento1; 
    *elemento1 = *elemento0;
    *elemento0 = auxiliar;  
}


/* Función auxiliar que recibe un vector y su número de elementos y lo ordena 
   en forma creciente con respecto a sus coordenadas en x */
   
void vector_ordenar(float **v, size_t nn) {
    int i, j;
    
    for (i = 0; i < (nn - 1); i++) { 
      for (j = i + 1; j < nn; j++) { 
        if (v[j][0] < v[i][0]) { 
          swap_coordenadas(&v[i], &v[j]);
      } 
    }
  } 
}



char *invertir_cadena(char *cadena, int cadena_tam) { 
  // Establecemos las cotas superioires e inferiores
  int inf = 0;   
  int sup = cadena_tam - 1; 
  
  while (inf < sup) { 
    swap_elementos(&cadena[inf], &cadena[sup]); 
    inf++; 
    sup--; 
  } 
  
  return cadena;
} 


/* Función que recibe un número de como máximo 4 dígitos y lo convierte en una cadena de caracteres
  de 4 elementos.
  Precondición: el número debe ser positivo, en caso de ser negativo, la función
  lo imprimirá como positivo.*/

char *itoa(int num, char *cadena, int base, int min_digit) {
    int i = 0, resto = 0; 
    
    if (num < 0)
      num = -num;
    
    // Evaluamos específicamente el 0
    if (num == 0) { 
      for (; i < min_digit; i++)
      cadena[i] = '0'; 
      
      cadena[i + 1] = '\0'; 
       
      return cadena; 
    } 
  
    while (num != 0) { 
      resto = num % base; 
      cadena[i] = resto + '0'; 
      num = num / base; 
      i++;
    } 
    
    for (; i < min_digit; i++)
      cadena[i] = '0';
    
    cadena[i] = '\0';               // Terminador de la cadena
  
    // Damos vuelta la cadena 
    invertir_cadena(cadena, i); 
  
    return cadena; 
} 





