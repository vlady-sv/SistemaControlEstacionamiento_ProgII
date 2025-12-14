#ifndef CONVENIO_H
#define CONVENIO_H
#include <iostream>
#include <string>
using namespace std;

// Clase base 
class Convenio {
public:
    virtual string get_empresa() = 0;
    virtual double get_descuento() = 0;

    virtual ~Convenio() {}
};

// Clases derivadas
class MexaBank : public Convenio {
private:
    string nombreEmpresa;
    double descuento;

public:
    MexaBank(string nE = "Mexabank", double d = 0.10) : nombreEmpresa(nE), descuento(d) {} 

    string get_empresa(){
        return nombreEmpresa;
    }

    double get_descuento(){
        return descuento;
    }
};

class Sis : public Convenio {
private:
    string nombreEmpresa;
    double descuento;
public:
    Sis(string nE = "Sis", double d = 0.15) : nombreEmpresa(nE), descuento(d) {} 

    string get_empresa(){
        return nombreEmpresa;
    }

    double get_descuento(){
        return descuento;
    }
};

class Seguro : public Convenio {
private:
    string nombreEmpresa;
    double descuento;
public:
    Seguro(string nE = "Seguros Automotrices", double d = 0.25) : nombreEmpresa(nE), descuento(d) {}

    string get_empresa(){
        return nombreEmpresa;
    }

    double get_descuento(){
        return descuento;
    }
};

#endif // CONVENIO_H

