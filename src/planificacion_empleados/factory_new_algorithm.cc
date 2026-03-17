// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_divide_y_venceras.cc: fichero de definición.
// Contiene la definición de la clase FactoryDivideYVenceras.

#include "factory_new_algorithm.h"
#include "selector_factory_algoritmo.h"
#include "new-algorithm.h"

FactoryNewAlgorithm::FactoryNewAlgorithm (SelectorFactoryAlgoritmo* selector)
    : selector_(selector) {}

Algoritmo* FactoryNewAlgorithm::Crear(const json& config) {


  const json& initial_solver = config["initialSolver"];

  FactoryAlgoritmosPlanificacion* factory = selector_->Seleccionar(initial_solver);
  Algoritmo* algoritmo_inicial = factory->Crear(initial_solver);

  delete factory;

  return new NewAlgorithm(algoritmo_inicial);
}