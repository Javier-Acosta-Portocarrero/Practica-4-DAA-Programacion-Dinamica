// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo algoritmo_voraz_planificacion_dia.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoVorazPlanificacionDia.

#ifndef ALGORITMO_VORAZ_PLANIFICACION_DIA_H_
#define ALGORITMO_VORAZ_PLANIFICACION_DIA_H_

#include "../lib/algoritmo.h"
#include "solucion_planificacion_empleados.h"

class AlgoritmoVorazPlanificacionDia : public Algoritmo {
 public:
  Solucion* Solve(Instancia* entrada) override;
 private:
  int EncontrarMejorEmpleadoDisponible(SolucionPlanificacionEmpleados* solucion, size_t dia, size_t turno);
};

#endif