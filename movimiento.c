#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "movimiento.h"

double computar_velocidad(double vi ,double a ,double dt) {
  return vi + a * dt;
}

double computar_posicion(double pi, double vi ,double dt) {
  return pi + vi * dt; 
}

bool vector_esta_arriba(float **v, size_t n, float x, float y) {
  for (int i = 1; i < n; i++) {
    if (x >= v[i - 1][0] && x <= v[i][0]) {
      float x0 = v[i - 1][0], x1 = v[i][0];
      float y0 = v[i - 1][1], y1 = v[i][1];

      if (y > ((y1 - y0) / (x1 - x0)) * (x - x0) + y0)
        return true;

    return false;
    }
  }

  return false;
}


void vector_trasladar(float **v, size_t n, float dx, float dy) {
  for (int i = 0; i < n; i++) {
    v[i][0] += dx;
    v[i][1] += dy;
  }
}

void vector_rotar(float **v, size_t n, double rad) {
  float coseno = cos(rad), seno = sin(rad);
  float x, y;

  for (int i = 0; i < n; i++) {
    x = v[i][0] * coseno - v[i][1] * seno;
    y = v[i][0] * seno + v[i][1] * coseno;

    v[i][0] = x;
    v[i][1] = y;
    }
}


