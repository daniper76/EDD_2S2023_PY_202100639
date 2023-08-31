#ifndef LISTAEMPLEADOS_H
#define LISTAEMPLEADOS_H
#include "NodoEmpleados.h"
#include <string>

class ListaEmpleados
{
    public:
        NodoEmpleados *primero;
        int tamanio;
        void CargaMasiva(std::string archivo);
        void Mostrar();
        void InsertarEmpleado(std::string nombre,std::string password);
        bool Login(std::string nombre,std::string password);
        ListaEmpleados();
        virtual ~ListaEmpleados();



    protected:

    private:
};

#endif // LISTAEMPLEADOS_H
