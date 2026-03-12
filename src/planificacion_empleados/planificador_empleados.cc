// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo planificador_empleados.cc: fichero de definición.
// Contiene la definición de la clase PlanificadorEmpleados.

#include "planificador_empleados.h"
#include <stdexcept>

SolucionPlanificacionEmpleados* PlanificadorEmpleados::Planificar(InstanciaPlanificacionEmpleados* entrada) const {
  SolucionPlanificacionEmpleados* solucion = dynamic_cast<SolucionPlanificacionEmpleados*>(estrategia_->Solve(entrada));
  if (!solucion) {
    throw std::runtime_error("La estrategia elegida no es capaz de resolver la planificación-");
  }
  return solucion;
}

void PlanificadorEmpleados::SetEstrategia(Algoritmo* nueva_estrategia) {
  if (estrategia_ != nullptr) {
    delete estrategia_;
  }
  estrategia_ = nueva_estrategia;
}
