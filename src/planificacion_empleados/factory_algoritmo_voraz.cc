// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_algoritmo_voraz.cc: fichero de definición.
// Contiene la definición de la clase FactoryAlgoritmoVoraz.

#include "factory_algoritmo_voraz.h"
#include "algoritmo_voraz_planificacion_dia.h"

Algoritmo* FactoryAlgoritmoVoraz::Crear(const json& config) {
  return new AlgoritmoVorazPlanificacionDia();
}