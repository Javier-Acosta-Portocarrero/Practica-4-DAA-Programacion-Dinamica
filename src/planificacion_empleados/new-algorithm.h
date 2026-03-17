// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Fecha: 15/03/2026
// Archivo algoritmo_intercambios_planificacion_dia.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoIntercambiosPlanificacionDia.

#ifndef NEW_ALGORITHM_H_
#define NEW_ALGORITHM_H_

#include "../lib/algoritmo.h"
#include "solucion_planificacion_empleados.h"

class NewAlgorithm : public Algoritmo {
 public:
  NewAlgorithm(Algoritmo* algoritmo_inicial) : algoritmo_inicial_{algoritmo_inicial} {} 
  ~NewAlgorithm() { delete algoritmo_inicial_;}

  Solucion* Solve(Instancia* entrada) override;

 private:
  Algoritmo* algoritmo_inicial_ = nullptr;

  SolucionPlanificacionEmpleados* MejorarPorIntercambios(SolucionPlanificacionEmpleados* solucion);
};

#endif