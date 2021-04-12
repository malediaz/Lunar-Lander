#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

typedef const int (*vectores_t)[2];

const int caracter_estrella[16][2];
char opciones_caracteres[42];
size_t longitud_cadena[42];
size_t cantidad_caracteres;

/* Recibe un caracter y devuelve la el vector de coordenadas
  que lo representa */
vectores_t conversion_a_vector(char caracter);

/* Recibe un caracter y devuelve el numero de coordenadas
  que contiene el vector que lo representa */
size_t conversion_a_longitud(char caracter);


#endif // _DICCIONARIO_H_
