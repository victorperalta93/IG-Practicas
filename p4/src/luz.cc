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

    rotacion = 0.0;
}

void _luz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice_luz);
	
	glLightfv(indice_luz, GL_AMBIENT, (GLfloat*) &ambiente);
	glLightfv(indice_luz, GL_DIFFUSE, (GLfloat*) &difusa);
	glLightfv(indice_luz, GL_SPECULAR, (GLfloat*) &especular);
	//glLightfv(indice_luz, GL_POSITION, (GLfloat*) &posicion);
}

void _luz::desactivar(){
	glDisable(indice_luz);
	glDisable(GL_LIGHTING);	
}

void _luz::transformar(){
	glPushMatrix();
        glRotatef(rotacion,0,1,0);
        glTranslatef(5,0,0);
        glLightfv(indice_luz, GL_POSITION, (GLfloat*) &posicion);
	glPopMatrix();
}
