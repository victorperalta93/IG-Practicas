// objeto por revolucion

_rotacion::rotacion(){

}


<
void rotacion(parametros)(vector<_vertex3f)

// vertices
for 
    for 
        vertice_aux.x = perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.z = perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].y;
        vertices[i+j*num_aux] = vertice_aux;


// caras

for
    for
        cara_aux._0 = i+((j+1)%num) * num_aux;
        cara_aux._1 = i+1+((j+1)%num)*num_aux;
        cara_aux._2 = i+1+j*num_aux;
        caras.push_back(cara_aux);

        cara_aux._0 = i+1+j*num_aux;
        cara_aux._1 = i+j*num_aux;
        cara_aux._2 = i+((j+1)%num)*num_aux;
        caras.push_back(cara_aux);


// tapa inferior

if(fabs(perfil[0].x) > 0.0){
    vertice_aux.x  =0.0;
    vertice_aux.y = perfil[0].y;
    vertice_aux.z = 0.0;
    vertices.push_back(vertice_aux);

    // última cara
    for
        cara_aux._0 = num_aux*num+2;
        cara_aux._1 = i+j*num_aux+num_aux-1;
        cara_aux._2 = (j+1)%num * num_aux-1;
}

// tapa superior