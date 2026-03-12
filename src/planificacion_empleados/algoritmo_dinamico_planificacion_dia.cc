// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo algoritmo_voraz_planificacion_dia.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoVorazPlanificacionDia.


#include "../lib/algoritmo.h"
#include "algoritmo_dinamico_planificacion_dia.h"

#include <limits>
#include <stdexcept>
#include <iostream>

Solucion* AlgoritmoDinamicoPlanificacionDia::Solve(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  if (entrada_procesada->GetCantidadDias() > 1) {
    throw std::logic_error("Este algoritmo solo se puede usar para instancias de tamaño 1.");
  }
  SolucionPlanificacionEmpleados* solucion_dia = new SolucionPlanificacionEmpleados(*entrada_procesada);
  size_t cantidad_empleados = solucion_dia->GetCantidadEmpleados();
  size_t cantidad_turnos = solucion_dia->GetCantidadTurnos();

 

  return solucion_dia;  
}

int AlgoritmoDinamicoPlanificacionDia::EncontrarMejorEmpleadoDisponible(SolucionPlanificacionEmpleados* solucion, 
                                                                          size_t dia, 
                                                                          size_t turno) {

}
