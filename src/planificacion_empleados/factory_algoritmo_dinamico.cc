// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_algoritmo_dinamico.cc: fichero de definición.
// Contiene la definición de la clase FactoryAlgoritmoDinamico.

#include "factory_algoritmo_dinamico.h"
#include "algoritmo_dinamico_planificacion_dia.h"

Algoritmo* FactoryAlgoritmoDinamico::Crear(const json& config) {
  return new AlgoritmoDinamicoPlanificacionDia();
}