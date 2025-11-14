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
        Vehiculo* v;
        Convenio conv;
        tiempo llegada = reloj::now();
        tiempo salida = reloj::now();
        int tarifa; //Ver si tarifa se hace como una clase mas o se maneja directo

    public:
};


#endif 
