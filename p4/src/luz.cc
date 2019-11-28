#include "luz.h"

//************************************************************************
// Objeto luz
//************************************************************************

_luz::_luz(GLenum indice_luz, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular){
	this->indice_luz = indice_luz;
	this->posicion = posicion;
	this->ambiente = ambiente;
	this->difusa = difusa;
	this->especular = especular;

	pos_x = posicion[0];
	pos_y = posicion[1];
	pos_z = posicion[2];
	angx = 0;
	angy = 0;
	angz = 0;
	a = 0;
	b = 0;
	c = 0;
}

void _luz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice_luz);
	
	glLightfv(indice_luz, GL_AMBIENT, (GLfloat*) &ambiente);
	glLightfv(indice_luz, GL_DIFFUSE, (GLfloat*) &difusa);
	glLightfv(indice_luz, GL_SPECULAR, (GLfloat*) &especular);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &posicion);
}

void _luz::desactivar(){
	glDisable(indice_luz);
	glDisable(GL_LIGHTING);	
}

void _luz::transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(ang,a,b,c);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &posicion);
	glPopMatrix();
}
