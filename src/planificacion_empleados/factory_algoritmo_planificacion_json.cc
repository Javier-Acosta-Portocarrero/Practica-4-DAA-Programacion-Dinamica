// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 14/03/2026
// Archivo factory_algoritmo_planificacion_json.cc: fichero de definición.
// Contiene la definición de la clase FactoryAlgoritmosPlanificacionJson.

#include "factory_algoritmo_planificacion_json.h"
#include "algoritmo_aproximado_planificacion.h"
#include "algoritmo_voraz_planificacion_dia.h"
#include "algoritmo_dinamico_planificacion_dia.h"
#include <fstream>

using json = nlohmann::json;

Algoritmo* FactoryAlgoritmosPlanificacionJson::GenerarAlgoritmoPlanificacion() {
  std::ifstream flujo_json{ruta_fichero_};
  if (!flujo_json.is_open()) {
    throw std::runtime_error("No se ha podido abrir el fichero JSON para generar el algoritmo: " + ruta_fichero_);
  }
  json json_procesado;
  flujo_json >> json_procesado;
  if (!json_procesado.contains("class")) {
    throw std::runtime_error("Clase de algoritmo no especificada en el Json.");
  }
  std::string tipo_algoritmo = json_procesado["class"];
  Algoritmo* algoritmo_generado = nullptr;
  if (tipo_algoritmo == "BinaryDivideAndConquer") {
    algoritmo_generado = ProcesarDivideYVencerasBinario(json_procesado);
  } else if (tipo_algoritmo == "DivideAndConquer") {
    algoritmo_generado = ProcesarDivideYVenceras(json_procesado);
  } else {
    throw std::runtime_error("Algoritmo principal no soportado en el Json: " + tipo_algoritmo);
  }
  return algoritmo_generado;
}

Algoritmo* FactoryAlgoritmosPlanificacionJson::ProcesarDivideYVencerasBinario(const json& json_actual) {
  unsigned small_size = 1;
  if (json_actual.contains("smallSize")) {
    small_size = json_actual["smallSize"].get<unsigned>();
  }
  if (!json_actual.contains("smallSolver")) {
    throw std::runtime_error("SmallSolver no especificado en el Json.");
  }
  const json& small_solver = json_actual["smallSolver"];
  if (!small_solver.contains("class")) {
    throw std::runtime_error("Clase de algoritmo no especificada en el Json.");
  }
  std::string tipo_algoritmo = small_solver["class"];
  if (tipo_algoritmo == "BinaryDivideAndConquer") {
    return new AlgoritmoAproximadoPlanificacion(ProcesarDivideYVencerasBinario(small_solver), small_size);
  }
  if (tipo_algoritmo == "DivideAndConquer") {
    return new AlgoritmoAproximadoPlanificacion(ProcesarDivideYVenceras(small_solver), small_size);
  }
  if (tipo_algoritmo == "Greedy") {
    return new AlgoritmoAproximadoPlanificacion(new AlgoritmoVorazPlanificacionDia(), small_size);
  }
  if (tipo_algoritmo == "DynamicProgramming") {
    return new AlgoritmoAproximadoPlanificacion(new AlgoritmoDinamicoPlanificacionDia(), small_size);
  }

  throw std::runtime_error("Algoritmo principal no soportado en el Json: " + tipo_algoritmo);
}

Algoritmo* FactoryAlgoritmosPlanificacionJson::ProcesarDivideYVenceras(const json& json_actual) {
  unsigned small_size = 1;
  if (json_actual.contains("smallSize")) {
    small_size = json_actual["smallSize"].get<unsigned>();
  }
  unsigned cantidad_divisiones = 2;
  if (json_actual.contains("divisions")) {
    cantidad_divisiones = json_actual["divisions"].get<unsigned>();
  }
  if (!json_actual.contains("smallSolver")) {
    throw std::runtime_error("SmallSolver no especificado en el Json.");
  }
  const json& small_solver = json_actual["smallSolver"];
  if (!small_solver.contains("class")) {
    throw std::runtime_error("Clase de algoritmo no especificada en el Json.");
  }
  std::string tipo_algoritmo = small_solver["class"];
  if (tipo_algoritmo == "BinaryDivideAndConquer") {
    return new AlgoritmoAproximadoPlanificacion(
        ProcesarDivideYVencerasBinario(small_solver), 
        small_size, 
        cantidad_divisiones);
  }
  if (tipo_algoritmo == "DivideAndConquer") {
    return new AlgoritmoAproximadoPlanificacion(
        ProcesarDivideYVenceras(small_solver), 
        small_size,
        cantidad_divisiones);
  }
  if (tipo_algoritmo == "Greedy") {
    return new AlgoritmoAproximadoPlanificacion(
        new AlgoritmoVorazPlanificacionDia(), 
        small_size,
        cantidad_divisiones);
  }
  if (tipo_algoritmo == "DynamicProgramming") {
    return new AlgoritmoAproximadoPlanificacion(
        new AlgoritmoDinamicoPlanificacionDia(), 
        small_size,
        cantidad_divisiones);
  }

  throw std::runtime_error("Algoritmo principal no soportado en el Json: " + tipo_algoritmo);
}