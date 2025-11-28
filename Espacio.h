#ifndef ESPACIO_H
#define ESPACIO_H
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
        int folio;
        Vehiculo* v;
        Convenio* conv;
        tiempo llegada;
        tiempo salida;
        tiempo duracion;
        //tiempo duracion = duration_cast<minutes>(salida - llegada);         //////////////Obtener duracion - pasar a parte de Ticket
        string tarifa;
        bool ocupado;

    public:
        Espacio();
        Espacio(int, int, Vehiculo*, Convenio*, string, bool);
        Espacio(Espacio const &);
        void set_numEspacio(int);
        void set_folio(int);
        void set_vehiculo(Vehiculo*);
        void set_convenio(Convenio*);
        void set_llegada(tiempo);
        void set_salida(tiempo);
        void set_tarifa(string);
        void set_ocupado(bool);
        int get_numEspacio();
        int get_folio();
        Vehiculo* get_vehiculo();
        Convenio* get_convenio();
        tiempo get_llegada();
        tiempo get_salida();
        string get_tarifa();
        bool get_ocupado();
        void mostrarEspacio();
        ~Espacio();

};

Espacio::Espacio(){
    numEspacio = 0;
    folio = 0;
    v = nullptr;
    conv = nullptr;
    tarifa = "";
    ocupado = false;
}

Espacio::Espacio(int numEspacio, int folio, Vehiculo* v, Convenio* conv, string tarifa, bool ocupado){
    this->numEspacio = numEspacio;
    this->folio = folio;
    this->v = v;
    this->conv = conv;
    this->tarifa = tarifa;
    this->ocupado = ocupado;
}

Espacio::Espacio(Espacio const &obj){
    numEspacio = obj.numEspacio;
    folio = obj.folio;
    v = obj.v;
    conv = obj.conv;
    tarifa = obj.tarifa;
    ocupado = obj.ocupado;
}

void Espacio::set_numEspacio(int numEspacio){
    this->numEspacio = numEspacio;
}

void Espacio::set_folio(int folio){
    this->folio = folio;
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

void Espacio::set_ocupado(bool ocupado){
    this->ocupado = ocupado;
}

int Espacio::get_numEspacio(){
    return numEspacio;
}

int Espacio::get_folio(){
    return folio;
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

bool Espacio::get_ocupado(){
    return ocupado;
}

void Espacio::mostrarEspacio(){
    cout << u8"\n\t Número de espacio: " << numEspacio;
    v->mostrarInfo();
    //Si conv esta vacio mostrar nada
    cout << u8"\n\t Tarifa: " << tarifa;
    //Mostrar hora de llegada    
}

Espacio::~Espacio(){
    delete v;
    delete conv;
}

#endif 
