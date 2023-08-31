#include "Matriz.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
Matriz::Matriz()
{
    this->Raiz = new NodoMatriz(new Proyecto("RAIZ","",""),new Empleado("",""),-1,-1);
    this->CoordenadaX = 0;
    this->CoordenadaY = 0;
}

Matriz::~Matriz()
{
    //dtor
}

NodoMatriz* Matriz::buscarF(int y)
{
    NodoMatriz *aux = this->Raiz;
    while(aux != 0)
    {
        if(aux->PosY == y)
        {
            return aux;
        }
        aux = aux->Abajo;
    }
    return 0;
}

NodoMatriz* Matriz::buscarC(int x)
{
    NodoMatriz *aux = this->Raiz;
    while(aux != 0)
    {
        if(aux->PosX == x)
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return 0;
}

NodoMatriz* Matriz::insertar_columna(NodoMatriz *nuevo, NodoMatriz *cabeza_columna)
{
    NodoMatriz *temp = cabeza_columna;
    bool piv = false;
    while(true)
    {
        if(temp->PosX==nuevo->PosX){
            temp->PosY = nuevo->PosY;
            temp->Encargado_c = nuevo->Encargado_c;
            temp->Proyecto_c = nuevo->Proyecto_c;
            return temp;
        }else if(temp->PosX > nuevo->PosX){
            piv=true;
            break;
        }
        if(temp->Siguiente){
            temp = temp->Siguiente;
        }else{
            break;
        }
    }
    if(piv)
    {
        nuevo->Siguiente = temp;
        temp->Anterior->Siguiente = nuevo;
        nuevo->Anterior=temp->Anterior;
        temp->Anterior=nuevo;
    }
    else
    {
        temp->Siguiente=nuevo;
        nuevo->Anterior=temp;
    }
    return nuevo;
}

NodoMatriz* Matriz::insertar_fila(NodoMatriz *nuevo, NodoMatriz *cabeza_fila)
{
    NodoMatriz *temp = cabeza_fila;
    bool piv = false;
    while(true)
    {
        if(temp->PosY==nuevo->PosY){
            temp->PosX = nuevo->PosX;
            temp->Encargado_c = nuevo->Encargado_c;
            temp->Proyecto_c = nuevo->Proyecto_c;
            return temp;
        }else if(temp->PosY > nuevo->PosY){
            piv=true;
            break;
        }
        if(temp->Abajo){
            temp = temp->Abajo;
        }else{
            break;
        }
    }
    if(piv)
    {
        nuevo->Abajo = temp;
        temp->Arriba->Abajo = nuevo;
        nuevo->Arriba = temp->Arriba;
        temp->Arriba = nuevo;
    }
    else
    {
        temp->Abajo = nuevo;
        nuevo->Arriba = temp;
    }
    return nuevo;
}

NodoMatriz* Matriz::nueva_columna_1(int x, Proyecto *proyecto)
{
    NodoMatriz *columna = this->insertar_columna(new NodoMatriz(proyecto, 0, x, -1), this->Raiz);
    return columna;
}

void Matriz::insertar_proyecto(ColaPrioridad *cola)
{
    NodoMatriz *nodo_Columna = this->nueva_columna_1(this->CoordenadaX, cola->Primero->Proyecto_C);
    this->CoordenadaX++;
}

NodoMatriz* Matriz::nueva_fila_1(int y, Empleado *encargado)
{
    NodoMatriz *fila = this->insertar_fila(new NodoMatriz(0, encargado, -1, y), this->Raiz);
    return fila;
}

void Matriz::insertar_empleado(ListaEmpleados *lista)
{
    //
    NodoEmpleados *aux = lista->primero;
    int contador = 0;
    while(lista->tamanio > contador)
    {
        this->nueva_fila_1(this->CoordenadaY, aux->empleado);
        aux = aux->siguiente;
        contador++;
        this->CoordenadaY++;
    }
}

void Matriz::asignarProyecto(std::string nombre_empleado, std::string codigo_proyecto,std::string codigo_empleado)
{
    NodoMatriz *nodo_Columna =  this->buscarC_1(codigo_proyecto);
    NodoMatriz *nodo_Fila = this->buscarF_1(nombre_empleado);

    NodoMatriz *nuevo = new NodoMatriz(nodo_Columna->Proyecto_c, nodo_Fila->Encargado_c, nodo_Columna->PosX, nodo_Fila->PosY);
    nuevo->Encargado_c->codigo=codigo_empleado;
    if(nodo_Columna != 0 && nodo_Fila !=0 ){
        nuevo=this->insertar_columna(nuevo, nodo_Fila);
        nuevo=this->insertar_fila(nuevo, nodo_Columna);
        return;
    }
    else{
        cout << "Se podrujo un error al insertar el nuevo nodo" << endl;
    }
}

NodoMatriz* Matriz::buscarF_1(std::string nombre)
{
    NodoMatriz *aux = this->Raiz;
    while(aux != 0)
    {
        if(aux->Encargado_c->nombre.compare(nombre) == 0)
        {
            return aux;
        }
        aux = aux->Abajo;
    }
    return 0;
}

NodoMatriz* Matriz::buscarC_1(std::string codigo)
{
    NodoMatriz *aux = this->Raiz;
    while(aux != 0)
    {
        if(aux->Proyecto_c->Codigo.compare(codigo) == 0)
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return 0;
}

void Matriz::BuscarProyecto(std::string codigo, std::string nombre_tarea)
{
    NodoMatriz *nodo_Columna =  this->buscarC_1(codigo);
    nodo_Columna->Tareas->Insertar(codigo, nombre_tarea, "");
}

void Matriz::BuscarEmpleado(std::string codigo, std::string nombre_tarea, std::string nombre_empleado)
{
    NodoMatriz *nodo_Columna =  this->buscarC_1(codigo);
    NodoMatriz *nodo_Fila = this->buscarF_1(nombre_empleado);
    if(nodo_Fila != 0)
    {
        nodo_Columna->Tareas->Asignar(nodo_Columna->Proyecto_c->Codigo, nombre_tarea, nodo_Fila->Encargado_c->codigo);
    }
    else
    {
        cout << "No hay empleado con ese nombre" << endl;
    }
}

void Matriz::Graficar()
{
    ofstream archivo;
    std::string texto = "";
	std::string nombre_archivo = "matriz.dot";
	std::string nombre_imagen = "matriz.jpg";
	NodoMatriz *aux1 = this->Raiz;
	NodoMatriz *aux2 = this->Raiz;
	NodoMatriz *aux3 = this->Raiz;
	archivo.open(nombre_archivo, ios::out);
	if ( aux1 != 0 ) {
		archivo << "digraph MatrizCapa{ \n node[shape=box] \n rankdir=UD;\n";

        while( aux2 != 0 ) {
            aux1 = aux2;
            archivo << "{rank=same; \n";
            while( aux1 != 0 ) {
                if(aux1->Proyecto_c)
                {
                    if(aux1->Encargado_c)
                    {
                        archivo << "nodo" << aux1 << "[label=\"" << aux1->Proyecto_c->Codigo << "\\n" << aux1->Encargado_c->codigo << "\" ,group=" << (aux1->PosX+1) << "]; \n";
                    }else{
                        archivo << "nodo" << aux1 << "[label=\"" << aux1->Proyecto_c->Codigo << "\" ,group=" << (aux1->PosX+1) << "]; \n";
                    }
                }else if(aux1->Encargado_c)
                {
                    archivo << "nodo" << aux1 << "[label=\"" << aux1->Encargado_c->nombre << "\" ,group=" << (aux1->PosX+1) << "]; \n";
                }
                aux1 = aux1->Siguiente;
            }
            archivo << "} \n";
            aux2 = aux2->Abajo;
        }

        aux2 = aux3;
        while( aux2 != 0 ) {
            aux1 = aux2;
            while( aux1->Siguiente != 0 ) {
                archivo << "nodo" << aux1 << " -> " << "nodo" << aux1->Siguiente << " [dir=both];\n";
                aux1 = aux1->Siguiente;
            }
            aux2 = aux2->Abajo;
        }
        aux2 = aux3;
        while( aux2 != 0 ) {
            aux1 = aux2;
            while( aux1->Abajo != 0 ) {
                archivo << "nodo" << aux1 << " -> " << "nodo" << aux1->Abajo << " [dir=both];\n";
                aux1 = aux1->Abajo;
            }
            aux2 = aux2->Siguiente;
        }
        archivo << "} \n";
	} else {
		texto = "No hay elementos en la matriz";
	}

	archivo.close();
    std::string codigo_cmd="dot -Tjpg ";
    codigo_cmd+=nombre_archivo;
    codigo_cmd+=" -o ";
    codigo_cmd+=nombre_imagen;
    char j[codigo_cmd.size()+1];
    strcpy(j,codigo_cmd.c_str());
    cout << j << endl;
    system(j);
}


void Matriz::ImprimirCodigos()
{
    NodoMatriz *aux = this->Raiz;
    NodoMatriz *temp=aux->Siguiente;
    while(temp != 0)
    {
        std::cout<<"\n-------------------------\n";
        std::cout<<"\nNombre del Proyecto\n";
        std::cout<<temp->Proyecto_c->Nombre;
        std::cout<<"\n*Codigos de Proyectos\n";
        std::cout<<temp->Proyecto_c->Codigo;
        std::cout<<"\n-------------------------\n";
        temp = temp->Siguiente;
    }
}

void Matriz::ImprimirEmpleados()
{
    NodoMatriz *aux = this->Raiz;
    NodoMatriz *temp=aux->Abajo;
    while(temp != 0)
    {
        std::cout<<"\n-------------------------\n";
        std::cout<<"Nombre del Empleado\n";
        std::cout<<temp->Encargado_c->nombre;
        std::cout<<"\n-------------------------\n";
        temp = temp->Abajo;
    }
}



void Matriz::ImprimirEmpleadosCodigos()
{
    NodoMatriz *aux = this->Raiz;
    NodoMatriz *temp=aux->Abajo;
    while(temp != 0)
    {
        std::cout<<"-------------------------\n";
        std::cout<<"Nombre del Empleado\n";
        std::cout<<temp->Encargado_c->nombre;
        std::cout<<"*Codigo del Empleado\n";
        std::cout<<temp->Encargado_c->codigo;
        std::cout<<"-------------------------\n";
        temp = temp->Abajo;
    }
}

void Matriz::ImprimirTareasProyecto(std::string codigo)
{
    NodoMatriz *nodo_Columna =  this->buscarC_1(codigo);
    if(true)
    {
        nodo_Columna->Tareas->ImprimirTarea();
    }
    else
    {
        cout << "No hay empleado con ese nombre" << endl;
    }
}


void Matriz::Reporte()
{
    ofstream archivoReporte;
    archivoReporte.open("Proyecto.json",ios::out);
    if(archivoReporte.fail())
    {
        std::cout << "Se produjo un error" << endl;
    }else{
        archivoReporte << "{\n\t\"Proyectos\":[\n" << Contenido() << "\t]\n}";
        archivoReporte.close();
}
}

std::string Matriz::Contenido()
{

    std::string cuerpo = "";
    NodoMatriz *aux = this->Raiz;
    NodoMatriz *temp=aux->Siguiente;
    while(temp != 0)
    {
        if(temp->Siguiente!= 0){
            cuerpo+="\t\t{\n";
            cuerpo+="\t\t\t\"id\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Codigo;
            cuerpo+="\",\n";
            cuerpo+="\t\t\t\"nombre\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Nombre;
            cuerpo+="\",\n";
            cuerpo+="\t\t\t\"tareas\":[";
            NodoListaDoble *tarea=temp->Tareas->Primero;
            while(tarea!= 0){
                if(tarea->Siguiente!=0){
                    cuerpo+="\t\t\t\t{\n";
                    cuerpo+="\t\t\t\t\t\"nombre\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Nombre_Tarea;
                    cuerpo+="\",\n";
                    cuerpo+="\t\t\t\t\t\"empleado\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Codigo_Encargado;
                    cuerpo+="\"\n";
                    cuerpo+="\t\t\t\t},\n";
                }
                else if(tarea->Siguiente==0){
                    cuerpo+="\t\t\t\t{\n";
                    cuerpo+="\t\t\t\t\t\"nombre\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Nombre_Tarea;
                    cuerpo+="\",\n";
                    cuerpo+="\t\t\t\t\t\"empleado\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Codigo_Encargado;
                    cuerpo+="\"\n";
                    cuerpo+="\t\t\t\t}\n";
                }
                tarea=tarea->Siguiente;

            }
            cuerpo+="\t\t\t],";
            cuerpo+="\t\t\t\"prioridad\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Prioridad;
            cuerpo+="\"";
            cuerpo+="\t\t\t},";
        }
        else if(temp->Siguiente== 0){
            cuerpo+="\t\t{\n";
            cuerpo+="\t\t\t\"id\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Codigo;
            cuerpo+="\",\n";
            cuerpo+="\t\t\t\"nombre\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Nombre;
            cuerpo+="\",\n";
            cuerpo+="\t\t\t\"tareas\":[";
            NodoListaDoble *tarea=temp->Tareas->Primero;
            while(tarea!= 0){
                if(tarea->Siguiente!=0){
                    cuerpo+="\t\t\t\t{\n";
                    cuerpo+="\t\t\t\t\t\"nombre\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Nombre_Tarea;
                    cuerpo+="\",\n";
                    cuerpo+="\t\t\t\t\t\"empleado\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Codigo_Encargado;
                    cuerpo+="\"\n";
                    cuerpo+="\t\t\t\t},\n";
                }
                else if(tarea->Siguiente==0){
                    cuerpo+="\t\t\t\t{\n";
                    cuerpo+="\t\t\t\t\t\"nombre\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Nombre_Tarea;
                    cuerpo+="\",\n";
                    cuerpo+="\t\t\t\t\t\"empleado\":";
                    cuerpo+="\"";
                    cuerpo+=tarea->Codigo_Encargado;
                    cuerpo+="\"\n";
                    cuerpo+="\t\t\t\t}\n";
                }
                tarea=tarea->Siguiente;

            }
            cuerpo+="\t\t\t],";
            cuerpo+="\t\t\t\"prioridad\":";
            cuerpo+="\"";
            cuerpo+=temp->Proyecto_c->Prioridad;
            cuerpo+="\"";
            cuerpo+="\t\t\t}";
        }
        temp=temp->Siguiente;
        }

    return cuerpo;


}
