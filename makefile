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

PROJECT=p5

CC= g++
BIN=$(PROJECT)/bin
OBJ=$(PROJECT)/obj
SRC=$(PROJECT)/src
INCLUDE=$(PROJECT)/include

BINARIES=$(BIN)/practica_objetos_B5

all : clean mkdir $(BINARIES) $(BIN)/practica_objetos_B5

# --------------------------------- EJECUTABLES -----------------------------------------
$(BIN)/practica_objetos_B5: $(OBJ)/file_ply_stl.o $(OBJ)/objetos_B5.o $(OBJ)/practica_objetos_B5.o $(OBJ)/robot.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)
# ---------------------------------------------------------------------------------------

# --------------------------------- OBJETOS ---------------------------------------------
$(OBJ)/file_ply_stl.o : $(SRC)/file_ply_stl.cc $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/objetos_B5.o : $(SRC)/objetos_B5.cc $(INCLUDE)/objetos_B5.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/robot.o : $(SRC)/robot.cc $(INCLUDE)/robot.h $(INCLUDE)/objetos_B5.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/practica_objetos_B5.o : $(SRC)/practica_objetos_B5.cc $(INCLUDE)/objetos_B5.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
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