#ifndef _LUZ
#define _LUZ

//************************************************************************
// Clase luz
//************************************************************************
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

class _luz{
	protected:
		GLenum    indice;
		_vertex4f posicion;
		_vertex4f ambiente;
		_vertex4f difusa;
		_vertex4f especular;

	public:
        float rotacion;

		_luz(GLenum indice, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular);
		void movimiento();
		void desactivar();
};

class _luz_direccional : public _luz{
	private:
		float alpha, beta;

	public:
		_luz_direccional(GLenum indice, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular) 
						: _luz(indice,posicion,ambiente,difusa,especular){alpha=0,beta=0;}
		void activar();
};	

class _luz_posicional : public _luz{
	public:
		_luz_posicional(GLenum indice, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular) 
						: _luz(indice,posicion,ambiente,difusa,especular){}
		void activar();
};

#endif