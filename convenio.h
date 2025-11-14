#ifndef CONVENIO_H
#define CONVENIO_H
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// Clase base 
class Convenio {
protected:
    string nombreEmpresa;
    double porcentajeDescuento;

public:
  
    Convenio(string nombre, double descuento)
        : nombreEmpresa(nombre), porcentajeDescuento(descuento) {}

  
    string getNombreEmpresa() const {
        return nombreEmpresa;
    }

    double getPorcentajeDescuento() const {
        return porcentajeDescuento;
    }


    void setNombreEmpresa(const string& nombre) {
        nombreEmpresa = nombre;
    }

    void setPorcentajeDescuento(double descuento) {
        if (descuento >= 0 && descuento <= 100)
            porcentajeDescuento = descuento;
        else
            cout << u8"Descuento inválido. Debe estar entre 0% y 100%.\n";
    }

  
    virtual double calcularDescuento(double horas) {
        return 0; 
    }

    virtual void mostrarDescuento(double horas) {
        cout << "\nEmpresa: " << nombreEmpresa << endl;
    }

    virtual ~Convenio() {}
};

// Clases derivadas
class MexaBank : public Convenio {
public:
    MexaBank() : Convenio("Mexabank", 10.0) {} 
};

class Sis : public Convenio {
public:
    Sis() : Convenio("Secretaría de Innovación Social", 15.0) {} 
};

class Seguro : public Convenio {
public:
    Seguro() : Convenio("Seguros Automotrices", 25.0) {}
};

#endif // CONVENIO_H

