// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2024
// Archivo solucion-planificacion-empleados.cc: fichero de definicion.
// Contiene la definicion de la clase SolucionPlanificacionEmpleados.

#include "solucion_planificacion_empleados.h"

SolucionPlanificacionEmpleados::SolucionPlanificacionEmpleados(const InstanciaPlanificacionEmpleados& instancia_base) {
  empleados_ = instancia_base.GetNombresEmpleados();
  turnos_ = instancia_base.GetNombresTurnos();
  dias_a_planificar_ = instancia_base.GetCantidadDias();
  dias_originales_ = instancia_base.GetCantidadDiasOriginales();
  descanso_minimo_empleados_ = instancia_base.GetDescansoEmpleados();
  minimo_empleados_por_dia_turno_ = std::vector<std::vector<unsigned>>(
      dias_a_planificar_, std::vector<unsigned>(turnos_.size(), 0));

  for (size_t dia{0}; dia < instancia_base.GetCantidadDias(); ++dia) {
    for (size_t turno{0}; turno < instancia_base.GetCantidadTurnos(); ++turno) {
      minimo_empleados_por_dia_turno_[dia][turno] = instancia_base.GetMinimoEmpleados(dia, turno);
    }
  }
  satisfaccion_por_empleado_dia_turno_ = std::vector<std::vector<std::vector<int>>>(
      empleados_.size(), 
      std::vector<std::vector<int>>(dias_a_planificar_,
      std::vector<int>(turnos_.size(), 0)));
      
  for (size_t empleado{0}; empleado < instancia_base.GetCantidadEmpleados(); ++empleado) {
    for (size_t dia{0}; dia < instancia_base.GetCantidadDias(); ++dia) {
      for (size_t turno{0}; turno < instancia_base.GetCantidadTurnos(); ++turno) {
        satisfaccion_por_empleado_dia_turno_[empleado][dia][turno] = instancia_base.GetSatisfaccion(empleado, 
                                                                                                    dia, turno);
      }
    }
  }
  trabaja_empleado_dia_turno_ = std::vector<std::vector<std::vector<bool>>>(
      empleados_.size(), std::vector<std::vector<bool>>(
          dias_a_planificar_, std::vector<bool>(turnos_.size(), false)));

  dias_trabajados_empleado_ = std::vector<unsigned>(empleados_.size(), 0);
}

SolucionPlanificacionEmpleados::SolucionPlanificacionEmpleados(
    const std::vector<std::string>& empleados, 
    const std::vector<std::vector<std::vector<bool>>>& trabaja_empleado_dia_turno,
    const std::vector<unsigned>& dias_trabajados_empleado, 
    const std::vector<std::string>& turnos, 
    unsigned dias_a_planificar, unsigned dias_originales,
    const std::vector<std::vector<std::vector<int>>>& satisfaccion,
    const std::vector<std::vector<unsigned>>& minimo_empleados, 
    const std::vector<unsigned>& descansos) {

  empleados_ = empleados;
  trabaja_empleado_dia_turno_ = trabaja_empleado_dia_turno;
  dias_trabajados_empleado_ = dias_trabajados_empleado;
  turnos_ = turnos;
  dias_a_planificar_ = dias_a_planificar;
  dias_originales_ = dias_originales;
  minimo_empleados_por_dia_turno_ = minimo_empleados;
  descanso_minimo_empleados_ = descansos;
  satisfaccion_por_empleado_dia_turno_ = satisfaccion;
}

int SolucionPlanificacionEmpleados::GetSatisfaccion(size_t empleado, size_t dia, size_t turno) const {
  return satisfaccion_por_empleado_dia_turno_[empleado][dia][turno];
}

unsigned SolucionPlanificacionEmpleados::GetMinimoEmpleados(size_t dia, size_t turno) const {
  return minimo_empleados_por_dia_turno_[dia][turno];
}

bool SolucionPlanificacionEmpleados::TrabajaEmpleadoDia(size_t empleado, size_t dia) const {
  for (size_t turno{0}; turno < GetCantidadTurnos(); ++turno) {
    if (trabaja_empleado_dia_turno_[empleado][dia][turno]) {
      return true;
    }
  }
  return false;
}

bool SolucionPlanificacionEmpleados::TrabajaEmpleadoDiaTurno(size_t empleado, size_t dia, size_t turno) const {
  return trabaja_empleado_dia_turno_[empleado][dia][turno];
}

unsigned SolucionPlanificacionEmpleados::DiasTrabajadosEmpleado(size_t empleado) const {
  return dias_trabajados_empleado_[empleado];
}

void SolucionPlanificacionEmpleados::NuevoTrabajoTurno(size_t dia, size_t turno, size_t empleado) {
  // si ya trabaja ese día no permitimos otro turno
  if (TrabajaEmpleadoDia(empleado, dia)) {
    return;
  }
  if (!trabaja_empleado_dia_turno_[empleado][dia][turno]) {
    trabaja_empleado_dia_turno_[empleado][dia][turno] = true;
    ++dias_trabajados_empleado_[empleado];
  }
}

void SolucionPlanificacionEmpleados::LiberarTrabajoTurno(size_t dia, size_t turno, size_t empleado) {
  if (trabaja_empleado_dia_turno_[empleado][dia][turno]) {
    trabaja_empleado_dia_turno_[empleado][dia][turno] = false;
    // No puede trabajar el mismo día en más de un turno.
    --dias_trabajados_empleado_[empleado];
  }
}

unsigned SolucionPlanificacionEmpleados::EmpleadosTurno(size_t dia, size_t turno) const {
  unsigned total_empleados{0};
  for (int i{0}; i < GetCantidadEmpleados(); ++i) {
    if (trabaja_empleado_dia_turno_[i][dia][turno]) {
      ++total_empleados;
    }
  }
  return total_empleados;
}

float SolucionPlanificacionEmpleados::GetValorObjetivo() const {
  float valor_objetivo{0};
  // Primero calculamos la si el turno tiene la cantidad mínima deseada de empleados,
  // y después el sumatario de la satisfacción de los empleados.
  for (size_t dia{0}; dia < GetCantidadDias(); ++dia) {
    for (size_t turno{0}; turno < GetCantidadTurnos(); ++turno) {
      if (EmpleadosTurno(dia, turno) >= GetMinimoEmpleados(dia, turno)) {
        valor_objetivo += 100;
      }
      for (size_t empleado{0}; empleado < GetCantidadEmpleados(); ++empleado) {
        if (trabaja_empleado_dia_turno_[empleado][dia][turno]) {
          valor_objetivo += GetSatisfaccion(empleado, dia, turno);
        }
      }
    }
  }
  return valor_objetivo;
}