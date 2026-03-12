// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo algoritmo_divide_y_venceras.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoDivideYVenceras.

#include "algoritmo_divide_y_venceras.h"

Solucion* AlgoritmoDivideYVenceras::Solve(Instancia* entrada) {
  if (IsSmall(entrada)) {
    return SolveSmall(entrada);
  }  
  std::vector<Instancia*> subinstancias = Divide(entrada);
  std::vector<Solucion*> soluciones;  
  for (Instancia* subinstancia : subinstancias) {
    soluciones.push_back(Solve(subinstancia));
    delete subinstancia;
  }
    
  return Combine(soluciones);
}