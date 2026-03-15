// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Fecha: 15/03/2026
// Archivo algoritmo_intercambios_planificacion_dia.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoIntercambiosPlanificacionDia.

#ifndef ALGORITMO_INTERCAMBIOS_PLANIFICACION_DIA_H_
#define ALGORITMO_INTERCAMBIOS_PLANIFICACION_DIA_H_

#include "../lib/algoritmo.h"
#include "solucion_planificacion_empleados.h"

class AlgoritmoIntercambiosPlanificacionDia : public Algoritmo {
 public:
  Solucion* Solve(Instancia* entrada) override;

 private:
  int EncontrarMejorEmpleadoDisponible(SolucionPlanificacionEmpleados* solucion, size_t dia, size_t turno);
  void MejorarPorIntercambios(SolucionPlanificacionEmpleados* solucion, size_t dia);
};

#endif