// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo almacenar-solucion-planificacion.h

#ifndef ALMACENAR_SOLUCION_PLANIFICACION_H_
#define ALMACENAR_SOLUCION_PLANIFICACION_H_

#include "solucion_planificacion_empleados.h"
#include <string>

class AlmacenarSolucionPlanificacion {
 public:
  virtual ~AlmacenarSolucionPlanificacion() = default;
  virtual void Almacenar(const SolucionPlanificacionEmpleados& solucion) = 0;
};

#endif