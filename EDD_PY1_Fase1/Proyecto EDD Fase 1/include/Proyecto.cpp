#include "Proyecto.h"
#include <string>

Proyecto::Proyecto(std::string codigo, std::string nombre,std::string prioridad)
{
    this->Nombre = nombre;
    this->Codigo = codigo;
    this->Prioridad=prioridad;
}

Proyecto::~Proyecto()
{
    //dtor
}
