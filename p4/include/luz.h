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
        float rotacion;
		GLenum indice_luz;

		_luz(GLenum indice_luz, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular);

		void activar();
		void transformar();
		void desactivar();
};

#endif