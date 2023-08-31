#include "ListaEmpleados.h"
#include <string>
#include "NodoEmpleados.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <sstream>
#include <stdlib.h>
using namespace std;

ListaEmpleados::ListaEmpleados()
{
    this->tamanio=0;
    this->primero=0;
}

ListaEmpleados::~ListaEmpleados()
{
    //dtor
}

void ListaEmpleados::InsertarEmpleado(std::string nombre,std::string password){
    NodoEmpleados *nuevo=new NodoEmpleados(nombre,password);
    if (this->primero==0){
        nuevo->siguiente=nuevo;
        nuevo->anterior=nuevo;
        this->primero=nuevo;
        this->tamanio++;
    }
    else
    {
        NodoEmpleados *aux=this->primero;
        int contador=1;
        while(contador<this->tamanio){
            aux=aux->siguiente;
            contador++;
        }
        aux->siguiente=nuevo;
        nuevo->anterior=aux;
        nuevo->siguiente=this->primero;
        this->primero->anterior=nuevo;
        this->tamanio++;

    }
}

void ListaEmpleados::CargaMasiva(std::string archivo){
    try
    {
        ifstream lectura;
        lectura.open(archivo, ios::in);
        bool encabezado = false;
        for(std::string fila; std::getline(lectura,fila);)
        {
            std::stringstream lineas(fila);
            std::string nombre;
            std::string password;
            if(encabezado)
            {
                getline(lineas, nombre, ',');
                getline(lineas, password, ',');
                this->InsertarEmpleado(nombre,password);
            }
            else{
                encabezado = true;
            }

        }
    }
    catch(exception)
    {
        cout << "No se pudo leer el archivo" << endl;
    }


}

void ListaEmpleados::Mostrar(){
    int contador=1;
    NodoEmpleados *aux = this->primero;
    if(this->tamanio==1){
        std::cout<<"Nombre:";
        std::cout<<aux->empleado->nombre;
        std::cout<<"\nPassword:";
        std::cout<<aux->empleado->password;
    }
    else{
        while(contador<=this->tamanio){
            std::cout<<"\nNombre:";
            std::cout<<aux->empleado->nombre;
            std::cout<<"\nPassword:";
            std::cout<<aux->empleado->password;
            aux=aux->siguiente;
            contador++;
        }
    }
}

bool ListaEmpleados::Login(std::string nombre,std::string password){
    int contador=0;
    NodoEmpleados *aux=this->primero;
    while(contador<this->tamanio){

        if (aux->empleado->nombre==nombre && aux->empleado->password==password){
            return true;
        }
        aux=aux->siguiente;
        contador++;
    }
    return false;
}

