#include "Empleado.h"

Empleado::Empleado(std::string nombre, std::string password)
{
    this->codigo = "";
    this->nombre = nombre;
    this->password = password;
    this->puesto = "";
}

Empleado::~Empleado()
{
    //dtor
}
