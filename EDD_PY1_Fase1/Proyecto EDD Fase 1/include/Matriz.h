#ifndef MATRIZ_H
#define MATRIZ_H
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include "NodoMatriz.h"
#include "NodoEmpleados.h"
#include "ColaPrioridad.h"
#include "Proyecto.h"
#include "Empleado.h"
#include "ListaEmpleados.h"
#include "ListaDoble.h"
#include "NodoListaDoble.h"
using namespace std;

class Matriz
{
    public:
        NodoMatriz *Raiz;
        int CoordenadaX;
        int CoordenadaY;
        void insertar_elemento(std::string proyecto, std::string encargado, int x, int y);
        NodoMatriz *nueva_columna(int x);
        NodoMatriz *nueva_fila(int y);
        NodoMatriz *insertar_fila(NodoMatriz *nuevo, NodoMatriz *cabeza_fila);
        NodoMatriz *insertar_columna(NodoMatriz *nuevo, NodoMatriz *cabeza_columna);
        NodoMatriz *buscarF(int y);
        NodoMatriz *buscarC(int x);
        void Graficar();
        void insertar_proyecto(ColaPrioridad *cola);
        void insertar_empleado(ListaEmpleados *lista);
        NodoMatriz *nueva_columna_1(int x, Proyecto *proyecto);
        NodoMatriz *nueva_fila_1(int y, Empleado *empleado);
        void asignarProyecto(std::string nombre_empleado, std::string codigo_proyecto,std::string codigo_empleado);
        NodoMatriz *buscarF_1(std::string nombre);
        NodoMatriz *buscarC_1(std::string codigo);
        void BuscarProyecto(std::string codigo, std::string nombre_tarea);
        void BuscarEmpleado(std::string codigo, std::string nombre_tarea, std::string nombre_empleado);
        void ImprimirCodigos();
        void ImprimirEmpleados();
        void ImprimirEmpleadosCodigos();
        void ImprimirTareasProyecto(std::string codigo);
        void Reporte();
        Matriz();
        virtual ~Matriz();

    protected:
        std::string Contenido();
    private:

};

#endif // MATRIZ_H
