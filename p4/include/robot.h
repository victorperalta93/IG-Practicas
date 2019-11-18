#ifndef _ROBOT
#define _ROBOT

#include <vector>
#include <GL/gl.h>
#include <stdlib.h>
#include "vertex.h"
#include "objetos_B4.h"

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

class Mano: public _triangulos3D{
	private:
		_cubo *palma;
		_cilindro *pulgar;
		_cilindro *indice;
		_cilindro *medio;
		_cilindro *anular;
	public:
		Mano();
		~Mano();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


class Brazo: public _triangulos3D{
	private:
		_esfera *hombro;
		_cilindro *brazo_superior;
		_esfera *codo;
		_cilindro *brazo_inferior;
		Mano mano;
	public:
		Brazo();
		~Brazo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class Pierna: public _triangulos3D{
	private:
		_cilindro *pierna_superior;
		_esfera   *rodilla;
		_cilindro *pierna_inferior;
		_cilindro *pie;
	public:
		Pierna();
		~Pierna();	
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class Robot: public _triangulos3D{
	public:
 		const float LIMITE_BRAZO = 40;
		const float LIMITE_PIERNA = 40;
		float giro_cabeza;
		float giro_brazo;
		float giro_pierna;
		float rotacion_robot;

		Robot(){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	protected:
		Cabeza cabeza;
		Torso torso;
		Brazo brazo_izq;
		Brazo brazo_dcho;
		Pierna pierna_izq;
		Pierna pierna_dcha;
};

#endif