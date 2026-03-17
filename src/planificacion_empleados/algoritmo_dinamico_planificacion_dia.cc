// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 17/03/2026
// Archivo algoritmo_voraz_planificacion_dia.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoVorazPlanificacionDia.


#include "../lib/algoritmo.h"
#include "algoritmo_dinamico_planificacion_dia.h"

#include <limits>
#include <stdexcept>
#include <iostream>

Solucion* AlgoritmoDinamicoPlanificacionDia::Solve(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  if (entrada_procesada->GetCantidadDias() > 1) {
    throw std::logic_error("Este algoritmo solo se puede usar para instancias de tamaño 1.");
  }
  SolucionPlanificacionEmpleados* solucion_dia = new SolucionPlanificacionEmpleados(*entrada_procesada);
  size_t cantidad_empleados = solucion_dia->GetCantidadEmpleados();
  size_t cantidad_turnos = solucion_dia->GetCantidadTurnos();

  unsigned slots = EncontrarCantidadSlots(solucion_dia);
  std::vector<std::vector<int>> tabla_dinamica{ConstruirTablaDinamica(solucion_dia)};
  ReconstuirSolucion(tabla_dinamica, solucion_dia);

  return solucion_dia;  
}

std::vector<std::vector<int>> AlgoritmoDinamicoPlanificacionDia::ConstruirTablaDinamica(
    SolucionPlanificacionEmpleados* const solucion) {

  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  unsigned slots = EncontrarCantidadSlots(solucion);
  std::vector<std::vector<int>> tabla_dinamica(cantidad_empleados + 1, std::vector<int>(slots + 1, 0));
  for (size_t empleados{0}; empleados < cantidad_empleados + 1; ++empleados) {
    for (unsigned slot{0}; slot <= slots; ++slot) {
      // Caso base, no hay empleados o slots
      if (empleados == 0 || slot == 0) {
        tabla_dinamica[empleados][slot] = 0;
      } else {
        unsigned turno_slot = TraducirSlotTurno(slot - 1, solucion);
        const int satisfaccion_empleado = solucion->GetSatisfaccion(empleados - 1, 0, turno_slot);
        tabla_dinamica[empleados][slot] = std::max(
            tabla_dinamica[empleados - 1][slot], 
            tabla_dinamica[empleados - 1][slot - 1] + satisfaccion_empleado);
      }
    }
  }
  
  return tabla_dinamica;
}

unsigned AlgoritmoDinamicoPlanificacionDia::EncontrarCantidadSlots(SolucionPlanificacionEmpleados* const solucion) {
  int cantidad_slots{0};
  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  size_t cantidad_turnos = solucion->GetCantidadTurnos();
  for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
    const unsigned minimo_empleados{solucion->GetMinimoEmpleados(0, turno)};
    cantidad_slots += minimo_empleados;
  }
  return cantidad_slots;
}

unsigned AlgoritmoDinamicoPlanificacionDia::TraducirSlotTurno(
     unsigned slot, 
     SolucionPlanificacionEmpleados* const solucion) {

  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  size_t cantidad_turnos = solucion->GetCantidadTurnos();
  unsigned acumulado_empleados{0};
  for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
    const unsigned minimo_empleados{solucion->GetMinimoEmpleados(0, turno)};
    if (slot < acumulado_empleados + minimo_empleados) {
      return turno;
    }
    acumulado_empleados += minimo_empleados;
  }
  
  // En caso de que el slot sea mayor al acumulado, se asigna al último turno
  return cantidad_turnos - 1; 
}

void AlgoritmoDinamicoPlanificacionDia::ReconstuirSolucion(
    const std::vector<std::vector<int>>& tabla, 
    SolucionPlanificacionEmpleados* solucion) {

  size_t cantidad_empleados_actual = tabla.size() - 1;
  size_t slot_actual = tabla[0].size() - 1;
  // Se parte de la solución final y se va determinando qué empleado se asignó a cada slot.
  while (cantidad_empleados_actual > 0 && slot_actual > 0) {
    if (tabla[cantidad_empleados_actual][slot_actual] != tabla[cantidad_empleados_actual - 1][slot_actual]) {
      unsigned turno_slot = TraducirSlotTurno(slot_actual - 1, solucion);
      solucion->NuevoTrabajoTurno(0, turno_slot, cantidad_empleados_actual - 1);
      --slot_actual;
    }
    --cantidad_empleados_actual;
  }
}