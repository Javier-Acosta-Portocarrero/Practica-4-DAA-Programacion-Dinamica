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

#include "factory_divide_y_venceras.h"
#include "selector_factory_algoritmo.h"
#include "algoritmo_aproximado_planificacion.h"

FactoryDivideYVenceras::FactoryDivideYVenceras(SelectorFactoryAlgoritmo* selector)
    : selector_(selector) {}

Algoritmo* FactoryDivideYVenceras::Crear(const json& config) {

  unsigned small_size = 1;
  if (config.contains("smallSize"))
    small_size = config["smallSize"].get<unsigned>();

  unsigned divisiones = 2;
  if (config.contains("divisions"))
    divisiones = config["divisions"].get<unsigned>();

  const json& small_solver = config["smallSolver"];

  FactoryAlgoritmosPlanificacion* factory = selector_->Seleccionar(small_solver);
  Algoritmo* algoritmo_pequeno = factory->Crear(small_solver);

  delete factory;

  return new AlgoritmoAproximadoPlanificacion(
      algoritmo_pequeno,
      small_size,
      divisiones);
}