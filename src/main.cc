// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 08/03/2026
// Archivo main.cc: fichero con la función principal del programa.
// Se encarga de usar las clases de la librería de planificación de empleados 
// implementada para experimentar con la planificación de distintas instancias 
// introducidas por fichero.

#include "planificacion_empleados/carga_instancia_planificacion_json.h"
#include "planificacion_empleados/almacenar_solucion_planificacion_fichero.h"
#include "planificacion_empleados/planificador_empleados.h"
#include "planificacion_empleados/algoritmo_aproximado_planificacion.h"
#include "planificacion_empleados/algoritmo_voraz_planificacion_dia.h"
#include <iostream>

int main() {
  std::cout << "Introduce el fichero de entrada con los datos de la planificación:\n";
  std::string ruta_fichero{"predeterminado.txt"};
  std::cin >> ruta_fichero;

  CargaInstanciaPlanificacion* carga_instancias = new CargaInstanciaPlanificacionJson(ruta_fichero);
  InstanciaPlanificacionEmpleados* entrada = carga_instancias->Load();

  Algoritmo* resuelve_casos_dia = new AlgoritmoVorazPlanificacionDia();
  Algoritmo* estrategia_planificacion = new AlgoritmoAproximadoPlanificacion(resuelve_casos_dia);
  PlanificadorEmpleados planificador(estrategia_planificacion);

  SolucionPlanificacionEmpleados* solucion = planificador.Planificar(entrada);

  std::cout << "\nIntroduce el fichero de salida donde se volcarán los resultados:\n";
  std::string ruta_fichero_salida{"salida_predeterminada.txt"};
  std::cin >> ruta_fichero_salida;
  AlmacenarSolucionPlanificacion* almacenador = new AlmacenarSolucionPlanificacionFichero(ruta_fichero_salida);
  almacenador->Almacenar(*solucion);

  return 0;
}