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

void vector_copiar(float **v, float **vRand, size_t nv){
  
            //Funcion copiar vector en densificar
  }
  


float **vector_densificar(float **v, size_t nv, size_t nn, float margen) {
  float **vDensif = NULL;
  
  if ((vDensif = vector_asignar_memoria(nn, CANT_COLS)) == NULL) 
    return NULL;
  
  for(int i = 0; i < nv; i++) {
    vDensif[i][0] = v[i][0];
    vDensif[i][1] = v[i][1];  
  }
    
  generar_coordenadas_random(v, vDensif, nv, nn, margen);
  
  vector_ordenar(vDensif, nn);
  
  return vDensif;
}

  
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


char *itoa(int num, char *cadena, int base, int min_digit) {
    int i = 0, resto = 0; 
    
    if (num < 0)
      num = -num;
    
    // Evaluamos específicamente el 0
    if (num == 0) { 
      cadena[i] = '0';
      i++; 
      
      for (; i < min_digit; i++)
        cadena[i] = '0'; 
      
      cadena[i] = '\0'; 
       
      return cadena; 
    } 
  
    for (; num != 0; i++) { 
      resto = num % base; 
      cadena[i] = resto + '0'; 
      num = num / base; 
    } 
    
    for (; i < min_digit; i++)
      cadena[i] = '0';
    
    cadena[i] = '\0';               // Terminador de la cadena
  
    // Damos vuelta la cadena 
    invertir_cadena(cadena, i); 
  
    return cadena; 
} 





