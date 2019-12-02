#include "luz.h"

_luz::_luz(GLenum indice, _vertex4f posicion, _vertex4f ambiente, _vertex4f difusa, _vertex4f especular){
	this->indice = indice;
	this->posicion = posicion;
	this->ambiente = ambiente;
	this->difusa = difusa;
	this->especular = especular;

    rotacion = 0.0;
}

void _luz::movimiento(){
	glRotatef(rotacion,0,1,0);
	glTranslatef(5,0,0);
	glLightfv(indice, GL_POSITION, (GLfloat*) &posicion);
}

void _luz::desactivar(){
	glDisable(indice);
	glDisable(GL_LIGHTING);
}

void _luz_direccional::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice);
	
	glLightfv(indice, GL_AMBIENT,  (GLfloat*) &ambiente);
	glLightfv(indice, GL_DIFFUSE,  (GLfloat*) &difusa);
	glLightfv(indice, GL_SPECULAR, (GLfloat*) &especular);
	glLightfv(indice, GL_POSITION, (GLfloat*) &posicion);
}

void _luz_posicional::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice);

	glLightfv(indice, GL_POSITION, (GLfloat*) &posicion);
	glLightfv(indice, GL_AMBIENT,  (GLfloat*) &ambiente);
	glLightfv(indice, GL_DIFFUSE,  (GLfloat*) &difusa);
	glLightfv(indice, GL_SPECULAR, (GLfloat*) &especular);
}