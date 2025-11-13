#ifndef CONVENIO_H
#define CONVENIO_H
#include <iostream>
#include <string>
using namespace std;

// Clase base Convenio
class Convenio {
protected:
    string nombreEmpresa;
    double porcentajeDescuento; 
    const double tarifaHora = 80.0; 

public:
  
    Convenio(string nombre, double descuento)
        : nombreEmpresa(nombre), porcentajeDescuento(descuento) {}

  
    string getNombreEmpresa() const {
        return nombreEmpresa;
    }

    double getPorcentajeDescuento() const {
        return porcentajeDescuento;
    }

    double getTarifaHora() const {
        return tarifaHora;
    }


    void setNombreEmpresa(const string& nombre) {
        nombreEmpresa = nombre;
    }

    void setPorcentajeDescuento(double descuento) {
        if (descuento >= 0 && descuento <= 100)
            porcentajeDescuento = descuento;
        else
            cout << "Descuento inválido. Debe estar entre 0% y 100%.\n";
    }

  
    virtual double calcularDescuento(double horas) {
        double total = horas * tarifaHora;
        double descuento = total * (porcentajeDescuento / 100.0);
        return total - descuento;
    }

    void mostrarDescuento(double horas) {
        double total = horas * tarifaHora;
        double totalConDescuento = calcularDescuento(horas);

        cout << "\nEmpresa: " << nombreEmpresa << endl;
        cout << "Horas estacionado: " << horas << endl;
        cout << "Tarifa por hora: $" << tarifaHora << endl;
        cout << "Total sin descuento: $" << total << endl;
        cout << "Descuento aplicado: " << porcentajeDescuento << "%" << endl;
        cout << "Total con descuento: $" << totalConDescuento << endl;
        cout << "------------------------------------\n";
    }

    virtual ~Convenio() {}
};

//clases derivadas
class motorsA : public Convenio {
public:
    motorsA() : Convenio("MotoresJalisco", 10.0) {} 
};

class llamtas : public Convenio {
public:
    llamtas() : Convenio("LlantasAguascalientes", 15.0) {} 
};

class rimes : public Convenio {
public:
    rimes() : Convenio("RinesBallarta", 25.0) {}
};

#endif // CONVENIO_H
