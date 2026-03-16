// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_algoritmo_voraz.h: fichero de declaración.
// Contiene la declaración de la clase FactoryAlgoritmoVoraz.

#ifndef FACTORY_ALGORITMO_VORAZ_H_
#define FACTORY_ALGORITMO_VORAZ_H_

#include "factory_algoritmos_planificacion.h"

class FactoryAlgoritmoVoraz : public FactoryAlgoritmosPlanificacion {
 public:
  ~FactoryAlgoritmoVoraz() = default;
  Algoritmo* Crear(const json& config) override;
};

#endif