//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"
#include "file_ply_stl.hpp"
#include <algorithm>    // std::reverse
//*************************************************************************
// _puntos3D
//*************************************************************************
_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************
void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
	for (size_t i=0;i<vertices.size();i++){
		glVertex3fv((GLfloat *) &vertices[i]);
		}
	glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************
_triangulos3D::_triangulos3D(){	
	b_normales_caras = false;
	b_normales_vertices = false;

	ambiente_difusa = _vertex4f(0.4,0.4,0.4,1);
	especular = _vertex4f(0.4,0.4,0.4,1);
    brillo = 5.0;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (size_t i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************
void _triangulos3D::draw_solido(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);

	glBegin(GL_TRIANGLES);
	for (size_t i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************
void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_TRIANGLES);
	for (size_t i=0;i<caras.size();i++){
		if(i%2)
			glColor3f(r1,g1,b1);
		else
			glColor3f(r2,g2,b2);
			
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo iluminación plana
//*************************************************************************
void _triangulos3D::draw_iluminacion_plana(){
	if(!b_normales_caras)
		calcular_normales_caras();	

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	
	// Si ponemos el material aquí, se aplicará a todas las caras
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i <(int)caras.size(); ++i){
		glNormal3fv((GLfloat*) &normales_caras[i]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo iluminación suave (Gourand)
//*************************************************************************
void _triangulos3D::draw_iluminacion_suave(){
	if(!b_normales_vertices)
		calcular_normales_vertices();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i <(int)caras.size(); ++i){
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());

	_vertex3f a1,a2,n;
	for(unsigned long i=0; i<caras.size(); i++){
		// obtener dos vectores en el triangulo y calcular producto vectorial
		a1 = vertices[caras[i]._1]-vertices[caras[i]._0];
		a2 = vertices[caras[i]._2]-vertices[caras[i]._0];
		n=a1.cross_product(a2);

		// modulo
		float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);

		// normalización
		normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
	}

	b_normales_caras = true;
}

void _triangulos3D::calcular_normales_vertices(){
	normales_vertices.resize(vertices.size());

	vector<int> veces;
	veces.resize(normales_vertices.size());

	for(int i=0;i<(int)caras.size();i++){
		veces[caras[i]._0] += 1;
		normales_vertices[caras[i]._0] += normales_caras[i];

		veces[caras[i]._1] += 1;
		normales_vertices[caras[i]._1] += normales_caras[i];

		veces[caras[i]._2] += 1;
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for(int i=0;i<(int)normales_vertices.size();i++){
		normales_vertices[i] /= veces[i];
	}


	for(int i=0;i<(int)normales_vertices.size();i++){
		// modulo
		float m = sqrt(normales_vertices[i].x*normales_vertices[i].x
						+normales_vertices[i].y*normales_vertices[i].y
						+normales_vertices[i].z*normales_vertices[i].z);

		// normalización
		normales_vertices[i] = _vertex3f(normales_vertices[i].x/m, normales_vertices[i].y/m, normales_vertices[i].z/m);
	}

	b_normales_vertices = true;
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************
void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
		case SOLID:draw_solido(r1, g1, b1);break;
		case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
		case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************
_cubo::_cubo(float tam)
{
	// Vertices
	vertices.push_back(_vertex3f(-tam, -tam,  tam));
	vertices.push_back(_vertex3f( tam, -tam,  tam));
	vertices.push_back(_vertex3f( tam,  tam,  tam));
	vertices.push_back(_vertex3f(-tam,  tam,  tam));
    vertices.push_back(_vertex3f(-tam, -tam, -tam));
    vertices.push_back(_vertex3f( tam, -tam, -tam));
    vertices.push_back(_vertex3f( tam,  tam, -tam));
    vertices.push_back(_vertex3f(-tam,  tam, -tam));

    // Caras
    caras.push_back(_vertex3i(0, 1, 4));
    caras.push_back(_vertex3i(1, 5, 4));
    caras.push_back(_vertex3i(1, 2, 5));
    caras.push_back(_vertex3i(2, 6, 5));
    caras.push_back(_vertex3i(2, 3, 6));
    caras.push_back(_vertex3i(3, 7, 6));
    caras.push_back(_vertex3i(3, 0, 7));
    caras.push_back(_vertex3i(0, 4, 7));
    caras.push_back(_vertex3i(4, 5, 7));
    caras.push_back(_vertex3i(5, 6, 7));
    caras.push_back(_vertex3i(3, 2, 0));
    caras.push_back(_vertex3i(2, 1, 0));
}

//*************************************************************************
// clase piramide
//*************************************************************************
_piramide::_piramide(float tam, float al){
	vertices.resize(5); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}


//*************************************************************************
// clase cono
//*************************************************************************
 _cono::_cono(float radio, float altura, int num)
{
	_vertex3f vertice_aux;
	_vertex3i cara_aux;

	// tratamiento de los vértice
	vertices.resize(num+2);
	for (int j=0;j<num;j++){
		vertice_aux.x=radio*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-radio*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=0;
		vertices[j]=vertice_aux;
	}

	// punto central de la circunferencia
	vertice_aux.x=vertice_aux.y=vertice_aux.z=0;
	vertices[num]=vertice_aux;

	// tratamiento de las caras de la circunferencia
	for (int i=0;i<num;i++){
		cara_aux._0=i;

		// si es la última cara, se une el vértice con el primero
		if (i==num-1)
			cara_aux._1=0;
		else 
			cara_aux._1=(i+1);

		// el tercer vertice de la cara es siempre el centro
		cara_aux._2=num; 

		caras.push_back(cara_aux);
	}

	// punto superior del cono
	vertice_aux.x=vertice_aux.z=0;
	vertice_aux.y=altura;
	vertices[num+1]=vertice_aux;

	for (int i=0;i<num;i++){
		cara_aux._0=i;
		if (i==num-1)  
			cara_aux._1=0;
		else 
			cara_aux._1=(i+1);

		// el tercer vertice de la cara es siempre el pico
		cara_aux._2=num+1;
		caras.push_back(cara_aux);
	}
}

//*************************************************************************
// clase cilindro
//*************************************************************************
 _cilindro::_cilindro(float radio, float altura, int num){
	 this->radio = radio;
	 this->altura = altura;
	 this->num = num;

	 vector<_vertex3f> perfil = generar_perfil();
	 this->parametros(perfil,num,true,true,EJE_Y);
}

vector<_vertex3f> _cilindro::generar_perfil(){
	// Creación del perfil
	_vertex3f aux;
	vector<_vertex3f> perfil;

	float dist = altura/num;

	// perfil no es de 90 a 270 para evitar dibujar las tapas de la esfera
 	for (float i=0; i<=altura; i+=dist){
		aux.x = radio;
		aux.y = i;
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	return perfil;
}

//*************************************************************************
// clase esfera
//*************************************************************************
_esfera::_esfera(float latitud, float radio, float longitud, bool semi){
	this->latitud = latitud;
	this->longitud = longitud;
	this->radio = radio;

	vector<_vertex3f> perfil = generar_perfil(semi);
	this->parametros(perfil,longitud,true,true,EJE_Y);
}

vector<_vertex3f> _esfera::generar_perfil(bool semi){
	int grados = 270;
	if(semi)
		grados = 180;

	// Creación del perfil
	_vertex3f aux;
	vector<_vertex3f> perfil;

	// perfil no es de 90 a 270 para evitar dibujar las tapas de la esfera
 	for (int i=90+latitud; i<=grados-latitud; i+=latitud){
		aux.x = cos(i*(M_PI/180))*radio;
		aux.y = sin(i*(M_PI/180))*radio;
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	reverse(perfil.begin(),perfil.end());
	return perfil;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************
_objeto_ply::_objeto_ply() 
{
}


int _objeto_ply::parametros(char *archivo){
  int n_ver,n_car;

  vector<float> ver_ply ;
  vector<int>   car_ply ;
  
  _file_ply::read(archivo, ver_ply, car_ply );

  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);

  _vertex3f ver_aux;
  _vertex3i car_aux;

  for (int i=0;i<n_ver;i++){
    ver_aux.x=ver_ply[i*3];
    ver_aux.y=ver_ply[i*3+1];
    ver_aux.z=ver_ply[i*3+2];
    vertices[i]=ver_aux;
  }

  for (int i=0;i<n_car;i++){
    car_aux.x=car_ply[i*3];
    car_aux.y=car_ply[i*3+1];
    car_aux.z=car_ply[i*3+2];
    caras[i]=car_aux;
  }

  return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************
_rotacion::_rotacion()
{

}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, bool tapa_sup, bool tapa_inf, _eje eje)
{
	// tener en cuenta el sentido de la generatriz para las tapas
	if(perfil[0].y < perfil.back().y){
		bool au = tapa_sup;
		tapa_sup = tapa_inf;
		tapa_inf = au;
	}

	// tratamiento de los vértices
	//-----------------------------------------------------------------
	vertices.clear();
	_vertex3f aux;

	if(eje == EJE_Y){
		for (int j=0;j<num;j++) {
			for (int i=0;i<(int)perfil.size();i++) {
				aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
				aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
				aux.y=perfil[i].y;
				vertices.push_back(aux);
			}
		}
	}
	else if(eje == EJE_Z){
		for (int j=0;j<num;j++) {
			for (int i=0;i<(int)perfil.size();i++) {
				aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+perfil[i].y*sin(2.0*M_PI*j/(1.0*num));
				aux.y=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+perfil[i].y*cos(2.0*M_PI*j/(1.0*num));
				aux.z=perfil[i].z;
				vertices.push_back(aux);
			}
		}
	}
	else if(eje == EJE_X){
		for (int j=0;j<num;j++) {
			for (int i=0;i<(int)perfil.size();i++) {
				aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))+perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
				aux.z=-perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
				aux.x=perfil[i].x;
				vertices.push_back(aux);
			}
		}
	}

	//-----------------------------------------------------------------

	// tratamiento de las caras
	//-----------------------------------------------------------------
	_vertex3i cara_aux;

 	for(int i=0; i<num-1; ++i){
		for(int j=1; j<(int)perfil.size(); ++j){
			int actual = j + i*perfil.size();

			cara_aux._0 = actual;
			cara_aux._1 = actual-1;
			cara_aux._2 = actual-1 + perfil.size();
			caras.push_back(cara_aux);

			cara_aux._0 = actual;
			cara_aux._1 = actual-1 + perfil.size();
			cara_aux._2 = actual + perfil.size();
			caras.push_back(cara_aux);
		}
	}

  	// Último perfil con el primero
	for(int i=1; i<(int)perfil.size(); ++i){
		int actual = (num-1)*perfil.size()+i;
		int sig_perfil = i;

		cara_aux._0 = actual;
		cara_aux._1 = actual-1;
		cara_aux._2 = sig_perfil-1;
		caras.push_back(cara_aux);

		cara_aux._0 = actual;
		cara_aux._1 = sig_perfil-1;
		cara_aux._2 = sig_perfil;
		caras.push_back(cara_aux);
	} 
	//-----------------------------------------------------------------

 	// TAPA SUPERIOR
	//-----------------------------------------------------------------
	// añade el vertice centro de la tapa superior
	if(tapa_sup){
		if(eje == EJE_Y){
			aux.x = aux.z = 0.0;
			aux.y = perfil[0].y;
		}
		else if(eje == EJE_Z){
			aux.x = aux.y = 0.0;
			aux.z = perfil[0].z;
		}
		else if(eje == EJE_X){
			aux.y = aux.z = 0.0;
			aux.x = perfil[0].x;
		}

		vertices.push_back(aux);
		int centro = vertices.size()-1;

		for(int i=0; i<num-1; i++){
			int actual = i * perfil.size();
			cara_aux._0 = centro;
			cara_aux._1 = actual;
			cara_aux._2 = actual+perfil.size();
			caras.push_back(cara_aux);
		}
		
		//La última cara a mano
		cara_aux._0 = centro;
		cara_aux._1 = perfil.size()*(num-1);
		cara_aux._2 = 0;
		caras.push_back(cara_aux);
	}
	//-----------------------------------------------------------------


	// TAPA INFERIOR
	//-----------------------------------------------------------------
	// añade el vertice centro de la tapa inferior
	if(tapa_inf){		
		if(eje == EJE_Y){
			aux.x = aux.z = 0.0;
			aux.y = perfil.back().y;
		}
		else if(eje == EJE_Z){
			aux.x = aux.y = 0.0;
			aux.z = perfil.back().z;
		}
		else if(eje == EJE_X){
			aux.y = aux.z = 0.0;
			aux.x = perfil.back().x;
		}

		vertices.push_back(aux);
		int centro = vertices.size()-1;
		for(int i=1; i<num; i++){
			int actual = i * perfil.size()-1;
			cara_aux._0 = centro;
			cara_aux._1 = actual+ perfil.size();
			cara_aux._2 = actual;
			caras.push_back(cara_aux);
		}
		
		//La última cara a mano
		cara_aux._0 = centro;
		cara_aux._1 = perfil.size()-1;
		cara_aux._2 = perfil.size() * (num) -1;
		caras.push_back(cara_aux);
	}
	//-----------------------------------------------------------------
}