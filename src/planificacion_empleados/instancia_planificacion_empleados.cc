// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2024
// Archivo instancia-planificacion-empleados.cc: fichero de definicion.
// Contiene la definicion de la clase InstanciaPlanificacionEmpleados.

#include "instancia_planificacion_empleados.h"

InstanciaPlanificacionEmpleados::InstanciaPlanificacionEmpleados(const std::vector<std::string>& empleados,  
                                   const std::vector<std::string>& turnos, unsigned dias_a_planificar, 
                                   unsigned dias_originales,
                                   const std::vector<std::vector<std::vector<int>>>& satisfaccion,
                                   const std::vector<std::vector<unsigned>>& minimo_empleados, 
                                   const std::vector<unsigned>& descansos) {
  empleados_ = empleados;
  turnos_ = turnos;
  dias_a_planificar_ = dias_a_planificar;
  dias_originales_ = dias_originales;
  minimo_empleados_por_dia_turno = minimo_empleados;
  descanso_minimo_empleado = descansos;
  satisfaccion_por_empleado_dia_turno_ = satisfaccion;
}

int InstanciaPlanificacionEmpleados::GetSatisfaccion(size_t empleado, size_t dia, size_t turno) const {
  return satisfaccion_por_empleado_dia_turno_[empleado][dia][turno];
}

unsigned InstanciaPlanificacionEmpleados::GetMinimoEmpleados(size_t dia, size_t turno) const {
  return minimo_empleados_por_dia_turno[dia][turno];
}
