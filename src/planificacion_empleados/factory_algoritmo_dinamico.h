// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_algoritmo_dinamico.h: fichero de declaración.
// Contiene la declaración de la clase FactoryAlgoritmoDinamico.

#ifndef FACTORY_ALGORITMO_DINAMICO_H_
#define FACTORY_ALGORITMO_DINAMICO_H_

#include "factory_algoritmos_planificacion.h"

class FactoryAlgoritmoDinamico : public FactoryAlgoritmosPlanificacion {
 public:
  ~FactoryAlgoritmoDinamico() = default;
  Algoritmo* Crear(const json& config) override;
};

#endif