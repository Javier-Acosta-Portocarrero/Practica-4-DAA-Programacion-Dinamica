// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación Dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 16/03/2026
// Archivo factory_divide_y_venceras.h: fichero de declaración.
// Contiene la declaración de la clase FactoryDivideYVenceras.

#ifndef FACTORY_DIVIDE_Y_VENCERAS_H_
#define FACTORY_DIVIDE_Y_VENCERAS_H_

#include "factory_algoritmos_planificacion.h"

class SelectorFactoryAlgoritmo;

class FactoryDivideYVenceras : public FactoryAlgoritmosPlanificacion {
 public:
  FactoryDivideYVenceras(SelectorFactoryAlgoritmo* selector);
  ~FactoryDivideYVenceras() = default;

  Algoritmo* Crear(const json& config) override;

 private:
  SelectorFactoryAlgoritmo* selector_;
};

#endif