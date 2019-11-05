# ---------------------------------------------------------------------------------------
#          Makefile : Práctica 3
#          Autor : Víctor Peralta Cámara
#          Informática Gráfica
# ---------------------------------------------------------------------------------------

.PHONY: x clean tar

MODULOS:= practica_objetos_B3.o\
         objetos_B2.o\
         file_ply_stl.o\
      
LIBS:= -lglut -lGLU -lGL -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
CXXFLAGS:= -Wall -fmax-errors=2 -g

CC= g++
BIN=bin
OBJ=obj
SRC=src
INCLUDE=include

all : $(BIN)/practica_objetos_B3

# --------------------------------- EJECUTABLES -----------------------------------------
$(BIN)/practica_objetos_B3 : $(OBJ)/file_ply_stl.o $(OBJ)/objetos_B3.o $(OBJ)/practica_objetos_B3.o $(OBJ)/robot.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)
# ---------------------------------------------------------------------------------------

# --------------------------------- OBJETOS ---------------------------------------------
$(OBJ)/file_ply_stl.o : $(SRC)/file_ply_stl.cc $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/objetos_B3.o : $(SRC)/objetos_B3.cc $(INCLUDE)/objetos_B3.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/robot.o : $(SRC)/robot.cc $(INCLUDE)/robot.h $(INCLUDE)/objetos_B3.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/practica_objetos_B3.o : $(SRC)/practica_objetos_B3.cc $(INCLUDE)/objetos_B3.h $(INCLUDE)/vertex.h $(INCLUDE)/file_ply_stl.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)
# ---------------------------------------------------------------------------------------

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o $(BIN)/*

redo:
	touch *.cc
	make