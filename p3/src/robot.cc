#include "objetos_B3.h"
#include "robot.h"

Cabeza::Cabeza(){
	craneo = new _esfera(5,1,20,false);
	oreja_izq = new _cilindro(0.05,0.5,20);
	oreja_dcha = new _cilindro(0.05,0.5,20);
}

Cabeza::~Cabeza(){
	delete craneo;
	delete oreja_izq;
	delete oreja_dcha;
}


void Cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	this->craneo->draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4,0.9,0);
	glRotatef(15.0,0,0,1);
	this->oreja_izq->draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,0.9,0);
	glRotatef(-15.0,0,0,1);
	this->oreja_dcha->draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}

void Robot::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	glTranslatef(0,1.9,0);
	this->cabeza.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();
}