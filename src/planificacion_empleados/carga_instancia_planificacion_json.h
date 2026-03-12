// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica: Planificación de empleados
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo carga_instancia_planificacion_json.h: fichero de declaración
// Contiene la declaración de la clase CargaInstanciaPlanificacionJson

#ifndef CARGA_INSTANCIA_PLANIFICACION_JSON_H_
#define CARGA_INSTANCIA_PLANIFICACION_JSON_H_

#include "carga_instancia_planificacion.h"
#include "instancia_planificacion_empleados.h"

#include <string>
#include <vector>

class CargaInstanciaPlanificacionJson : public CargaInstanciaPlanificacion {
 public:
  CargaInstanciaPlanificacionJson(const std::string& json_path) : json_path_(json_path) {}
  CargaInstanciaPlanificacionJson() = default;
  ~CargaInstanciaPlanificacionJson() = default;

  void SetPath(const std::string& json_path) { json_path_ = json_path; }

  InstanciaPlanificacionEmpleados* Load() override;

 private:
  std::string json_path_;
};

#endif