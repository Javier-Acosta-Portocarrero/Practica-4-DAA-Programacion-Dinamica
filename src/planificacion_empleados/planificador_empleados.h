// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo planificador_empleados.h: fichero de declaración.
// Contiene la declaración de la clase PlanificadorEmpleados.

#ifndef PLANIFICADOR_EMPLEADOS_H_
#define PLANIFICADOR_EMPLEADOS_H_

#include "../lib/algoritmo.h"
#include "solucion_planificacion_empleados.h"

class PlanificadorEmpleados {
 public:
  PlanificadorEmpleados(Algoritmo* estrategia) : estrategia_{estrategia} {}
  ~PlanificadorEmpleados() { delete estrategia_;}

  SolucionPlanificacionEmpleados* Planificar(InstanciaPlanificacionEmpleados* entrada) const;

  void SetEstrategia(Algoritmo* nueva_estrategia);
 private:
  Algoritmo* estrategia_ = nullptr;
};

#endif