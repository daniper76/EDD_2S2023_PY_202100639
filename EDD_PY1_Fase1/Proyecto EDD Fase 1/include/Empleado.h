#ifndef EMPLEADO_H
#define EMPLEADO_H
#include <string>

class Empleado
{
    public:
        std::string nombre;
        std::string password;
        std::string codigo;
        std::string puesto;
        Empleado(std::string nombre, std::string password);
        virtual ~Empleado();

    protected:

    private:
};

#endif // EMPLEADO_H
