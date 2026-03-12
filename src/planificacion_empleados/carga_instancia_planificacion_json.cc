// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica: Planificación de empleados
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo carga_instancia_planificacion_json.cc: fichero de definición
// Contiene la definición de la clase CargaInstanciaPlanificacionJson

#include "carga_instancia_planificacion_json.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

InstanciaPlanificacionEmpleados* CargaInstanciaPlanificacionJson::Load() {
  std::ifstream file(json_path_);
  if (!file.is_open()) {
      throw std::runtime_error("Error abriendo fichero JSON");
  }
  json json_procesado;
  file >> json_procesado;
  // Turnos
  std::vector<std::string> turnos = json_procesado["shifts"].get<std::vector<std::string>>();
  // Empleados
  std::vector<std::string> empleados;
  std::vector<unsigned> free_days;
  for (const auto& emp : json_procesado["employees"]) {
      empleados.push_back(emp["name"]);
      free_days.push_back(emp["freeDays"]);
  }
  size_t num_empleados = empleados.size();
  size_t num_turnos = turnos.size();
  // Cantidad de días
  size_t dias = json_procesado["planningHorizon"];
  // Satisfacción
  std::vector<std::vector<std::vector<int>>> satisfaccion(
      num_empleados,
      std::vector<std::vector<int>>(dias, std::vector<int>(num_turnos, 0))
  );
  for (const auto& s : json_procesado["satisfaction"]) {
    int t = s["shift"];
    int e = s["employee"];
    int d = s["day"];
    int v = s["value"];
    satisfaccion[e][d][t] = v;
  }
  // Empleados por turno.
  std::vector<std::vector<unsigned>> minimo_empleados(
      dias, std::vector<unsigned>(num_turnos, 0)
  );
  for (const auto& r : json_procesado["requiredEmployees"]) {
    int shift = r["shift"];
    int day = r["day"];
    int value = r["value"];
    minimo_empleados[day][shift] = value;
  }

  return new InstanciaPlanificacionEmpleados(
      empleados,
      turnos,
      dias,
      dias,
      satisfaccion,
      minimo_empleados,
      free_days);
}