#include "ColaPrioridad.h"
#include <string>
using namespace std;


ColaPrioridad::ColaPrioridad()
{
    this->Primero = 0;
    this->Tamanio = 0;
}

ColaPrioridad::~ColaPrioridad()
{
    //dtor
}

void ColaPrioridad::Encolar(std::string Nombre, std::string Tipo_de_Prioridad)
{
    int numero_proyecto = 100 + this->Tamanio;
    Proyecto *nuevoProyecto = new Proyecto("PY-"+std::to_string(numero_proyecto),Nombre,Tipo_de_Prioridad);
    NodoCola *nuevoNodo = new NodoCola(nuevoProyecto,Tipo_de_Prioridad);
    if(this->Primero == 0)
    {
        this->Primero = nuevoNodo;
        this->Tamanio++;
    }else{
        NodoCola *aux = this->Primero;
        while(aux->Siguiente)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevoNodo;
        this->Tamanio++;
    }
}

void ColaPrioridad::VerProyectos()
{
    NodoCola *aux = this->Primero;
    int contador = 0;
    while(aux)
    {
        cout << "---------------------------------"<< endl;
        cout << aux->Proyecto_C->Nombre << endl;
        cout << aux->Proyecto_C->Codigo << endl;
        cout << aux->Prioridad << endl;
        cout << "---------------------------------"<< endl;
        aux = aux->Siguiente;
        contador++;
    }
}

void ColaPrioridad::Descolar()
{
    if(this->Primero)
    {
        this->Primero = this->Primero->Siguiente;
    }
}

void ColaPrioridad::Ordenar()
{
    if(this->Primero)
    {
        NodoCola *piv = this->Primero;
        NodoCola *actual;
        int contador = 0;
        while(contador != this->Tamanio)
        {
            actual = piv->Siguiente;
            while(actual)
            {
                if(piv->Prioridad.compare(actual->Prioridad) == 1)
                {
                    Proyecto *tempProyecto = piv->Proyecto_C;
                    std::string tempPrioridad = piv->Prioridad;
                    piv->Proyecto_C = actual->Proyecto_C;
                    piv->Prioridad = actual->Prioridad;
                    actual->Proyecto_C = tempProyecto;
                    actual->Prioridad = tempPrioridad;
                }
                actual = actual->Siguiente;
            }
            piv = piv->Siguiente;
            contador++;
        }
    }
}

void ColaPrioridad::GraficarCola()
{
    ofstream archivoCola;
    archivoCola.open("Cola.dot",ios::out);
    if(archivoCola.fail())
    {
        std::cout << "Se produjo un error" << endl;
    }else{
        archivoCola << "digraph migrafica{\n rankdir=LR; \n node[shape=record];\n" << textoGraficaCola() << "\n }";
        archivoCola.close();
    }
    try{
        system("dot -Tjpg Cola.dot -o Cola.jpg");
    }catch(exception e){
        std::cout << "Error al generar imagen";
    }

}

std::string ColaPrioridad::textoGraficaCola()
{
    std::string cuerpo = "";
    NodoCola *aux = this->Primero;
    for(int i = 0; i < this->Tamanio; i++)
    {
        cuerpo+="nodo";
        cuerpo+=std::to_string(i);
        cuerpo+="[label=\"";
        cuerpo+=aux->Proyecto_C->Codigo;
        cuerpo+="\\n";
        cuerpo+=aux->Prioridad;
        cuerpo+="\"];\n";
        aux = aux->Siguiente;
    }

    for(int i = 0; i < (this->Tamanio-1); i++)
    {
        cuerpo+="nodo";
        cuerpo+=std::to_string(i);
        cuerpo+=" -> nodo";
        cuerpo+=std::to_string(i+1);
        cuerpo+="\n";
    }
    return cuerpo;
}


