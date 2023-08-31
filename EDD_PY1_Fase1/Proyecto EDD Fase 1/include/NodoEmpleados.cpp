#include "NodoEmpleados.h"
#include <string>

NodoEmpleados::NodoEmpleados(std::string nombre,std::string password)
{
    this->siguiente=0;
    this->anterior=0;
    this->empleado=new Empleado(nombre,password);
}

NodoEmpleados::~NodoEmpleados()
{
    //dtor
}
