#ifndef ESPACIO_H
#define ESPACIO_H
#include <cstdlib>
#include <chrono>
#include "Vehiculo.h"
#include "convenio.h"
#include "calculoTiempo.h"
using namespace std;
using namespace std::chrono;
using reloj = system_clock;
using tiempo = system_clock::time_point;

class Espacio{
    private:
        int numEspacio;
        int folio;
        Vehiculo* v;
        Convenio* conv;
        tiempo horaLlegada;
        tiempo fechaLlegada;
        tiempo horaSalida;
        tiempo fechaSalida;
        int horasDuracion;
        int diasDuracion;
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
        void set_horaLlegada(tiempo);
        void set_fechaLlegada(tiempo);
        void set_horaSalida(tiempo);
        void set_fechaSalida(tiempo);
        void set_tarifa(string);
        void set_ocupado(bool);
        void set_horasDuracion(int);
        void set_diasDuracion(int);
        int get_numEspacio();
        int get_folio();
        Vehiculo* get_vehiculo();
        Convenio* get_convenio();
        tiempo get_horaLlegada();
        tiempo get_fechaLlegada();
        tiempo get_horaSalida();
        tiempo get_fechaSalida();
        string get_tarifa();
        int get_horasDuracion();
        int get_diasDuracion();
        bool get_ocupado();
        void establecerLlegada();
        void establecerSalida();
        void calcularDuracion();
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

void Espacio::set_horaLlegada(tiempo horaLlegada){
    this->horaLlegada= horaLlegada;
}

void Espacio::set_fechaLlegada(tiempo fechaLlegada){
    this->fechaLlegada= fechaLlegada;
}

void Espacio::set_horaSalida(tiempo horaSalida){
    this->horaSalida = horaSalida;
}

void Espacio::set_fechaSalida(tiempo fechaSalida){
    this->fechaSalida = fechaSalida;
}

void Espacio::set_tarifa(string tarifa){
    this->tarifa = tarifa;
}

void Espacio::set_ocupado(bool ocupado){
    this->ocupado = ocupado;
}

void Espacio::set_horasDuracion(int horasDuracion){
    this->horasDuracion = horasDuracion;
}

void Espacio::set_diasDuracion(int diasDuracion){
    this->diasDuracion = diasDuracion;
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

tiempo Espacio::get_horaLlegada(){
    return horaLlegada;
}

tiempo Espacio::get_fechaLlegada(){
    return fechaLlegada;
}

tiempo Espacio::get_fechaSalida(){
    return fechaSalida;
}

string Espacio::get_tarifa(){
    return tarifa;
}

bool Espacio::get_ocupado(){
    return ocupado;
}

int Espacio::get_horasDuracion(){
    return horasDuracion;
}

int Espacio::get_diasDuracion(){
    return diasDuracion;
}

void Espacio::establecerLlegada(){
    tiempo ahora = reloj::now();
    horaLlegada = ahora;
    fechaLlegada = ahora;
}

void Espacio::establecerSalida(){
    tiempo ahora = reloj::now();
    horaSalida = ahora;
    fechaSalida = ahora;
}

void Espacio::calcularDuracion(){
    if(tarifa == "horas"){
        horasDuracion = horasCobrar(horaLlegada, horaSalida);
        //Hacer la multiplicación de las horas por el monto por hora
    }else if(tarifa == "dia"){
        diasDuracion = diasCobrar(horaLlegada, horaSalida);
        //Hacer la multiplicación de los días por el monto por día
    }else{

    }
}

void Espacio::mostrarEspacio(){
    cout << u8"\n\t Número de espacio: " << numEspacio;
    v->mostrarInfo();
    //Si conv no esta vacio se muestra la empresa con la que se tiene convenio y el porcentaje de descuento ofrecido
    if(conv != nullptr){
        cout << "\n\t Convenio con: " << conv->getNombreEmpresa();
        cout << "\n\t Descuento: " << conv->getPorcentajeDescuento() << "%";
    }
    cout << u8"\n\t Tarifa: " << tarifa;
    //Mostrar hora de llegada    
}

Espacio::~Espacio(){
    delete v;
    delete conv;
}

#endif 
