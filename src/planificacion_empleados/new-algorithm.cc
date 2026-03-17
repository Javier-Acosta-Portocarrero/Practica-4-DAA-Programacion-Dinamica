// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo algoritmo_voraz_planificacion_dia.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoVorazPlanificacionDia.


#include "../lib/algoritmo.h"
#include "new-algorithm.h"

#include <limits>
#include <stdexcept>
#include <iostream>
#include <random>

Solucion* NewAlgorithm::Solve(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);

  SolucionPlanificacionEmpleados* solucion_inicial = dynamic_cast<SolucionPlanificacionEmpleados*>(   
      algoritmo_inicial_->Solve(entrada_procesada));

  SolucionPlanificacionEmpleados* solucion_final = MejorarPorIntercambios(solucion_inicial);

  return solucion_final;  
}

SolucionPlanificacionEmpleados* NewAlgorithm::MejorarPorIntercambios(SolucionPlanificacionEmpleados* solucion) {
  SolucionPlanificacionEmpleados* solucion_nueva = new SolucionPlanificacionEmpleados(*solucion);
  unsigned cantidad_dia = solucion->GetCantidadDias();
  unsigned cantidad_turnos = solucion->GetCantidadTurnos();
  unsigned cantidad_empleado = solucion->GetCantidadEmpleados();

  for (int iteraciones{0}; iteraciones < 100; ++iteraciones) {
    unsigned dia = std::rand() % cantidad_dia;
    unsigned turno_a = std::rand() % cantidad_turnos;
    unsigned turno_b = std::rand() % cantidad_turnos;
    unsigned empleado_a = std::rand() % cantidad_empleado;
    unsigned empleado_b = std::rand() % cantidad_empleado;

    if (solucion_nueva->TrabajaEmpleadoDiaTurno(empleado_a, dia, turno_a) &&
        solucion_nueva->TrabajaEmpleadoDiaTurno(empleado_b, dia, turno_b)) {
      solucion_nueva->LiberarTrabajoTurno(dia, turno_a, empleado_a);
      solucion_nueva->LiberarTrabajoTurno(dia, turno_b, empleado_b);
      solucion_nueva->NuevoTrabajoTurno(dia, turno_a, empleado_b);
      solucion_nueva->NuevoTrabajoTurno(dia, turno_b, empleado_a);
    }
  } 
  
  if (solucion_nueva->GetValorObjetivo() > solucion->GetValorObjetivo()) {
    return solucion_nueva;
  }

  delete solucion_nueva;
  return solucion;
}