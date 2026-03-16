// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo selector_factory_algoritmo.h: fichero de declaración.
// Contiene la declaración de la clase SelectorFactoryAlgoritmo.

#ifndef SELECTOR_FACTORY_ALGORITMO_H_
#define SELECTOR_FACTORY_ALGORITMO_H_

#include "factory_algoritmos_planificacion.h"

class SelectorFactoryAlgoritmo {
 public:
  FactoryAlgoritmosPlanificacion* Seleccionar(const json& config);
};

#endif