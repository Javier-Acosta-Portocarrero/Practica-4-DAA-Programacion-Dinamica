// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 4: Programación dinámica
// Autor: Javier Acosta Portocarrero
// Fecha: 14/3/2026
// Archivo main.cc: fichero con la función principal del programa.
// Se encarga de usar las clases de la librería de planificación de empleados 
// implementada para experimentar con la planificación de distintas instancias 
// introducidas por fichero.

#include "planificacion_empleados/carga_instancia_planificacion_json.h"
#include "planificacion_empleados/almacenar_solucion_planificacion_fichero.h"
#include "planificacion_empleados/planificador_empleados.h"
#include "planificacion_empleados/algoritmo_aproximado_planificacion.h"
#include "planificacion_empleados/algoritmo_voraz_planificacion_dia.h"
#include "planificacion_empleados/algoritmo_dinamico_planificacion_dia.h"
#include "planificacion_empleados/factory_algoritmo_planificacion_json.h"
#include "planificacion_empleados/generador_instancias_planificacion.h"

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>


int main() {
  std::cout << "Elija el modo de ejecución, comparativa de algoritmos(0) o modo normal(1): ";
  unsigned modo_ejecucion{1};
  std::cin >> modo_ejecucion;
  if (modo_ejecucion == 0) {
    std::srand(time(nullptr));
    size_t empleados = 10;
    size_t turnos = 5;
    std::vector<size_t> dias = {5, 10, 15, 20, 25, 30, 40, 50};
    GeneradorInstanciasPlanificacion generador;
    PlanificadorEmpleados planificador(nullptr);
    for (size_t dia : dias) {
      InstanciaPlanificacionEmpleados* instancia = generador.GenerarInstancia(empleados, dia, turnos);
      planificador.SetEstrategia(new AlgoritmoAproximadoPlanificacion(new AlgoritmoDinamicoPlanificacionDia(), 1, 2));
      double tiempo_ejecucion_dinamico{0.0};
      float valor_objetivo_dinamico{0.0};
      auto inicio = std::chrono::high_resolution_clock::now();
      SolucionPlanificacionEmpleados* solucion_dinamica = planificador.Planificar(instancia);
      auto fin = std::chrono::high_resolution_clock::now();
      tiempo_ejecucion_dinamico = std::chrono::duration<double>(fin - inicio).count();
      valor_objetivo_dinamico = solucion_dinamica->GetValorObjetivo();

      planificador.SetEstrategia(new AlgoritmoAproximadoPlanificacion(new AlgoritmoVorazPlanificacionDia(), 1, 2));
      double tiempo_ejecucion_voraz{0.0};
      float valor_objetivo_voraz{0.0};
      inicio = std::chrono::high_resolution_clock::now();
      SolucionPlanificacionEmpleados* solucion_voraz = planificador.Planificar(instancia);
      fin = std::chrono::high_resolution_clock::now();
      tiempo_ejecucion_voraz = std::chrono::duration<double>(fin - inicio).count();
      valor_objetivo_voraz = solucion_voraz->GetValorObjetivo();

      // Se imprime días, turnos, empleados, tiempo y valor objetivo para cada algoritmo.
      std::cout << "Días: " << dia << ", Turnos: " << turnos << ", Empleados: " << empleados << "\n";
      std::cout << "Algoritmo Dinámico: Tiempo de ejecución: " << tiempo_ejecucion_dinamico 
                << " segundos, Valor objetivo: " << valor_objetivo_dinamico << "\n";
      std::cout << "Algoritmo Voraz: Tiempo de ejecución: " << tiempo_ejecucion_voraz
                << " segundos, Valor objetivo: " << valor_objetivo_voraz << "\n\n";

      // Libreamos memoria 
      delete instancia;
      delete solucion_dinamica;
      delete solucion_voraz;
    }
  } else if (modo_ejecucion == 1) {
    std::cout << "Introduza la ruta del fichero json con la configuración del algoritmo a usar.\n";
    std::string ruta_fichero_algoritmo{"algoritmo.json"};
    std::cin >> ruta_fichero_algoritmo;

    std::cout << "Introduzca la ruta del fichero de entrada con los datos de la planificación:\n";
    std::string ruta_fichero_instancia{"predeterminado.txt"};
    std::cin >> ruta_fichero_instancia;

    CargaInstanciaPlanificacion* carga_instancias = new CargaInstanciaPlanificacionJson(ruta_fichero_instancia);
    InstanciaPlanificacionEmpleados* entrada = carga_instancias->Load();

    FactoryAlgoritmosPlanificacion* factory = new FactoryAlgoritmosPlanificacionJson(ruta_fichero_algoritmo);
    Algoritmo* estrategia_planificacion = factory->GenerarAlgoritmoPlanificacion();
    PlanificadorEmpleados planificador(estrategia_planificacion);

    SolucionPlanificacionEmpleados* solucion = planificador.Planificar(entrada);

    std::cout << "\nIntroduzca el fichero de salida donde se volcarán los resultados:\n";
    std::string ruta_fichero_salida{"salida_predeterminada.txt"};
    std::cin >> ruta_fichero_salida;
    AlmacenarSolucionPlanificacion* almacenador = new AlmacenarSolucionPlanificacionFichero(ruta_fichero_salida);
    almacenador->Almacenar(*solucion);
  } else {
    std::cerr << "Modo de ejecución no válido, abortando ejecución.\n";
    return 1;
  }

  return 0;
}