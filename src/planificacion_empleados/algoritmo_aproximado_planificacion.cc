// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo quick_sort.cc: fichero de definición.
// Contiene la definición de la clase AlgoritmoAproximadoPlanificacion.

#include "algoritmo_aproximado_planificacion.h"
#include "solucion_planificacion_empleados.h"

#include <iostream>
#include <limits>

std::vector<Instancia*> AlgoritmoAproximadoPlanificacion::Divide(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  const size_t cantidad_turnos = entrada_procesada->GetCantidadTurnos();
  const size_t cantidad_empleados = entrada_procesada->GetCantidadEmpleados();
  // Calculamos la cantidad de días que tendrá cada subinstancia.
  const unsigned total_dias = entrada_procesada->GetCantidadDias();
  const unsigned dias_base = total_dias / cantidad_divisiones_;
  // Si la cantidad de días no es divisible entre la cantidad de divisiones, se suma 1 día a "resto" primeras
  // instancias.
  const unsigned resto = total_dias % cantidad_divisiones_;

  const std::vector<std::string>& nombres_empleados = entrada_procesada->GetNombresEmpleados();
  const std::vector<std::string>& nombres_turnos = entrada_procesada->GetNombresTurnos();
  const std::vector<unsigned>& descansos = entrada_procesada->GetDescansoEmpleados();
  const unsigned dias_originales = entrada_procesada->GetCantidadDiasOriginales();

  std::vector<Instancia*> instancias;
  unsigned dia_inicio = 0;
  // Se divide la instancia original en tantas instancias como divisiones se hayan indicado.
  for (unsigned division = 0; division < cantidad_divisiones_; ++division) {
    const unsigned dias_instancia_actual = dias_base + (division < resto ? 1 : 0);

    std::vector<std::vector<std::vector<int>>> satisfaccion_sub(
        cantidad_empleados,
        std::vector<std::vector<int>>(
            dias_instancia_actual,
            std::vector<int>(cantidad_turnos, 0)));

    std::vector<std::vector<unsigned>> min_empleados_sub(
        dias_instancia_actual,
        std::vector<unsigned>(cantidad_turnos, 0));

    // Primero se asignan los mínimos de empleados por día y turno para cada subinstancia.
    for (size_t dia{0}; dia < dias_instancia_actual; ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
        // Hay que ajustar el índice de días para obtener el correcto de la instancia original.
        const unsigned dia_real = dia_inicio + dia;
        min_empleados_sub[dia][turno] = entrada_procesada->GetMinimoEmpleados(dia_real, turno);
      }
    }
    // Después se asignan las satisfacciones de cada empleado para cada día y turno.
    for (size_t empleado{0}; empleado < cantidad_empleados; ++empleado) {
      for (size_t dia{0}; dia < dias_instancia_actual; ++dia) {
        for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
          const unsigned dia_real = dia_inicio + dia;
          satisfaccion_sub[empleado][dia][turno] =
              entrada_procesada->GetSatisfaccion(empleado, dia_real, turno);
        }
      }
    }
    InstanciaPlanificacionEmpleados* nueva_instancia = new InstanciaPlanificacionEmpleados(
        nombres_empleados,
        nombres_turnos,
        dias_instancia_actual,
        dias_originales,
        satisfaccion_sub,
        min_empleados_sub,
        descansos);

    instancias.emplace_back(nueva_instancia);
    dia_inicio += dias_instancia_actual;
  }

  return instancias;
}

Solucion* AlgoritmoAproximadoPlanificacion::Combine(std::vector<Solucion*> soluciones) {
  std::vector<SolucionPlanificacionEmpleados*> soluciones_cast;
  for (size_t i{0}; i < soluciones.size(); ++i) {
    soluciones_cast.push_back(dynamic_cast<SolucionPlanificacionEmpleados*>(soluciones[i]));
  }
  // Inicializamos los componentes de la solución, teniendo en cuenta que la cantidad de días es la suma de 
  // las partes izquierda y derecha, mientras que la cantidad de empleados y turnos se mantiene igual.
  unsigned cantidad_dias_fusion{0};
  for (size_t i{0}; i < soluciones_cast.size(); ++i) {
    cantidad_dias_fusion += soluciones_cast[i]->GetCantidadDias();
  }
  const size_t cantidad_empleados_fusion{soluciones_cast[0]->GetCantidadEmpleados()};
  const size_t cantidad_turnos_fusion{soluciones_cast[0]->GetCantidadTurnos()};

  std::vector<std::vector<std::vector<int>>> satisfaccion_fusion(
      cantidad_empleados_fusion,
      std::vector<std::vector<int>>(
          cantidad_dias_fusion,
          std::vector<int>(cantidad_turnos_fusion, 0)));
  
  std::vector<std::vector<std::vector<bool>>> trabajados_fusion(
      cantidad_empleados_fusion,
      std::vector<std::vector<bool>>(
          cantidad_dias_fusion,
          std::vector<bool>(cantidad_turnos_fusion, false)));

  std::vector<std::vector<unsigned>> min_empleados_fusion(
      cantidad_dias_fusion, 
      std::vector<unsigned>(cantidad_turnos_fusion, 0));

  // Ahora asignamos los valores correspondientes a cada parte de la planificación, 
  // teniendo cuidado de ajustar los índices de los días para las distintas soluciones.
  std::vector<unsigned> dias_trabajados_empleado_fusion(cantidad_empleados_fusion, 0);
  unsigned offset_dias = 0;
  // Comenzamos por asignar los mínimos de empleados.
  for (size_t s{0}; s < soluciones_cast.size(); ++s) {
    for (size_t dia{0}; dia < soluciones_cast[s]->GetCantidadDias(); ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
        min_empleados_fusion[offset_dias + dia][turno] =
            soluciones_cast[s]->GetMinimoEmpleados(dia, turno);
      }
    }
    offset_dias += soluciones_cast[s]->GetCantidadDias();
  }

  offset_dias = 0;
  // Después asignamos las satisfacciones y los turnos trabajados.
  for (size_t s{0}; s < soluciones_cast.size(); ++s) {
    for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
      for (size_t dia{0}; dia < soluciones_cast[s]->GetCantidadDias(); ++dia) {
        for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
          satisfaccion_fusion[empleado][offset_dias + dia][turno] =
              soluciones_cast[s]->GetSatisfaccion(empleado, dia, turno);

          if (soluciones_cast[s]->TrabajaEmpleadoDiaTurno(empleado, dia, turno)) {
            trabajados_fusion[empleado][offset_dias + dia][turno] = true;
            ++dias_trabajados_empleado_fusion[empleado];
          }
        }
      }
    }
    offset_dias += soluciones_cast[s]->GetCantidadDias();
  }

  // Creamos la solución resulatnte con los componentes calculados.
  SolucionPlanificacionEmpleados* solucion_fusionada = new SolucionPlanificacionEmpleados(
      soluciones_cast[0]->GetNombresEmpleados(),
      trabajados_fusion,
      dias_trabajados_empleado_fusion,
      soluciones_cast[0]->GetNombresTurnos(),
      cantidad_dias_fusion,
      soluciones_cast[0]->GetCantidadDiasOriginales(),
      satisfaccion_fusion,
      min_empleados_fusion,
      soluciones_cast[0]->GetDescansosEmpleados());

  // Restauramos las reestricciones globales, que son los días mínimos de descanso de cada empleado,
  // solo si la cantidad de dias de la fusión es igual a la cantidad de días originales.
  if (cantidad_dias_fusion >= solucion_fusionada->GetCantidadDiasOriginales()) {
    for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
      unsigned cantidad_dias_descanso = cantidad_dias_fusion - solucion_fusionada->DiasTrabajadosEmpleado(empleado);
      unsigned dias_minimos = solucion_fusionada->DiasMinimosDescansoEmpleado(empleado);
      while (cantidad_dias_descanso < dias_minimos) {
        std::pair<unsigned, unsigned> peor_turno = EncontrarPeorDiaTrabajdoNoMinimo(empleado, solucion_fusionada);
        if (peor_turno.first == -1) {
          // No existe turno para ese empleado que tenga empleados sobrantes.
          break;
        }
        solucion_fusionada->LiberarTrabajoTurno(peor_turno.first, peor_turno.second, empleado);
        ++cantidad_dias_descanso;
      }
      while (cantidad_dias_descanso < dias_minimos) {
        // Eliminamos el día con peor satisfacción del empleado, esta vez sin tener en cuenta
        // los días mínimos de los turnos, pues el paso anterior eliminó todos los sobrantes.
        std::pair<unsigned, unsigned> peor_turno = EncontrarPeorDiaTrabajado(empleado, solucion_fusionada);
        solucion_fusionada->LiberarTrabajoTurno(peor_turno.first, peor_turno.second, empleado);
        ++cantidad_dias_descanso;
      }
    }
  }

  // Liberamos memoria
  for (size_t i{0}; i < soluciones.size(); ++i) {
    delete soluciones[i];
  }

  return solucion_fusionada;
}

 std::pair<int, int> AlgoritmoAproximadoPlanificacion::EncontrarPeorDiaTrabajdoNoMinimo(
      unsigned empleado, 
      SolucionPlanificacionEmpleados* solucion) {
  // Necesitamos poder representar si no existe ese día y turno que cumpla las condiciones,
  // por lo que el pair es de int y no de unsigned, -1 en cualquiera de los valores significa,
  // que no existe ese día y turno.
  std::pair<int, int> peor_dia_turno{-1, -1}; 
  float peor_satisfaccion{std::numeric_limits<float>::infinity()};
  // Buscamos el día y turno que tenga empleados sobrantes donde trabaje el empleado, 
  // y que tenga la peor satisfacción para este. 
  for (size_t dia{0}; dia < solucion->GetCantidadDias(); ++dia) {
    for (size_t turno{0}; turno < solucion->GetCantidadTurnos(); ++turno) {
      if (solucion->TrabajaEmpleadoDiaTurno(empleado, dia, turno) && 
          solucion->EmpleadosTurno(dia, turno) > solucion->GetMinimoEmpleados(dia, turno)) {

        if (solucion->GetSatisfaccion(empleado, dia, turno) < peor_satisfaccion) {
          peor_satisfaccion = solucion->GetSatisfaccion(empleado, dia, turno);
          peor_dia_turno = std::pair<unsigned, unsigned>(dia, turno);
        }
        // No puede trabajar más de un turno en un día así que no tiene sentido seguir buscando aquí.
        break;
      }
    }
  }

  return peor_dia_turno;
}

std::pair<unsigned, unsigned> AlgoritmoAproximadoPlanificacion::EncontrarPeorDiaTrabajado(unsigned empleado, 
                                                                     SolucionPlanificacionEmpleados* solucion) {
  // Se busca el día y turno con peor satisfacción en el que trabaje el empleado,
  // esta vez sin tener en cuenta la cantidad mímina de empleados para ese turno.
  std::pair<unsigned, unsigned> peor_dia_turno{0, 0};
  float peor_satisfaccion{std::numeric_limits<float>::infinity()};
  for (size_t dia{0}; dia < solucion->GetCantidadDias(); ++dia) {
    for (size_t turno{0}; turno < solucion->GetCantidadTurnos(); ++turno) {
      if (solucion->TrabajaEmpleadoDiaTurno(empleado, dia, turno)) {
        if (solucion->GetSatisfaccion(empleado, dia, turno) < peor_satisfaccion) {
          peor_satisfaccion = solucion->GetSatisfaccion(empleado, dia, turno);
          peor_dia_turno = std::pair<unsigned, unsigned>(dia, turno);
        }
        // No puede trabajar más de un turno en un día así que no tiene sentido seguir buscando aquí.
        break;
      }
    }
  }

  return peor_dia_turno;
}

Solucion* AlgoritmoAproximadoPlanificacion::SolveSmall(Instancia* entrada) {
  Solucion* solucion = algoritmo_small_->Solve(entrada);
  return solucion;
}

bool AlgoritmoAproximadoPlanificacion::IsSmall(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  // Lo consideramos pequeño cuando la cantidad de días es 1 o menos,
  return (entrada_procesada->GetCantidadDias() <= small_size_);
}