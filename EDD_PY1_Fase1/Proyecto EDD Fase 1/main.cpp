#include <iostream>
#include <string>
#include "ListaEmpleados.h"
#include "ColaPrioridad.h"
#include "ListaDoble.h"
#include "Matriz.h"

using namespace std;

int main()
{
    bool bandera=true;
    while(bandera){
    ListaEmpleados *listaEmpleados=new ListaEmpleados();
    ColaPrioridad *colaPrioridad=new ColaPrioridad();
    Matriz *matriz = new Matriz();
    int contador1=0;
    int contador2=0;
    int contador3=0;
    bool time=true;
    listaEmpleados->InsertarEmpleado("PM-202100639","password");
    std::cout<<"1-.Ingresar al sistema\n";
    std::cout<<"2-.Salir";
    std::cout<<"\nIngrese la opción que desea";
    std:string opcion;
    std::getline(std::cin, opcion);
    if (opcion=="1"){
            std::string nombre;
            std::string password;
            std::cout<<"Ingresar su usuario\n";
            std::getline(std::cin, nombre);
            std::cout<<"Ingresar sun contrasena \n";
            std::getline(std::cin, password);
            bool llave=listaEmpleados->Login(nombre,password);
            if (llave){
                while(true){
                    std::cout<<"1-.Cargar Empleados\n";
                    std::cout<<"2-.Crear Proyectos\n";
                    std::cout<<"3-.Asignar Proyectos\n";
                    std::cout<<"4-.Crear Tareas\n";
                    std::cout<<"5-.Asignar Tareas\n";
                    std::cout<<"6-.Generar Reporte\n";
                    std::cout<<"7-.Salir\n";
                    std::cout<<"Ingrese la opción que desee\n";
                    string opcion2;
                    std::getline(std::cin, opcion2);
                    if(opcion2=="1"){
                        while(true){
                            std::cout<<"1-.Carga Manual\n";
                            std::cout<<"2-.Carga Masiva\n";
                            string opcionCarga;
                            std::getline(std::cin, opcionCarga);
                            if(opcionCarga=="1"){
                                std::string nombreNuevo;
                                std::string password_Nueva;
                                std::cout<<"Ingresar el nuevo empleado\n";
                                std::getline(std::cin, nombreNuevo);
                                std::cout<<"Ingresar la nueva contrasena \n";
                                std::getline(std::cin, password_Nueva);
                                listaEmpleados->InsertarEmpleado(nombreNuevo,password_Nueva);
                                listaEmpleados->Mostrar();
                                std::cout<<"Empleado agregado \n";
                                break;
                            }
                            else if(opcionCarga=="2"){
                                listaEmpleados->CargaMasiva("empleados.csv");
                                listaEmpleados->Mostrar();
                                std::cout<<"Empleado agregado \n";
                                break;
                            }
                            else{
                              std::cout<<"Opcion Erronea\n";
                            }
                        }
                    }
                    else if(opcion2=="2"){
                        std::string nuevoProyecto;
                        std::string prioridadProyecto;
                        std::cout<<"-------------------Crear Proyecto--------------------- \n";
                        std::cout<<"Ingrese el nombre del Proyecto \n";
                        std::getline(std::cin, nuevoProyecto);
                        std::cout<<"Ingrese la prioridad del Proyecto \n";
                        std::getline(std::cin, prioridadProyecto);
                        colaPrioridad->Encolar(nuevoProyecto,prioridadProyecto);
                        colaPrioridad->Ordenar();
                        colaPrioridad->VerProyectos();
                    }
                    else if(opcion2=="3"){
                        if(time){
                            colaPrioridad->GraficarCola();
                            while(colaPrioridad->Primero)
                            {
                                matriz->insertar_proyecto(colaPrioridad);
                                colaPrioridad->Descolar();
                            }
                            matriz->insertar_empleado(listaEmpleados);
                            time=false;
                        }
                        std::string empleadoAsignado;
                        std::string codigoProyecto;
                        std::string codigoEmpleado;
                        std::string opcionCargoEmpleado;
                        std::cout<<"-------------------Asignar Proyecto--------------------- \n";
                        std::cout<<"Detalle de Proyectos\n";
                        matriz->ImprimirCodigos();
                        std::cout<<"Ingrese el codigo del Proyecto\n";
                        std::getline(std::cin, codigoProyecto);
                        std::cout<<"\nEmpleados:  \n";
                        matriz->ImprimirEmpleados();
                        std::cout<<"Ingrese el nombre del empleado\n";
                        std::getline(std::cin, empleadoAsignado);
                        std::cout<<"Cargos Disponibles para los Empleados\n";
                        std::cout<<"1-.Frontend Developer\n";
                        std::cout<<"2-.Backend Developer\n";
                        std::cout<<"3-. Quality Assurance\n";
                        std::cout<<"Elija el cargo\n";
                        std::getline(std::cin, opcionCargoEmpleado);
                        if(opcionCargoEmpleado=="1"){
                            codigoEmpleado=(contador1 < 100 ? (contador1 < 10 ? "FDEV-00"+std::to_string(contador1) : "FDEV-0"+std::to_string(contador1)): "FDEV-"+std::to_string(contador1));
                        }
                        else if(opcionCargoEmpleado=="2"){
                            codigoEmpleado=(contador2 < 100 ? (contador2 < 10 ? "BDEV-00"+std::to_string(contador2) : "BDEV-0"+std::to_string(contador2)): "BDEV-"+std::to_string(contador2));
                        }
                        else if(opcionCargoEmpleado=="3"){
                            codigoEmpleado=(contador3 < 100 ? (contador3 < 10 ? " QA-00"+std::to_string(contador3) : " QA-0"+std::to_string(contador3)): " QA-"+std::to_string(contador3));
                        }
                        else{
                            std::cout<<"Otra opción";
                        }
                        matriz->asignarProyecto(empleadoAsignado,codigoProyecto,codigoEmpleado);
                    }
                    else if(opcion2=="4"){
                        std::string tarea;
                        std::string codigoProyectoTarea;
                        std::cout<<"-------------------Crear Tarea--------------------- \n";
                        std::cout<<"Detalle de Proyectos \n";
                        matriz->ImprimirCodigos();
                        std::cout<<"Ingrese el código del Proyecto \n";
                        std::getline(std::cin, codigoProyectoTarea);
                        std::cout<<"Ingrese el nombre de la Tarea \n";
                        std::getline(std::cin, tarea);
                        matriz->BuscarProyecto(codigoProyectoTarea,tarea);
                    }
                    else if(opcion2=="5"){
                        std::string tareaElegir;
                        std::string codigoProyectoTareaElegir;
                        std::string codigoEmpleadoAsignar;
                        std::cout<<"-------------------Asignar Tarea--------------------- \n";
                        std::cout<<"****Detalle de Proyectos \n";
                        matriz->ImprimirCodigos();
                        std::cout<<"Ingrese el codigo del Proyecto \n";
                        std::getline(std::cin, codigoProyectoTareaElegir);
                        std::cout<<"\n****Detalle Tareas \n";
                        matriz->ImprimirTareasProyecto(codigoProyectoTareaElegir);
                        std::cout<<"\nIngrese el nombre de la Tarea \n";
                        std::getline(std::cin, tareaElegir);
                        std::cout<<"\n****Detalle Empleados \n";
                        matriz->ImprimirEmpleadosCodigos();
                        std::cout<<"\nIngrese el codigo del Empleado \n";
                        std::getline(std::cin, codigoEmpleadoAsignar);
                        matriz->BuscarEmpleado(codigoProyectoTareaElegir,tareaElegir,codigoEmpleadoAsignar);
                    }
                    else if(opcion2=="6"){
                        matriz->Graficar();
                        matriz->Reporte();
                    }
                    else if(opcion2=="7"){
                        break;
                    }
                }
             }

    }
    else if(opcion=="2"){
            bandera=false;
    }
    else{
        std::cout<<"Ingrese una opción válida";
    }
    }
    return 0;
}
