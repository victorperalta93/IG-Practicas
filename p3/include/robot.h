#ifndef _ROBOT
#define _ROBOT

#include <vector>
#include <GL/gl.h>
#include <stdlib.h>
#include "vertex.h"
#include "objetos_B3.h"

class Cabeza: public _triangulos3D{
	private:
		_esfera *craneo;
		_cilindro *oreja_izq;
		_cilindro *oreja_dcha;

	public:
		Cabeza();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
		~Cabeza();
};

class Robot: public _triangulos3D{
	public:
		Robot(){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	protected:
		Cabeza cabeza;
};

#endif