// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 14/03/2026
// Archivo generador_instancias_planificacion.h: fichero de declaración.
// Contiene la declaración de la clase FactoryAlgoritmosPlanificacion.

#include "generador_instancias_planificacion.h"
#include <random>

#include "generador_instancias_planificacion.h"
#include <cstdlib>

InstanciaPlanificacionEmpleados* GeneradorInstanciasPlanificacion::GenerarInstancia(
    size_t empleados, 
    size_t dias, 
    size_t turnos) {

  std::vector<std::vector<std::vector<int>>> satisfaccion_sub(
        empleados,
        std::vector<std::vector<int>>(
            dias,
            std::vector<int>(turnos, 0)));
  std::vector<std::vector<unsigned>> min_empleados_sub(
        dias,
        std::vector<unsigned>(turnos, 0));

  for (size_t empleado{0}; empleado < empleados; ++empleado) {
    for (size_t dia{0}; dia < dias; ++dia) {
      for (size_t turno{0}; turno < turnos; ++turno) {
        satisfaccion_sub[empleado][dia][turno] = std::rand() % 11; // 0-10
      }
    }
  }
  for (size_t dia{0}; dia < dias; ++dia) {
    for (size_t turno{0}; turno < turnos; ++turno) {
      min_empleados_sub[dia][turno] = (std::rand() % empleados) + 1; // 1-empleados
    }
  }

  std::vector<std::string> nombres_empleados;
  for (size_t i{0}; i < empleados; ++i) {
    nombres_empleados.push_back("Empleado_" + std::to_string(i));
  }
  std::vector<std::string> nombres_turnos;
  for (size_t i{0}; i < turnos; ++i) {
    nombres_turnos.push_back("Turno_" + std::to_string(i));
  }
  std::vector<unsigned> descansos;
  for (size_t i{0}; i < empleados; ++i) {
    descansos.push_back(std::rand() % (dias + 1));
  }

  return new InstanciaPlanificacionEmpleados(
      nombres_empleados,
      nombres_turnos,
      dias,
      dias,
      satisfaccion_sub,
      min_empleados_sub,
      descansos);
}