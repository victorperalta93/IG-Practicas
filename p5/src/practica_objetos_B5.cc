//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"
#include "robot.h"

using namespace std;

GLint viewport[4];
bool cambiar_vista = false;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION,CONO,CILINDRO,ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=ROTACION;
_modo   modo=SOLID;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;
int modo_objeto[5];
int estadoRaton[3], xc, yc, cambio=0;
int Ancho=450, Alto=450, tipo_camara=0;
float factor=1.0;

// variables para camara Ortho
float xx=2,yy=2;

// objetos
_rotacion rotacion; 
Robot robot;
vector<_vertex3f> colores;
vector<_vertex3f> colores_originales;
vector<_vertex3f> colores_seleccion;

vector<_vertex3i> colores_cilindro_seleccion;
vector<_vertex3f> colores_cilindro;
vector<_vertex3f> colores_cilindro_originales;

_esfera esfera(5,1,20,false);
_cilindro cilindro(0.4,1,10);

// para movimiento
float valor = 2;
bool limite_piernas = false;
bool limite_brazos = false;

void rellenar_colores(){
	colores.clear();
	colores_originales.clear();

	_vertex3f aux;
	aux.x = 0.5,aux.y = 0.5,aux.z = 0.5;
	colores.push_back(aux);
	aux.x = 0.0,aux.y = 0.0,aux.z = 0.0;
	colores.push_back(aux);
	aux.x = 0.0,aux.y = 0.0,aux.z = 0.0;
	colores.push_back(aux);
	aux.x = 0.8, aux.y = 0.8, aux.z = 0.8;
	colores.push_back(aux);
	aux.x = 0.8, aux.y = 0.8, aux.z = 0.8;
	colores.push_back(aux);
	aux.x = 1, aux.y = 1, aux.z = 1;
	colores.push_back(aux);
	aux.x = 1, aux.y = 1, aux.z = 1;
	colores.push_back(aux);
	aux.x = 0.5,aux.y = 0.5,aux.z = 0.5;
	colores.push_back(aux);
	aux.x = 0.0,aux.y = 0.0,aux.z = 0.0;
	colores.push_back(aux);
	aux.x = 0.0,aux.y = 0.0,aux.z = 0.0;
	colores.push_back(aux);

	for(int i=0;i<colores.size();i++){
		colores_originales.push_back(colores[i]);
	}
}

void rellenar_colores_seleccion(){
	colores_seleccion.clear();

	int inc=0;
	_vertex3f aux;
	for(int i=0;i<10;i++){
		aux.x = inc, aux.y = inc, aux.z = inc;
		colores_seleccion.push_back(aux);
		inc++;
	}
}

void rellenar_colores_caras(){
	_vertex3i color;
	for(int i=0;i<(int)cilindro.caras.size();i++){
		color.x = 255, color.y = i, color.z = 0;
		colores_cilindro_seleccion.push_back(color);
	}
}

void rellenar_colores_cilindro(){
	_vertex3f color;
	for(int i=0;i<(int)cilindro.caras.size();i++){
		if(i%2)
			color.x = 1, color.y = 0, color.z = 0;
		else
			color.x = 0, color.y = 0, color.z = 1;
		
		colores_cilindro.push_back(color);
	}

	for(int i=0;i<(int)colores_cilindro.size();i++){
		colores_cilindro_originales.push_back(colores_cilindro[i]);
	}
}

void pick_color(int x, int y);

void clean_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************
void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	if(tipo_camara==0)
		glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	else
		glOrtho(-xx*factor,xx*factor,-yy*factor,yy*factor,-100,100);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************
void change_observer(){
	change_projection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void draw_axis(){
	glDisable(GL_LIGHTING);
	glLineWidth(2);

	glBegin(GL_LINES);
		// eje X, color rojo
		glColor3f(1,0,0);
		glVertex3f(-AXIS_SIZE,0,0);
		glVertex3f(AXIS_SIZE,0,0);

		// eje Y, color verde
		glColor3f(0,1,0);
		glVertex3f(0,-AXIS_SIZE,0);
		glVertex3f(0,AXIS_SIZE,0);
		
		// eje Z, color azul
		glColor3f(0,0,1);
		glVertex3f(0,0,-AXIS_SIZE);
		glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************
void draw_objects(){
	robot.draw(modo,colores,1);

	glPushMatrix();
		glTranslatef(-1,0,0);
		cilindro.draw_solido_colores(colores_cilindro);
	glPopMatrix();
}

//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//***************************************************************************
void draw_objects_seleccion(){
	robot.draw(SEL_COLOR,colores_seleccion,1);

	glPushMatrix();
		glTranslatef(-1,0,0);
		cilindro.draw_seleccion_caras(colores_cilindro_seleccion);
	glPopMatrix();
}

void draw_basico(){
	glDrawBuffer(GL_FRONT);
	clean_window();

	glViewport(0,0,UI_window_width,UI_window_height);
	change_observer();
	draw_axis();
	draw_objects();

	// de nuevo para cada cámara

	// para que en GL_BACK los objetos tengan un color diferente y el pick funcione
	glDrawBuffer(GL_BACK);
	clean_window();
	change_observer();
	draw_objects_seleccion();
	glFlush();
}


//**************************************************************************
//
//***************************************************************************
void draw_4v(){
	//*****************************VIEWPORT 1**************************************************
	glDrawBuffer(GL_FRONT);
	clean_window();
	glViewport(0,0,UI_window_width/2,UI_window_height/2);

	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(45,1,0,0);
	glRotatef(45,0,1,0);

	draw_axis();
	draw_objects();
	// para que en GL_BACK los objetos tengan un color diferente y el pick funcione
	glDrawBuffer(GL_BACK);
	clean_window();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);

	draw_objects_seleccion();
	//*****************************VIEWPORT 1**************************************************

	//*****************************VIEWPORT 2**************************************************
	glDrawBuffer(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT );
    glViewport(UI_window_width/2, 0, UI_window_width/2, UI_window_height/2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(-45,0,1,0);
	glRotatef(-45,1,0,0);
	glRotatef(90,0,1,0);

	draw_axis();
	draw_objects();
	// para que en GL_BACK los objetos tengan un color diferente y el pick funcione
	glDrawBuffer(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);

	draw_objects_seleccion();
	//*****************************VIEWPORT 2**************************************************

	//*****************************VIEWPORT 3**************************************************
	glDrawBuffer(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT );
    glViewport(0, UI_window_height/2, UI_window_width/2, UI_window_height/2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(-90,0,1,0);
	glRotatef(90,1,0,0);

	draw_axis();
	draw_objects();
	// para que en GL_BACK los objetos tengan un color diferente y el pick funcione
	glDrawBuffer(GL_BACK);
	clean_window();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);

	draw_objects_seleccion();
	//*****************************VIEWPORT 3**************************************************

	//*****************************VIEWPORT 4**************************************************
	glDrawBuffer(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT );
    glViewport(UI_window_width/2, UI_window_height/2, UI_window_width/2, UI_window_height/2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(-90,1,0,0);
	

	draw_axis();
	draw_objects();
	// para que en GL_BACK los objetos tengan un color diferente y el pick funcione
	glDrawBuffer(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glMatrixMode(GL_MODELVIEW);

	draw_objects_seleccion();
	glFlush();
	//*****************************VIEWPORT 4**************************************************
}


void draw(void){
	if(cambiar_vista)
		draw_4v();
	else
		draw_basico();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(int Ancho1,int Alto1){
	float Aspect_ratio;

	Aspect_ratio=(float) Alto1/(float )Ancho1;
	Window_height=Window_width*Aspect_ratio;
	yy = xx*Aspect_ratio;

	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void normal_key(unsigned char Tecla1,int x,int y)
{
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '+':factor*=0.9;break;
		case '-':factor*=1.1;break;
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;
		case 'R':t_objeto=ROTACION;break;
		case 'C':tipo_camara==0 ? tipo_camara=1 : tipo_camara=0;break;
		case 'V':cambiar_vista==0 ? cambiar_vista=1 : cambiar_vista=0;break;
	}
	
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	glutPostRedisplay();
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y ){
	if(boton== GLUT_RIGHT_BUTTON) {
		if( estado == GLUT_DOWN) {
			estadoRaton[2] = 1;
			xc=x;
			yc=y;
		} 
		else estadoRaton[2] = 1;
	}

	if(boton== GLUT_LEFT_BUTTON) {
		if( estado == GLUT_DOWN) {
			estadoRaton[2] = 2;
			xc=x;
			yc=y;
			pick_color(xc, yc);
		} 
	}

	if(boton==3){
		if(tipo_camara == 0)
			Observer_distance/=1.2;
		else
			factor*=0.9;
		glutPostRedisplay();
	}
	
	if(boton==4){
		if(tipo_camara == 0)
			Observer_distance*=1.2;
		else
			factor*=1.1;
		glutPostRedisplay();
	}

  // falta añadir para el boton central con el zoom
  // esto tiene que cambiar el valor del factor, igual que el codigo de repag y avpag
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y){
	*x=Observer_angle_x;
	*y=Observer_angle_y;
}

/*************************************************************************/
void setCamara (GLfloat x, GLfloat y){
	Observer_angle_x=x;
	Observer_angle_y=y;
}


/*************************************************************************/
void RatonMovido( int x, int y ){
	float x0, y0, xn, yn; 
	if(estadoRaton[2]==1){
		getCamara(&x0,&y0);
		yn=y0+(y-yc);
		xn=x0-(x-xc);
		setCamara(xn,yn);
		xc=x;
		yc=y;
		glutPostRedisplay();
	}
}

//***************************************************************************
// Funciones para la seleccion
//************************************************************************
void procesar_color(unsigned char color[3])
{
	_vertex3f aux;
	aux.x = 1, aux.y = 1, aux.z = 0;

	if(colores[color[0]]._0 == 1 && colores[color[0]]._1 == 1 && colores[color[0]]._2 == 0)
		colores[color[0]] = colores_originales[color[0]];
	else if(!(color[0]== 255) && !(color[1] == 255) && !(color[2] == 255))
		colores[color[0]] = aux;
}

void procesar_color_caras(unsigned char color[3]){
	_vertex3f aux;
	aux.x = 1, aux.y = 1, aux.z = 0;

	if(colores_cilindro[color[1]]._0 == 1 && colores_cilindro[color[1]]._1 == 1 && colores_cilindro[color[1]]._2 == 0)
		colores_cilindro[color[1]] = colores_cilindro_originales[color[1]];
	else if(color[1] != 255)
		colores_cilindro[color[1]] = aux;
}

void pick_color(int x, int y){
	//GLint viewport[4];
	unsigned char pixel[3];

	//glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x,450-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
	printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

	if(pixel[0] == 255 && pixel[1] != 255)
		procesar_color_caras(pixel);
	else
		procesar_color(pixel);
	
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Window_width=.5;
	Window_height=.5;
	Front_plane=1;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);
	for (int i=0;i<5;i++) modo_objeto[i]=0;
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************
int main(int argc, char *argv[] ){
	rellenar_colores_seleccion();
	rellenar_colores();
	rellenar_colores_caras();
	rellenar_colores_cilindro();

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 5");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);

	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	// eventos ratón
	glutMouseFunc( clickRaton );
	glutMotionFunc( RatonMovido );

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
