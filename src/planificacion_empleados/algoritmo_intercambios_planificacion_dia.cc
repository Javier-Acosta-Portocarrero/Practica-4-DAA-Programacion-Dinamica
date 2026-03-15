// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 15/03/2026
// Archivo algoritmo_intercambios_planificacion_dia.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoIntercambiosPlanificacionDia.


#include "../lib/algoritmo.h"
#include "algoritmo_intercambios_planificacion_dia.h"

#include <limits>
#include <stdexcept>
#include <iostream>

Solucion* AlgoritmoIntercambiosPlanificacionDia::Solve(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  if (entrada_procesada->GetCantidadDias() > 1) {
    throw std::logic_error("Este algoritmo solo se puede usar para instancias de tamaño 1.");
  }

  SolucionPlanificacionEmpleados* solucion_dia = new SolucionPlanificacionEmpleados(*entrada_procesada);
  size_t cantidad_turnos = solucion_dia->GetCantidadTurnos();
  // Primera pasada para cubrir empleados mínimos por turno.
  for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
    const unsigned minimo_empleados{solucion_dia->GetMinimoEmpleados(0, turno)};
    while (solucion_dia->EmpleadosTurno(0, turno) < minimo_empleados) {
      int mejor_empleado_disponible{EncontrarMejorEmpleadoDisponible(solucion_dia, 0, turno)};
      if (mejor_empleado_disponible == -1) {
        break;
      }
      solucion_dia->NuevoTrabajoTurno(0, turno, static_cast<size_t>(mejor_empleado_disponible));
    }
  }

  // Segunda pasada, asignación voraz de empleados restantes maximizando satisfacción y
  // empleados por turno.
  std::vector<bool> turno_completado(cantidad_turnos, false);
  unsigned turnos_completados{0};
  while (turnos_completados < cantidad_turnos) {
    for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
      if (turno_completado[turno]) {
        continue;
      }
      int mejor_empleado_disponible = EncontrarMejorEmpleadoDisponible(solucion_dia, 0, turno);
      // Si no hay más empleados disponibles para este turno lo marcamos como completado.
      if (mejor_empleado_disponible == -1) {
        turno_completado[turno] = true;
        ++turnos_completados;
        continue;
      }
      // Si la satisfacción es negativa no compensa asignarlo.
      if (solucion_dia->GetSatisfaccion(mejor_empleado_disponible, 0, turno) < 0) {
        turno_completado[turno] = true;
        ++turnos_completados;
        continue;
      }
      solucion_dia->NuevoTrabajoTurno(0, turno, static_cast<size_t>(mejor_empleado_disponible));
    }
  }

  // Fase de mejora mediante intercambios entre empleados.
  MejorarPorIntercambios(solucion_dia, 0);

  return solucion_dia;
}

int AlgoritmoIntercambiosPlanificacionDia::EncontrarMejorEmpleadoDisponible(
    SolucionPlanificacionEmpleados* solucion,
    size_t dia,
    size_t turno) {

  int satisfaccion_mejor_empleado_disponible{std::numeric_limits<int>::min()};
  // Si al final sigue siendo -1 significa que no había ningún empleado disponible.
  int mejor_empleado_disponible{-1};
  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  for (size_t empleado{0}; empleado < cantidad_empleados; ++empleado) {
    if (!solucion->TrabajaEmpleadoDia(empleado, dia) &&
        solucion->GetSatisfaccion(empleado, dia, turno) > satisfaccion_mejor_empleado_disponible) {

      satisfaccion_mejor_empleado_disponible = solucion->GetSatisfaccion(empleado, dia, turno);
      mejor_empleado_disponible = empleado;
    }
  }

  return mejor_empleado_disponible;
}

void AlgoritmoIntercambiosPlanificacionDia::MejorarPorIntercambios(
    SolucionPlanificacionEmpleados* solucion,
    size_t dia) {

  bool mejora{true};
  size_t cantidad_turnos = solucion->GetCantidadTurnos();
  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  // Repetimos mientras sigan encontrándose mejoras en la planificación.
  while (mejora) {
    mejora = false;
    // Recorremos todos los pares de turnos posibles.
    for (size_t turno_i{0}; turno_i < cantidad_turnos; ++turno_i) {
      for (size_t turno_j{0}; turno_j < cantidad_turnos; ++turno_j) {
        // Probamos todos los empleados que trabajan en el turno_i.
        for (size_t empleado_a{0}; empleado_a < cantidad_empleados; ++empleado_a) {
          if (!solucion->TrabajaEmpleadoDiaTurno(empleado_a, dia, turno_i)) {
            continue;
          }
          // Probamos ahora todos los empleados que trabajan en el turno_j.
          for (size_t empleado_b{0}; empleado_b < cantidad_empleados; ++empleado_b) {
            if (!solucion->TrabajaEmpleadoDiaTurno(empleado_b, dia, turno_j)) {
              continue;
            }
            // Calculamos la satisfacción actual de ambos empleados con sus turnos actuales.
            int satisfaccion_actual =
                solucion->GetSatisfaccion(empleado_a, dia, turno_i) +
                solucion->GetSatisfaccion(empleado_b, dia, turno_j);
            // Calculamos la satisfacción que tendrían si intercambiamos los turnos.
            int satisfaccion_intercambio =
                solucion->GetSatisfaccion(empleado_a, dia, turno_j) +
                solucion->GetSatisfaccion(empleado_b, dia, turno_i);
            // Si el intercambio mejora la satisfacción total realizamos el cambio.
            if (satisfaccion_intercambio > satisfaccion_actual) {
              solucion->LiberarTrabajoTurno(dia, turno_i, empleado_a);
              solucion->LiberarTrabajoTurno(dia, turno_j, empleado_b);
              solucion->NuevoTrabajoTurno(dia, turno_j, empleado_a);
              solucion->NuevoTrabajoTurno(dia, turno_i, empleado_b);
              // Indicamos que se ha producido una mejora para seguir iterando.
              mejora = true;
            }
          }
        }
      }
    }
  }
}