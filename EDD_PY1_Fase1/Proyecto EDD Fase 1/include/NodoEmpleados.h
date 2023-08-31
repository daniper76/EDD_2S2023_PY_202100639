#ifndef NODOEMPLEADOS_H
#define NODOEMPLEADOS_H
#include <string>
#include "Empleado.h"

class NodoEmpleados
{
    public:
        Empleado *empleado;
        NodoEmpleados *siguiente;
        NodoEmpleados *anterior;
        NodoEmpleados(std::string nombre,std::string password);
        virtual ~NodoEmpleados();

    protected:

    private:
};

#endif // NODOEMPLEADOS_H
