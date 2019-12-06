//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"
#include "robot.h"
#include "luz.h"

using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION,CONO,CILINDRO,ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=OBJETO_PLY;
_modo   modo=SOLID_ILLUMINATED_FLAT;
_material mat=ESTANDAR;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

// luces
//          		indice        posicion                 ambiente                  difusa                     especular		   
_luz luz_posicional(GL_LIGHT0, _vertex4f(5,0,0,1), _vertex4f(0.2,0.5,0.2,1), _vertex4f(0.3,0.8,0.3,1), _vertex4f(0.2,0.5,0.2,1));
_luz luz_direccional(GL_LIGHT1, _vertex4f(0,2,0,0), _vertex4f(0.2,0.2,0.2,1), _vertex4f(0.8,0.8,0.8,1), _vertex4f(0.5,0.5,0.5,1));

bool rotacion_luz      = true;
bool rotacion_robot    = true;
bool luz_p_activada    = true;
bool luz_d_activada    = true;
bool material_estandar = true;

// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_cono cono(0.5,1,10);
_cilindro cilindro(1,3,10);
_esfera esfera(5,1,20,false);
Robot robot;

// para movimiento
float valor = 2;
bool limite_piernas = false;
bool limite_brazos = false;

void set_material_gold(){
	_vertex4f ambiente_difusa = _vertex4f(1,0.84,0,1);
	_vertex4f especular = _vertex4f(1,0.84,0,1);
    float brillo = 5.0;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);
}


void clean_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
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
	switch (t_objeto){
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,mat);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,mat);break;
		case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2,mat);break;
		case ROTACION: 
			robot.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,1,mat);
			glTranslatef(5,0,0);
			break;
		case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,8,mat);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,10,mat);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,mat);break;
	}
}

void movimiento(){
	if(rotacion_luz){
		luz_posicional.rotacion += valor;
		luz_posicional.movimiento();
	}

	if(valor != 0 && rotacion_robot){
		if(robot.giro_brazo == robot.LIMITE_BRAZO)
			limite_brazos = true;
		else if(robot.giro_brazo == -robot.LIMITE_BRAZO)
			limite_brazos = false;

		if(limite_brazos)
			robot.giro_brazo-=valor; 
		else
			robot.giro_brazo+=valor; 


		if(robot.giro_pierna == robot.LIMITE_PIERNA)
			limite_piernas = true;
		else if(robot.giro_pierna == -robot.LIMITE_PIERNA)
			limite_piernas = false;

		if(limite_piernas)
			robot.giro_pierna-=valor; 
		else
			robot.giro_pierna+=valor; 

		robot.rotacion_robot += valor;

	}
	
	glutPostRedisplay();
}

//**************************************************************************
//
//***************************************************************************
void draw(void){
	if(luz_d_activada)
		luz_direccional.activar();

	if(luz_p_activada)
		luz_posicional.activar();

	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
	movimiento();
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
	Size_y=Size_x*Aspect_ratio;
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

void normal_key(unsigned char Tecla1,int x,int y){
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;
		case '5':modo=SOLID_ILLUMINATED_FLAT;break;
		case '6':modo=SOLID_ILLUMINATED_GOURAUD;break;

		case 'P':t_objeto=PIRAMIDE;break;
		case 'C':t_objeto=CUBO;break;
		case 'O':t_objeto=OBJETO_PLY;break;	
		case 'R':t_objeto=ROTACION;break;
		case 'N':t_objeto=CONO;break;
		case 'I':t_objeto=CILINDRO;break;
		case 'E':t_objeto=ESFERA;break;
		case 'M':
			robot.giro_brazo = 0;
			robot.giro_pierna = 0;
			robot.giro_cabeza = 0;

			if(valor==0) valor=2;
			else valor=0;
			break;
		case 'J':
			if(luz_d_activada){
				luz_direccional.desactivar();
				luz_d_activada = false;
			}
			else
				luz_d_activada = true;
			break;
		case 'K':
			if(luz_p_activada){
				luz_posicional.desactivar();
				luz_p_activada = false;
			}
			else
				luz_p_activada = true;
			break;
		case 'G':
			mat == ESTANDAR ? mat=ORO : mat=ESTANDAR;
			break;
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

void special_key(int Tecla1,int x,int y){
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		case GLUT_KEY_F1:robot.giro_cabeza+=3; break;
		case GLUT_KEY_F2:robot.giro_cabeza-=3; break;
		case GLUT_KEY_F5:
			if(valor == 0 && (robot.giro_brazo < robot.LIMITE_BRAZO))
				robot.giro_brazo+=2; 
			break;
		case GLUT_KEY_F6:
			if(valor == 0 && (robot.giro_brazo > -robot.LIMITE_BRAZO))
				robot.giro_brazo-=2; 
			break;
		case GLUT_KEY_F7:
			if(valor == 0 && (robot.giro_pierna < robot.LIMITE_PIERNA))
				robot.giro_pierna+=2; 
			break;
		case GLUT_KEY_F8:
			if(valor == 0 && (robot.giro_pierna > -robot.LIMITE_PIERNA))
				robot.giro_pierna-=2; 
			break;

	}
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
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************
int main(int argc, char *argv[] ){
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
	glutCreateWindow("PRACTICA - 2");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.parametros(argv[1]);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
