// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 14/03/2026
// Archivo factory_algoritmo_planificacion_json.h: fichero de declaración.
// Contiene la declaración de la clase FactoryAlgoritmosPlanificacionJson.

#ifndef FACTORY_ALGORIMTO_PLANIFICACION_JSON_H_
#define FACTORY_ALGORIMTO_PLANIFICACION_JSON_H_

#include "factory_algoritmos_planificacion.h"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FactoryAlgoritmosPlanificacionJson : public FactoryAlgoritmosPlanificacion{
 public:
  FactoryAlgoritmosPlanificacionJson(std::string ruta_fichero) : ruta_fichero_{ruta_fichero} {}
  ~FactoryAlgoritmosPlanificacionJson() = default;

  Algoritmo* GenerarAlgoritmoPlanificacion() override;
  void SetRutaFichero(std::string ruta_fichero) { ruta_fichero_ = ruta_fichero;}

 private: 
  std::string ruta_fichero_;

  Algoritmo* ProcesarDivideYVencerasBinario(const json& json_actual);
  Algoritmo* ProcesarDivideYVenceras(const json& json_actual);
};

#endif