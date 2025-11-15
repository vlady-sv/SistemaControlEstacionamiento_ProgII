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
        Convenio* conv;
        tiempo llegada = reloj::now();
        tiempo salida = reloj::now();
        //tiempo duracion = duration_cast<minutes>(salida - llegada);         //////////////Obtener duracion - pasar a parte de Ticket
        string tarifa;

    public:
        Espacio(int, Vehiculo*, Convenio*, string);
        Espacio(Espacio const &);
        void set_numEspacio(int);
        void set_vehiculo(Vehiculo*);
        void set_convenio(Convenio*);
        void set_llegada(tiempo);
        void set_salida(tiempo);
        void set_tarifa(string);
        int get_numEspacio();
        Vehiculo* get_vehiculo();
        Convenio* get_convenio();
        tiempo get_llegada();
        tiempo get_salida();
        string get_tarifa();
        void mostrarEspacio();

};

Espacio::Espacio(int numEspacio, Vehiculo* v, Convenio* conv, string tarifa){
    this->numEspacio = numEspacio;
    this->v = v;
    this->conv = conv;
    this->tarifa = tarifa;
}

Espacio::Espacio(Espacio const &obj){
    numEspacio = obj.numEspacio;
    v = obj.v;
    conv = obj.conv;
    tarifa = obj.tarifa;
}

void Espacio::set_numEspacio(int numEspacio){
    this->numEspacio = numEspacio;
}

void Espacio::set_vehiculo(Vehiculo* v){
    this->v = v;
}

void Espacio::set_convenio(Convenio* conv){
    this->conv = conv;
}

void Espacio::set_llegada(tiempo llegada){
    this->llegada = llegada;
}

void Espacio::set_salida(tiempo salida){
    this->salida = salida;
}

void Espacio::set_tarifa(string tarifa){
    this->tarifa = tarifa;
}

int Espacio::get_numEspacio(){
    return numEspacio;
}

Vehiculo* Espacio::get_vehiculo(){
    return v;
}

Convenio* Espacio::get_convenio(){
    return conv;
}

tiempo Espacio::get_llegada(){
    return llegada;
}

tiempo Espacio::get_salida(){
    return salida;
}

string Espacio::get_tarifa(){
    return tarifa;
}

void Espacio::mostrarEspacio(){
    cout << u8"\n\t Número de espacio: " << numEspacio;
    v->mostrarInfo();
    //Si conv esta vacio mostrar nada
    cout << u8"\n\t Tarifa: " << tarifa;
    //Mostrar hora de llegada    
}


#endif 
