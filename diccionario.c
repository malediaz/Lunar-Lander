#include <stdio.h>

#include "caracteres.h"
#include "diccionario.h"


enum def_caracteres {
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V,
  W, X, Y, Z, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, DERECHA, 
  IZQUIERDA, ARRIBA, ABAJO, ESPACIO, ESTRELLA};
  
  
const int caracter_estrella[16][2] = {
  {0, 3},
  {0, 0},
  {1, 1},
  {0, 0},
  {2, 0},
  {0, 0},
  {1, -1},
  {0, 0},
  {0, -3},
  {0, 0},
  {-1, -1},
  {0, 0},
  {-2, 0},
  {0, 0},
  {-1, 1},
  {0, 0}
};
  
char opciones_caracteres[] = {
  [A] = 'A', [B] = 'B', [C] = 'C', [D] = 'D',
  [E] = 'E', [F] = 'F', [G] = 'G', [H] = 'H',
  [I] = 'I', [J] = 'J', [K] = 'K', [L] = 'L',
  [M] = 'M', [N] = 'N', [O] = 'O', [P] = 'P',
  [Q] = 'Q', [R] = 'R', [S] = 'S', [T] = 'T',
  [U] = 'U', [V] = 'V', [W] = 'W', [X] = 'X',
  [Y] = 'Y', [Z] = 'Z', [N0] = '0', [N1] ='1',
  [N2] = '2', [N3] = '3', [N4] = '4', [N5] = '5',
  [N6] = '6', [N7] = '7', [N8] = '8', [N9] = '9',
  [DERECHA] = '>', [IZQUIERDA] = '<',
  [ARRIBA] = '^', [ABAJO] = 'v', [ESPACIO] = ' ',
  [ESTRELLA] = '*'
};

vectores_t opciones_vectores[] = {
  [A] = caracter_a, [B] = caracter_b, [C] = caracter_c,
  [D] = caracter_d, [E] = caracter_e, [F] = caracter_f,
  [G] = caracter_g, [H] = caracter_h, [I] = caracter_i,
  [J] = caracter_j, [K] = caracter_k, [L] = caracter_l,
  [M] = caracter_m, [N] = caracter_n, [O] = caracter_o,
  [P] = caracter_p, [Q] = caracter_q, [R] = caracter_r,
  [S] = caracter_s, [T] = caracter_t, [U] = caracter_u,
  [V] = caracter_v, [W] = caracter_w, [X] = caracter_x,
  [Y] = caracter_y, [Z] = caracter_z, [N0] = caracter_0,
  [N1] = caracter_1, [N2] = caracter_2, [N3] = caracter_3,
  [N4] = caracter_4, [N5] = caracter_5, [N6] = caracter_6,
  [N7] = caracter_7, [N8] = caracter_8, [N9] = caracter_9,
  [DERECHA] = caracter_derecha, [IZQUIERDA] = caracter_izquierda,
  [ARRIBA] = caracter_arriba, [ABAJO] = caracter_abajo,
  [ESPACIO] = caracter_espacio, [ESTRELLA] = caracter_estrella
};


size_t longitud_cadena[] = {
  [A] = 7, [B] = 12, [C] = 4, [D] = 7, [E] = 7, [F] = 6, [G] = 7,
  [H] = 6, [I] = 6, [J] = 4, [K] = 6, [L] = 3, [M] = 5, [N] = 4,
  [O] = 5, [P] = 5, [Q] = 9, [R] = 7, [S] = 6, [T] = 4, [U] = 4,
  [V] = 3, [W] = 5, [X] = 5, [Y] = 5, [Z] = 4, [N0] = 5, [N1] = 2,
  [N2] = 6, [N3] = 7, [N4] = 5, [N5] = 6, [N6] = 5, [N7] = 3,
  [N8] = 7, [N9] = 5, [DERECHA] = 5, [IZQUIERDA] = 5, 
  [ARRIBA] = 5, [ABAJO] = 5, [ESPACIO] = 1, [ESTRELLA] = 16
};

size_t cantidad_caracteres = sizeof(opciones_caracteres) / sizeof(opciones_caracteres[0]);


vectores_t conversion_a_vector(char caracter) {
  // Iteramos hasta encontrar el mismo caracter en opciones_caracteres
  for (size_t i = 0; i < cantidad_caracteres; i++) {
    if (opciones_caracteres[i] == caracter) 
      
      return opciones_vectores[i];
  }
  
  return NULL;
}

size_t conversion_a_longitud(char caracter) {
  // Iteramos hasta encontrar el mismo caracter en opciones_caracteres
  for (size_t i = 0; i < cantidad_caracteres;i++) {
      if (opciones_caracteres[i] == caracter)
        
        return longitud_cadena[i];
  }
  
  return 1;
}
  


