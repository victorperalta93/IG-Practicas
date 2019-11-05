#include "objetos_B3.h"
#include "robot.h"
#include "file_ply_stl.hpp"


void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->semiesfera.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4,0.9,0);
	glRotatef(15.0,0,0,1);
	this->antena_izq.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,0.9,0);
	glRotatef(-15.0,0,0,1);
	this->antena_dcha.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

}

void _torso::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->cuerpo.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}

void _brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->extremidad.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2,0.6,0);
	this->articulacion.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}

void _pierna::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->extremidad.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.05,0);
	glRotatef(180,0,0,1);
	this->pie.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}

void _andy_android::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->torso.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.9,0);
	this->cabeza.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3,0.3,0);
	glScalef(1.5,1.5,1.5);
	this->brazo_izq.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3,0.3,0);
	glRotatef(180,0,1,0);
	glScalef(1.5,1.5,1.5);
	this->brazo_drch.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.35,-0.8,0);
	this->pierna_izq.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.35,-0.8,0);
	this->pierna_izq.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}