# ---------------------------------------------------------------------------------------
#          Makefile : Práctica 4
#          Autor : Víctor Peralta Cámara
#          Informática Gráfica
# 
# 	Este makefile está creado para la integración contínua del proyecto
# ---------------------------------------------------------------------------------------    
.PHONY: clean
  
LIBS:= -lglut -lGLU -lGL -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
CXXFLAGS:= -Wall -fmax-errors=2 -g

PROJECT=p4

CC= g++
BIN=$(PROJECT)/bin
OBJ=$(PROJECT)/obj
SRC=$(PROJECT)/src
INCLUDE=$(PROJECT)/include

BINARIES=$(BIN)/practica_objetos_B4

all : clean mkdir $(BINARIES) $(BIN)/practica_objetos_B4

# --------------------------------- EJECUTABLES -----------------------------------------
$(BIN)/practica_objetos_B4: $(OBJ)/file_ply_stl.o $(OBJ)/objetos_B4.o $(OBJ)/practica_objetos_B4.o $(OBJ)/robot.o $(OBJ)/luz.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)
# ---------------------------------------------------------------------------------------

# --------------------------------- OBJETOS ---------------------------------------------
$(OBJ)/file_ply_stl.o : $(SRC)/file_ply_stl.cc $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/objetos_B4.o : $(SRC)/objetos_B4.cc $(INCLUDE)/objetos_B4.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/robot.o : $(SRC)/robot.cc $(INCLUDE)/robot.h $(INCLUDE)/objetos_B4.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/practica_objetos_B4.o : $(SRC)/practica_objetos_B4.cc $(INCLUDE)/objetos_B4.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/luz.o : $(SRC)/luz.cc $(INCLUDE)/luz.h $(INCLUDE)/objetos_B4.h
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)
# ---------------------------------------------------------------------------------------

clean:
	echo "Limpiando..."
	rm -f $(OBJ)/*.o $(BIN)/*

redo:
	touch *.cc
	make

mkdir:
	mkdir -p $(PROJECT)/obj
	mkdir -p $(PROJECT)/bin