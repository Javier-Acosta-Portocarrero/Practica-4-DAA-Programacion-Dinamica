// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo algoritmo_divide_y_venceras.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoDivideYVenceras.

#ifndef ALGORITMO_DIVIDE_Y_VENCERAS_H_
#define ALGORITMO_DIVIDE_Y_VENCERAS_H_

#include "algoritmo.h"
#include <vector>

/**
  * @class AlgoritmoDivideYVenceras
  * 
  * @brief Clase abstracta que implementa, de forma general,  
  *        un algoritmo de divide y vencerás, hereda de la clase Algoritmo.
  */
class AlgoritmoDivideYVenceras : public Algoritmo {
 public:
  virtual ~AlgoritmoDivideYVenceras() = default;
  
  /**
   * @brief Método que implementa el algoritmo de divide y vencerás, recibe una instancia y devuelve una solución.
   *
   * @param entrada Puntero a cualquier instancia posible que pueda recibir un algoritmo
   * @return Un puntero a la solución del problema para esa instancia concreta,
   *         puede ser cualquier tipo de solución que pueda devolver un algoritmo.
   */
  Solucion* Solve(Instancia* entrada) override;

 protected:
  /**
   * @brief Método virtual puro para dividir la instancia en subinstancias.
   *
   * @param entrada Puntero a la instancia que se va a dividir.
   * @return Un vector de punteros a las subinstancias resultantes de la división.
   */
  virtual std::vector<Instancia*> Divide(Instancia* entrada) = 0;
  
  /**
   * @brief Método virtual puro para combinar las soluciones de las subinstancias.
   *
   * @param soluciones Un vector de punteros a las soluciones de las subinstancias.
   * @return Un puntero a la solución combinada resultante de la combinación de las soluciones de las subinstancias.
   */
  virtual Solucion* Combine(std::vector<Solucion*> soluciones) = 0;

  /**
   * @brief Método virtual puro para resolver la instancia cuando es lo suficientemente pequeña.
   *
   * @param entrada Puntero a la instancia que se va a resolver.
   * @return Un puntero a la solución de la instancia pequeña.
   */
  virtual Solucion* SolveSmall(Instancia* entrada) = 0;

  /**
   * @brief Método virtual puro para determinar si la instancia es lo suficientemente pequeña 
   *        para ser resuelta directamente.
   *
   * @param entrada Puntero a la instancia que se va a evaluar.
   * @return Un valor booleano que indica si la instancia es lo suficientemente pequeña para ser 
   *         resuelta directamente.
   */
  virtual bool IsSmall(Instancia* entrada) = 0;
};

#endif