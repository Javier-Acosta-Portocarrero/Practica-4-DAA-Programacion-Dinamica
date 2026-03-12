// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo almacenar-solucion-planificacion.cc: fichero de definición
// Contiene la definición de la clase AlmacenarSolucionPlanificacionFichero

#include "almacenar_solucion_planificacion_fichero.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

AlmacenarSolucionPlanificacionFichero::AlmacenarSolucionPlanificacionFichero(const std::string& ruta_fichero) {
  ruta_fichero_ = ruta_fichero;
}

void AlmacenarSolucionPlanificacionFichero::Almacenar(const SolucionPlanificacionEmpleados& solucion) {
  std::ofstream file(ruta_fichero_);
  if (!file.is_open()) {
    throw std::runtime_error("Error abriendo fichero de salida");
  }
  const auto& empleados = solucion.GetNombresEmpleados();
  const auto& turnos = solucion.GetNombresTurnos();
  for (size_t dia = 0; dia < solucion.GetCantidadDias(); ++dia) {
    file << "Dia " << dia << "\n";
    // Uso setw para que la salida no salga descentrada.
    file << std::setw(15) << "Empleado";
    for (size_t turno = 0; turno < solucion.GetCantidadTurnos(); ++turno) {
      file << std::setw(4) << turnos[turno];
    }
    file << "\n";
    for (size_t empleado = 0; empleado < solucion.GetCantidadEmpleados(); ++empleado) {
      file << std::setw(15) << empleados[empleado];
      for (size_t turno = 0; turno < solucion.GetCantidadTurnos(); ++turno) {
        // Si el empleado trabaja en ese turno y día, mostramos una X, sino una O.
        char marca = solucion.TrabajaEmpleadoDiaTurno(empleado, dia, turno) ? 'X' : 'O';
        file << std::setw(4) << marca;
      }
      file << "\n";
    }
    file << "\n";
  }
  file << "Valor objetivo: " << solucion.GetValorObjetivo() << "\n";
}