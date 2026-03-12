// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2024
// Archivo instancia-planificacion-empleados.h: fichero de declaración.
// Contiene la declaración de la clase InstanciaPlanificacionEmpleados.

#ifndef INSTANCIA_PLANIFICACION_EMPLEADOS_H_
#define INSTANCIA_PLANIFICACION_EMPLEADOS_H_

#include "../lib/algoritmo.h"
#include <vector>
#include <string>

class InstanciaPlanificacionEmpleados: public Instancia {
 public:
  InstanciaPlanificacionEmpleados(const std::vector<std::string>& empleados, const std::vector<std::string>& turnos_,
                                  unsigned dias_a_planificar, unsigned dias_originales,
                                  const std::vector<std::vector<std::vector<int>>>& satisfaccion,
                                  const std::vector<std::vector<unsigned>>& minimo_empleados, 
                                  const std::vector<unsigned>& descansos);
  ~InstanciaPlanificacionEmpleados() = default;

  inline const std::vector<std::string>& GetNombresEmpleados() const { return empleados_;}
  inline const std::vector<std::string>& GetNombresTurnos() const { return turnos_;}
  inline const std::vector<unsigned>& GetDescansoEmpleados() const { return descanso_minimo_empleado;}
  inline unsigned GetCantidadDias() const { return dias_a_planificar_;}
  inline unsigned GetCantidadDiasOriginales() const { return dias_originales_;}
  inline size_t GetCantidadTurnos() const { return turnos_.size();}
  inline size_t GetCantidadEmpleados() const { return empleados_.size();}
  int GetSatisfaccion(size_t empleado, size_t dia, size_t turno) const;
  unsigned GetMinimoEmpleados(size_t dia, size_t turno) const;

 private:
  std::vector<std::string> empleados_;
  std::vector<std::string> turnos_;
  unsigned dias_a_planificar_ = 0;
  unsigned dias_originales_ = 0;
  std::vector<std::vector<std::vector<int>>> satisfaccion_por_empleado_dia_turno_;
  std::vector<std::vector<unsigned>> minimo_empleados_por_dia_turno;
  std::vector<unsigned> descanso_minimo_empleado;
};

#endif