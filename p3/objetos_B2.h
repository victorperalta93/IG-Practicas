//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;
typedef enum{EJE_X,EJE_Y,EJE_Z} _eje;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, bool tapa_sup, bool tapa_inf, _eje eje);

vector<_vertex3f> perfil; 
int num;
};

//*************************************************************************
// clase cono
//*************************************************************************

class _cono: public _triangulos3D
{
public:

_cono(float radio, float altura, int num);


};

//*************************************************************************
// clase cilindro
//*************************************************************************
class _cilindro: public _triangulos3D
{
public:

	_cilindro(float radio=0.00005, float altura=1, int num=20);
};

//*************************************************************************
// clase esfera
//*************************************************************************
class _esfera: public _rotacion{
	private:
		float latitud;
		float longitud;
		float radio;
	public:
		_esfera(float latitud=5, float radio=1, float longitud=20, bool semi=false);
		std::vector<_vertex3f> generar_perfil(bool semi);
};

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
		_cabeza() : semiesfera(5,1,20,true),antena_izq(0.05,0.5,50),antena_dcha(0.05,0.5,50){} ;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _brazo: public _rotacion{
	public:
		_brazo(){};
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _pierna: public _rotacion{
	public:
		_pierna(){};
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