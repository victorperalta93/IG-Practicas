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
		_cilindro *ojo_izq;
		_cilindro *ojo_dcha;
		_cilindro *pupila_izq;
		_cilindro *pupila_dcha;

	public:
		Cabeza();
		~Cabeza();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class Torso: public _triangulos3D{
	private:
		_cilindro *cuerpo;
		_cilindro *cuello;
		_esfera *torso_inferior;
		
	public:	
		Torso();
		~Torso();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class Robot: public _triangulos3D{
	public:
		Robot(){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	protected:
		Cabeza cabeza;
		Torso torso;
};

#endif