#ifndef PROYECTO_H
#define PROYECTO_H
#include <string>

class Proyecto
{
    public:
        std::string Nombre;
        std::string Codigo;
        std::string Prioridad;
        Proyecto(std::string codigo, std::string nombre, std::string prioridad);
        virtual ~Proyecto();

    protected:

    private:
};

#endif // PROYECTO_H
