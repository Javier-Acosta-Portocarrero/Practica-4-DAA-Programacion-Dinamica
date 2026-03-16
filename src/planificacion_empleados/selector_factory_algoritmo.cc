// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo selector_factory_algoritmo.cc: fichero de definición.
// Contiene la definición de la clase SelectorFactoryAlgoritmo.

#include "selector_factory_algoritmo.h"
#include "factory_algoritmo_voraz.h"
#include "factory_algoritmo_dinamico.h"
#include "factory_divide_y_venceras.h"
#include "factory_divide_y_venceras_binario.h"

FactoryAlgoritmosPlanificacion* SelectorFactoryAlgoritmo::Seleccionar(const json& config) {

  std::string tipo = config["class"];

  if (tipo == "Greedy")
    return new FactoryAlgoritmoVoraz();

  if (tipo == "DynamicProgramming")
    return new FactoryAlgoritmoDinamico();

  if (tipo == "DivideAndConquer")
    return new FactoryDivideYVenceras(this);

  if (tipo == "BinaryDivideAndConquer")
    return new FactoryDivideYVencerasBinario(this);

  throw std::runtime_error("Algoritmo no soportado: " + tipo);
}