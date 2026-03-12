// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 28/02/2024
// Archivo solucion.h: fichero de declaración.
// Contiene la declaración de la clase Solucion.

#ifndef SOLUCION_H_
#define SOLUCION_H_

/**
  * @class Solucion
  * 
  * @brief Clase abstracta interfaz de las soluciones que generan los algoritmos,
  *        así siguiendo el patrón estrategia.  
  */
class Solucion {
 public:
  virtual ~Solucion() = default;
};

#endif