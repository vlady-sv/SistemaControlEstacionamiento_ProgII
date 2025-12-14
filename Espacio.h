#ifndef ESPACIO_H
#define ESPACIO_H
#include <cstdlib>
#include "Vehiculo.h"
#include "convenio.h"
#include "calculoTiempo.h"
using namespace std;

/* Función auxiliar para convertir tiempo a string como fecha */
string tiempoToStringFecha(const tiempo& t){
    time_t tt = reloj::to_time_t(t); //Conversión de tiempo a time_t
    tm tm = *localtime(&tt); //Lo hacemos local
    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y");

    return oss.str();
};

/* Función auxiliar para convertir tiempo a string como hora */
string tiempoToStringHora(const tiempo& t){
    time_t tt = reloj::to_time_t(t); //Conversión de tiempo a time_t
    tm tm = *localtime(&tt); //Lo hacemos local
    ostringstream oss;
    oss << put_time(&tm, "%H:%M:%S");

    return oss.str();
};

class Espacio{
    private:
        int numEspacio;
        int folio;
        char tipoVehiculo[10]; //De Vehiculo
        char placa[15]; //De Vehiculo
        char empresa[30]; //De Convenio
        double descuento; //De convenio
        char horaLlegada[15];
        char diaLlegada[15];
        char tarifa[15];
        bool ocupado;

    public:
        Espacio(int, int, const char[10], const char[15], const char[20], double, const char[15], const char[15], const char[15], bool);
        Espacio(Espacio const &);
        void set_numEspacio(int);
        void set_folio(int);
        void set_tipoVehiculo(char[10]);
        void set_placa(char[15]);
        void set_empresa(char[30]);
        void set_descuento(double);
        void set_horaLlegada(char[15]);
        void set_diaLlegada(char[15]);
        void set_horasDuracion(int);
        void set_diasDuracion(int);
        void set_tarifa(char[15]);
        void set_ocupado(bool);
        int get_numEspacio() const;
        int get_folio() const;
        const char* get_tipoVehiculo() const;
        const char* get_placa() const;
        const char* get_empresa() const;
        double get_descuento() const;
        const char* get_horaLlegada() const;
        const char* get_diaLlegada() const;
        const char* get_tarifa() const;
        bool get_ocupado() const;
        void establecerLlegada();
        void calcularDuracion();
        void mostrarEspacio(bool) const;
        Espacio& operator=(const Espacio&);
        friend bool escribirEspacio(fstream&, Espacio&);
        friend bool leerEspacio(fstream &, Espacio &);
};

Espacio::Espacio(int numEspacio = 0, int folio = 0, const char tipoVehiculo[10] = ".", const char placa[15] = ".", const char empresa[30] = ".", 
    double descuento = 0.0, const char horaLlegada[15] = ".", const char diaLlegada[15] = ".", const char tarifa[15] = ".", bool ocupado = false){
    this->numEspacio = numEspacio;
    this->folio = folio;
    strcpy(this->tipoVehiculo, tipoVehiculo);
    strcpy(this->placa, placa);
    strcpy(this->empresa, empresa);
    this->descuento = descuento;
    strcpy(this->horaLlegada, horaLlegada);
    strcpy(this->diaLlegada, diaLlegada);
    strcpy(this->tarifa, tarifa);
    this->ocupado = ocupado;
}

Espacio::Espacio(Espacio const &obj){
    numEspacio = obj.numEspacio;
    folio = obj.folio;
    strcpy(tipoVehiculo, obj.tipoVehiculo);
    strcpy(placa, obj.placa);
    strcpy(empresa, obj.empresa);
    descuento = obj.descuento;
    strcpy(horaLlegada, obj.horaLlegada);
    strcpy(diaLlegada, obj.diaLlegada);
    strcpy(tarifa, obj.tarifa);
    ocupado = obj.ocupado;
}

/* SETTERS*/
void Espacio::set_numEspacio(int numEspacio){
    this->numEspacio = numEspacio;
}

void Espacio::set_folio(int folio){
    this->folio = folio;
}

void Espacio::set_tipoVehiculo(char tipoVehiculo[10]){
    strcpy(this->tipoVehiculo, tipoVehiculo);
}

void Espacio::set_placa(char placa[15]){
    strcpy(this->placa, placa);
}

void Espacio::set_empresa(char empresa[30]){
    strcpy(this->empresa, empresa);
}

void Espacio::set_descuento(double descuento){
    this->descuento = descuento;
}

void Espacio::set_horaLlegada(char horaLlegada[15]){
    strcpy(this->horaLlegada, horaLlegada);
}

void Espacio::set_diaLlegada(char diaLlegada[15]){
    strcpy(this->diaLlegada, diaLlegada);
}

void Espacio::set_tarifa(char tarifa[15]){
    strcpy(this->tarifa, tarifa);
}

void Espacio::set_ocupado(bool ocupado){
    this->ocupado = ocupado;
}

/* GETTERS*/
int Espacio::get_numEspacio() const{
    return numEspacio;
}

int Espacio::get_folio() const{
    return folio;
}

const char* Espacio::get_tipoVehiculo() const{
    return tipoVehiculo;
}

const char* Espacio::get_placa() const{
    return placa;
}

const char* Espacio::get_empresa() const{
    return empresa;
}

double Espacio::get_descuento() const{
    return descuento;
}

const char* Espacio::get_horaLlegada() const{
    return horaLlegada;
}

const char* Espacio::get_diaLlegada() const{
    return diaLlegada;
}

const char* Espacio::get_tarifa() const{
    return tarifa;
}

bool Espacio::get_ocupado() const{
    return ocupado;
}

void Espacio::establecerLlegada(){
    tiempo ahora = reloj::now();
    strcpy(horaLlegada, tiempoToStringHora(ahora).c_str());
    strcpy(diaLlegada, tiempoToStringFecha(ahora).c_str());

}

void Espacio::mostrarEspacio(bool mostrarOcupado) const{
    cout << u8"\n\t\t ---> Espacio de Estacionamiento número: " << numEspacio << " <---";
    cout << "\n\t Folio: " << folio;
    cout << u8"\n\t Tipo de Vehículo: " << tipoVehiculo;
    cout << "\n\t Placa: " << placa;
    cout << "\n\t Empresa: " << empresa;
    if(descuento != 0){
        cout << "\n\t Descuento aplicado: " << fixed << setprecision(1) << descuento*100 << "%";
    }else{
        cout << "\n\t Descuento aplicado: N/A";
    }
    cout << "\n\t Hora de llegada: " << horaLlegada;
    cout << u8"\n\t Día de llegada: " << diaLlegada;
    cout << "\n\t Tarifa: Por " << (strcmp(tarifa, "pension") == 0? u8"mes/pensión" : tarifa);
    if(mostrarOcupado) cout << "\n\t Ocupado: " << (ocupado? u8"Sí":"No");
}

Espacio& Espacio::operator=(const Espacio& esp){
    if(this != &esp){
        numEspacio = esp.numEspacio;
        folio = esp.folio;
        strcpy(tipoVehiculo, esp.tipoVehiculo);
        strcpy(placa, esp.placa);
        strcpy(empresa, esp.empresa);
        descuento = esp.descuento;
        strcpy(horaLlegada, esp.horaLlegada);
        strcpy(diaLlegada, esp.diaLlegada);
        strcpy(tarifa, esp.tarifa);
        ocupado = esp.ocupado;
    }
    return *this;
}

#endif 
