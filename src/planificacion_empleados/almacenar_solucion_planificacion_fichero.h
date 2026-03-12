// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo almacenar-solucion-planificacion.h: fichero de declaración
// Contiene la declaración de la clase AlmacenarSolucionPlanificacionFichero

#ifndef ALMACENAR_SOLUCION_PLANIFICACION_FICHERO_H_
#define ALMACENAR_SOLUCION_PLANIFICACION_FICHERO_H_

#include "almacenar_solucion_planificacion.h"
#include "solucion_planificacion_empleados.h"
#include <string>

class AlmacenarSolucionPlanificacionFichero : public AlmacenarSolucionPlanificacion {
 public:
  explicit AlmacenarSolucionPlanificacionFichero(const std::string& ruta_fichero);
  void Almacenar(const SolucionPlanificacionEmpleados& solucion) override;

 private:
  std::string ruta_fichero_;
};

#endif