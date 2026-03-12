// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo quick_sort.h: fichero de declaración.
// Contiene la declaración de la clase AlgoritmoAproximadoPlanificacion.

#ifndef ALGORITMO_APROXIMADO_PLANIFICACION_H_
#define ALGORITMO_APROXIMADO_PLANIFICACION_H_

#include "../lib/algoritmo_divide_y_venceras.h"
#include "instancia_planificacion_empleados.h"
#include "solucion_planificacion_empleados.h"

#include <vector>

class AlgoritmoAproximadoPlanificacion : public AlgoritmoDivideYVenceras {
 public:
  AlgoritmoAproximadoPlanificacion(Algoritmo* algoritmo_samll) : algoritmo_small_{algoritmo_samll} {}
  ~AlgoritmoAproximadoPlanificacion() { delete algoritmo_small_;};
  
 protected:
  std::vector<Instancia*> Divide(Instancia* entrada) override;
  Solucion* Combine(std::vector<Solucion*> soluciones) override;
  Solucion* SolveSmall(Instancia* entrada) override;
  bool IsSmall(Instancia* entrada) override;

 private:
  Algoritmo* algoritmo_small_ = nullptr;

  std::pair<int, int> EncontrarPeorDiaTrabajdoNoMinimo(unsigned empleado, SolucionPlanificacionEmpleados* solucion);
  std::pair<unsigned, unsigned> EncontrarPeorDiaTrabajado(unsigned empleado, SolucionPlanificacionEmpleados* solucion);
};

#endif