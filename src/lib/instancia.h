// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 28/02/2024
// Archivo instancia.h: fichero de declaración.
// Contiene la declaración de la clase Instanca.

#ifndef INSTANCIA_H_
#define INSTANCIA_H_

/**
  * @class Instancia
  * 
  * @brief Clase abstracta interfaz de las instancias que reciben los algoritmos,
  *        así siguiendo el patrón estrategia.  
  */
class Instancia {
 public:
  virtual ~Instancia() = default;
};

#endif