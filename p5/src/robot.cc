#include "objetos_B5.h"
#include "robot.h"

// ---------------------------------------------------------------------------------------------------------
Cabeza::Cabeza(){
	craneo = new _esfera(5,1,20,false);
	oreja_izq = new _cilindro(0.2,0.05,20);
	oreja_dcha = new _cilindro(0.2,0.05,20);
	ojo_izq = new _cilindro(0.25,0.2,20);
	ojo_dcha = new _cilindro(0.25,0.2,20);
	pupila_dcha = new _cilindro(0.22,0.05,20);
	pupila_izq = new _cilindro(0.22,0.05,20);
}

Cabeza::~Cabeza(){
	delete craneo;
	delete oreja_izq;
	delete oreja_dcha;
	delete ojo_dcha;
	delete ojo_izq;
	delete pupila_dcha;
	delete pupila_izq;
}


void Cabeza::draw(_modo modo,vector<_vertex3f> colores, float grosor){
	glPushMatrix();
	this->craneo->draw(modo,colores[0]._0,colores[0]._1,colores[0]._2,colores[0]._0,colores[0]._1,colores[0]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,0,0);
	glRotatef(90.0,0,0,1);
	this->oreja_izq->draw(modo,colores[1]._0,colores[1]._1,colores[1]._2,colores[1]._0,colores[1]._1,colores[1]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.05,0,0);
	glRotatef(90.0,0,0,1);
	this->oreja_dcha->draw(modo,colores[2]._0,colores[2]._1,colores[2]._2,colores[2]._0,colores[2]._1,colores[2]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,0.4,0.75);
	glRotatef(90.0,1,0,0);
	this->ojo_izq->draw(modo,colores[3]._0,colores[3]._1,colores[3]._2,colores[3]._0,colores[3]._1,colores[3]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4,0.4,0.75);
	glRotatef(90.0,1,0,0);
	this->ojo_dcha->draw(modo,colores[4]._0,colores[4]._1,colores[4]._2,colores[4]._0,colores[4]._1,colores[4]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,0.4,0.92);
	glRotatef(90.0,1,0,0);
	this->pupila_dcha->draw(modo,colores[5]._0,colores[5]._1,colores[5]._2,colores[5]._0,colores[5]._1,colores[5]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4,0.4,0.92);
	glRotatef(90.0,1,0,0);
	this->pupila_izq->draw(modo,colores[6]._0,colores[6]._1,colores[6]._2,colores[6]._0,colores[6]._1,colores[6]._2,grosor);
	glPopMatrix();

}
// ---------------------------------------------------------------------------------------------------------
Torso::Torso(){
	cuerpo = new _cilindro(1,2,20);
	cuello = new _cilindro(0.2,0.5,20);
	torso_inferior = new _esfera(5,1,20,true);
}

Torso::~Torso(){
	delete cuerpo;
	delete cuello;
	delete torso_inferior;
}

void Torso::draw(_modo modo, vector<_vertex3f> colores, float grosor){
	glPushMatrix();
	this->cuerpo->draw(modo,colores[7]._0,colores[7]._1,colores[7]._2,colores[7]._0,colores[7]._1,colores[7]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,2,0);
	this->cuello->draw(modo,colores[8]._0,colores[8]._1,colores[8]._2,colores[8]._0,colores[8]._1,colores[8]._2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.1,0);
	glRotatef(180,0,0,1);
	this->torso_inferior->draw(modo,colores[9]._0,colores[9]._1,colores[9]._2,colores[9]._0,colores[9]._1,colores[9]._2,grosor);
	glPopMatrix();

}

void Robot::draw(_modo modo, vector<_vertex3f> colores, float grosor){
	glPushMatrix();
		glScalef(0.4,0.4,0.4);

		glPushMatrix();
		glTranslatef(0,3.2,0);
		this->cabeza.draw(modo,colores,grosor);
		glPopMatrix();

		glPushMatrix();
		this->torso.draw(modo,colores,grosor);
		glPopMatrix();
	glPopMatrix();
}