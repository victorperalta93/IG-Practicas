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
		_vertex4f posicion;
		_vertex4f ambiente;
		_vertex4f difusa;
		_vertex4f especular;

	public:
		float pos_x, pos_y, pos_z, angx, angy, angz;
		int a, b, c;
		GLenum indice_luz;

		_luz(GLenum indice_luz, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular);

		void activar();
		void transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z);
		void desactivar();
};

#endif