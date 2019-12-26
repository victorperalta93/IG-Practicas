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

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION,CONO,CILINDRO,ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=ROTACION;
_modo   modo=SOLID;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;
int modo_objeto[5];
int estadoRaton[3], xc, yc, cambio=0;
int Ancho=450, Alto=450, tipo_camara=1;
float factor=1.0;

// objetos
_rotacion rotacion; 
Robot robot;
_esfera esfera(5,1,20,false);

// para movimiento
float valor = 2;
bool limite_piernas = false;
bool limite_brazos = false;

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
		glFrustum(-Window_width,Window_width,-Window_high,Window_high,Front_plane,Back_plane);
	else
		glOrtho(-2*factor,2*factor,-2*factor,2*factor,-100,100);
	// P5: hay que cmabiar Frustum por Orto para la camara ortogonal
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************
void change_observer(){
	// PARA P5:
	// posicion del observador
	//change_projection();
	glViewport(0,0,Ancho,Alto);
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
void draw_objects()
{
	robot.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,1);
}

//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//***************************************************************************
void draw_objects_seleccion(){
	int inc=20;
	robot.draw_seleccion_color(100+inc,100+inc,100+inc);

	/* switch (t_objeto){
		case CUBO: cubo.draw_seleccion_color(100,100,100);inc+=20;break;
		case PIRAMIDE: piramide.draw_seleccion_color(100+inc,100+inc,100+inc);inc+=20;break;
		case OBJETO_PLY: ply.draw_seleccion_color(100+inc,100+inc,100+inc);inc+=20;break;
		case ROTACION: 
			inc+=20;
			glTranslatef(5,0,0);
			break;
		case CONO: cono.draw_seleccion_color(100+inc,100+inc,100+inc);inc+=20;break;
		case CILINDRO: cilindro.draw_seleccion_color(100+inc,100+inc,100+inc);inc+=20;break;
		case ESFERA: esfera.draw_seleccion_color(100+inc,100+inc,100+inc);inc+=20;break;
	} */
}

//**************************************************************************
//
//***************************************************************************
void draw(void){
	glDrawBuffer(GL_FRONT);
	clean_window();
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

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(int Ancho1,int Alto1)
{
	change_projection();
	Ancho=Ancho1;
	Alto=Alto1;
	draw();
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
	switch (color[0]){
		case 100: 
			modo_objeto[0] == 0 ? modo_objeto[0]=1 : modo_objeto[0]=0;
			modo_objeto[0] == 0 ? cambio=1 : cambio=0;
			break; 
		case 120: 
			modo_objeto[1] == 0 ? modo_objeto[1]=1 : modo_objeto[1]=0;
			modo_objeto[1] == 0 ? cambio=1 : cambio=0;
			break;
		case 140:
			modo_objeto[2] == 0 ? modo_objeto[2]=1 : modo_objeto[2]=0;
			modo_objeto[2] == 0 ? cambio=1 : cambio=0;
			break; 
		case 160: 
			modo_objeto[3] == 0 ? modo_objeto[3]=1 : modo_objeto[3]=0;
			modo_objeto[3] == 0 ? cambio=1 : cambio=0;
			break;
		case 180: 
			modo_objeto[4] == 0 ? modo_objeto[4]=1 : modo_objeto[4]=0;
			modo_objeto[4] == 0 ? cambio=1 : cambio=0;
			break;
	}

/* 	if (cambio==1){
		obj->r=0.3;
		obj->g=0.9;
		obj->b=0.3;
	}

	if (cambio==0){
		obj->r=0.9;
		obj->g=0.6;
		obj->b=0.2;
	} 
 */
}

void pick_color(int x, int y){
	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
	printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

	procesar_color(pixel);
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=20*Front_plane;
	Observer_angle_x=20;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);
	for (int i=0;i<5;i++) modo_objeto[i]=0;
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************
int main(int argc, char *argv[] ){
	// perfil 
	vector<_vertex3f> perfil2;
	_vertex3f aux;

	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil2.push_back(aux);

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
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x,Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width,Window_high);

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
