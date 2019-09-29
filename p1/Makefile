# ---------------------------------------------------------------------------------------
#          Makefile : Proyecto Final
#          Autor : Víctor Peralta Cámara
#          Metodología de la Programación
# ---------------------------------------------------------------------------------------

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGL -lGLU -lglut -lm

# definicion del compilador
#
CC = g++

BIN=bin
OBJ=obj
SRC=src
LIB= lib
INCLUDE=include

all : $(BIN)/practica1_B

# --------------------------------- EJECUTABLES -----------------------------------------
$(BIN)/practica1_B : $(OBJ)/objetos_B.o $(OBJ)/practica1_B.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
# ---------------------------------------------------------------------------------------

# --------------------------------- OBJETOS ---------------------------------------------
$(OBJ)/objetos_B.o : $(SRC)/objetos_B.cc $(INCLUDE)/objetos_B.h $(INCLUDE)/vertex.h
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ)/practica1_B.o : $(SRC)/practica1_B.cc $(INCLUDE)/objetos_B.h $(INCLUDE)/vertex.h
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)
# ---------------------------------------------------------------------------------------

clean : 
	echo "Limpiando..."
	rm obj/*.o lib/*.a bin/*

#
#

redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *
