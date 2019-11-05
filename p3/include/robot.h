#ifndef _ROBOT
#define _ROBOT

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "objetos_B3.h"

class _torso: public _rotacion{
	private:
		_cilindro cuerpo;

	public:
		_torso() : cuerpo(1,2,50){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _cabeza: public _rotacion{
	private:
		_esfera semiesfera;
		_cilindro antena_izq;
		_cilindro antena_dcha;

	public:
		_cabeza() : semiesfera(5,1,20,true),antena_izq(0.05,0.5,20),antena_dcha(0.05,0.5,20){} ;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _brazo: public _rotacion{
	private:
		_cilindro extremidad;
		_esfera articulacion;

	public:
		_brazo() : extremidad(0.15,1,20),articulacion(5,0.1,20,false){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _pierna: public _rotacion{
	private:
		_cilindro extremidad;
		_esfera pie;
	public:
		_pierna() : extremidad(0.25,1,20), pie(5,0.25,20,true){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _andy_android: public _rotacion{
	public:
		_andy_android(){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	protected:
		_torso torso;
		_cabeza cabeza;
		_brazo brazo_izq;
		_brazo brazo_drch;
		_pierna pierna_izq;
		_pierna pierna_drch;
};

#endif