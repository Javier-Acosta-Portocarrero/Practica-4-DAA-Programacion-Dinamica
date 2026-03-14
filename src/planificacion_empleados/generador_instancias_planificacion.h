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

#ifndef GENERADOR_INSTANCIA_PLANIFICACION_H_
#define GENERADOR_INSTANCIA_PLANIFICACION_H_

#include "instancia_planificacion_empleados.h"

class GeneradorInstanciasPlanificacion {
 public:
  GeneradorInstanciasPlanificacion() = default;
  ~GeneradorInstanciasPlanificacion() = default;

  InstanciaPlanificacionEmpleados* GenerarInstancia(size_t empleados, size_t dias, size_t turnos);
};

#endif