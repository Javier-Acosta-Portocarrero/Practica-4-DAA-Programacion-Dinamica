// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 28/02/2024
// Archivo algoritmo.h: fichero de declaración.
// Contiene la declaración de la clase Algoritmo.

#ifndef ALGORITMO_H_
#define ALGORITMO_H_

#include "instancia.h"
#include "solucion.h"

/**
  * @class Algoritmo
  * 
  * @brief Clase abstracta interfaz de los algoritmos, los cuales reciben como
  *        entrada una instancia y dan como salida una solución. También sigue
  *        el patrón estrategia.  
  */
class Algoritmo {
 public:

  virtual ~Algoritmo() = default; 
 /**
   * @brief Método virtual puro para resolver cualquier tipo de algoritmo
   *
   * @param entrada Puntero a cualquier instancia posible que pueda recibir un algoritmo
   * @return Un puntero a la solución del problema para esa instancia concreta,
   *         puede ser cualquier tipo de solución que pueda devolver un algoritmo.
   */
  virtual Solucion* Solve(Instancia* entrada) = 0;
};

#endif