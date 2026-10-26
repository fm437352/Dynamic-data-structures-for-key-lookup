
CXX = g++
CXXFLAGS = -std=c++11 -Wall

#Rutas
SRC1 = src/solucion1/main1.cpp
SRC2 = src/solucion2/main2.cpp
TARGET1 = bin/solucion1
TARGET2 = bin/solucion2

#Parámetros por defecto
K ?= 32
REP ?= 100

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC1) -o $(TARGET1)

$(TARGET2): $(SRC2)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC2) -o $(TARGET2)

#Ejecutar Solución 1 (arreglo dinamico)
run1: $(TARGET1)
	@echo "ejecutando solución 1"
	./$(TARGET1)

#Ejecutar Solución 2 (lista circular doblemente enlazada)
run2: $(TARGET2)
	@echo "ejecutando solución 2"
	./$(TARGET2) $(K) $(REP)

#Ejecutar ambas soluciones de forma secuencial
run_all: $(TARGET1) $(TARGET2)
	@echo "ejecutando solución 1"
	./$(TARGET1)
	@echo ""
	@echo "ejecutando solución 2"
	./$(TARGET2) $(K) $(REP)

clean:
	rm -rf bin
	rm -rf bin
