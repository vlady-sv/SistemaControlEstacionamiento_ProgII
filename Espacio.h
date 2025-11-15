#ifndef ESPACIO_H
#define ESPACIO_H
#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Vehiculo.h"
#include "convenio.h"
using namespace std;
using namespace std::chrono;
using reloj = steady_clock;
using tiempo = steady_clock::time_point;

class Espacio{
    private:
        int numEspacio;
        Vehiculo* v;
        Convenio conv;
        tiempo llegada = reloj::now();
        tiempo salida = reloj::now();
        //tiempo duracion = duration_cast<minutes>(salida - llegada);         //////////////Obtener duracion - pasar a parte de Ticket
        string tarifa;

    public:
        Espacio(int, Vehiculo*, Convenio, string);
        Espacio(Espacio const &);

};


#endif 
