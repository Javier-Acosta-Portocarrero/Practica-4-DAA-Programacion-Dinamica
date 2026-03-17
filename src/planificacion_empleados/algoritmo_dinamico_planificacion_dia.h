// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 17/03/2026
// Archivo algoritmo_voraz_planificacion_dia.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoVorazPlanificacionDia.

#ifndef ALGORITMO_DINAMICO_PLANIFICACION_DIA_H_
#define ALGORITMO_DINAMICO_PLANIFICACION_DIA_H_

#include "../lib/algoritmo.h"
#include "solucion_planificacion_empleados.h"

class AlgoritmoDinamicoPlanificacionDia : public Algoritmo {
 public:
  Solucion* Solve(Instancia* entrada) override;
 private:
  std::vector<std::vector<int>> ConstruirTablaDinamica(SolucionPlanificacionEmpleados* const solucion);
  unsigned EncontrarCantidadSlots(SolucionPlanificacionEmpleados* const  solucion);
  unsigned TraducirSlotTurno(unsigned slot, SolucionPlanificacionEmpleados* const solucion);
  void ReconstuirSolucion(const std::vector<std::vector<int>>& tabla, SolucionPlanificacionEmpleados* solucion);
};

#endif