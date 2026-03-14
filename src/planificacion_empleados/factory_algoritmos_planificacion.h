// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 14/03/2026
// Archivo factory_algoritmo_planificacion.h: fichero de declaración.
// Contiene la declaración de la clase FactoryAlgoritmosPlanificacion.

#ifndef FACTORY_ALGORIMTO_PLANIFICACION_H_
#define FACTORY_ALGORIMTO_PLANIFICACION_H_

#include "../lib/algoritmo.h"

class FactoryAlgoritmosPlanificacion {
 public:
  virtual ~FactoryAlgoritmosPlanificacion() = default;

  virtual Algoritmo* GenerarAlgoritmoPlanificacion() = 0;
};

#endif