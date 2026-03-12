CXX = g++
CXXFLAGS =  -std=c++23
TARGET = practica3_DAA

SOURCES = src/lib/algoritmo_divide_y_venceras.cc src/planificacion_empleados/algoritmo_aproximado_planificacion.cc  src/planificacion_empleados/algoritmo_voraz_planificacion_dia.cc src/planificacion_empleados/almacenar_solucion_planificacion_fichero.cc src/planificacion_empleados/carga_instancia_planificacion_json.cc src/planificacion_empleados/instancia_planificacion_empleados.cc src/planificacion_empleados/planificador_empleados.cc src/planificacion_empleados/solucion_planificacion_empleados.cc src/main.cc

OBJECTS = $(SOURCES:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

cleano:
	rm -f $(OBJECTS)

.PHONY: all clean cleano