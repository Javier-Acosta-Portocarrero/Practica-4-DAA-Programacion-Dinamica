// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica: Planificación de empleados
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo carga_instancia_planificacion.h: fichero de declaración
// Contiene la declaración de la clase CargaInstanciaPlanificacion.

#ifndef CARGA_INSTANCIA_PLANIFICACION_H_
#define CARGA_INSTANCIA_PLANIFICACION_H_

#include "carga_instancia_planificacion.h"
#include "instancia_planificacion_empleados.h"

#include <string>
#include <vector>

class CargaInstanciaPlanificacion {
 public:
  virtual ~CargaInstanciaPlanificacion() = default;

  virtual InstanciaPlanificacionEmpleados* Load() = 0;
};

#endif