#ifndef VEHICULO_VEHICULO_H
#define VEHICULO_VEHICULO_H
#include <string>
#include <iostream>
using namespace std;

class Vehiculo {
    protected:
        string placa;
        string tipo;

    public:
        Vehiculo() {}
        Vehiculo(string p, string t) : placa(p), tipo(t) {}

        void setPlaca(string p){
            placa = p;
        }
        void setTipo(string t){
            tipo = t;
        }

        string getPlaca() const{
            return placa;
        }
        string getTipo() const{
            return tipo;
        }
//ESTE METODO MOSTRAR NO ES NECESARIO, FUE PARA PROBAR PROGRAMA ASI QUE SE PUEDE COMENTAR DE SER NECESARIO
        void mostrarInfo() const{
            cout << "Placa: " << placa << endl;
            cout << "Tipo: " << tipo << endl;
        }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//clases derivadas Auto, Moto, Camioneta

class Auto : public Vehiculo{
    public:
        Auto(){
            tipo = "Auto";
        }

        Auto(string p) : Vehiculo(p, "Auto") {}
};

class Moto : public Vehiculo{
    public:
        Moto(){
            tipo = "Moto";
        }

        Moto(string p) : Vehiculo(p, "Moto") {}
};

class Camioneta : public Vehiculo{
    public:
        Camioneta(){
            tipo = "Camioneta";
        }

        Camioneta(string p) : Vehiculo(p, "Camioneta") {}
};

#endif //VEHICULO_VEHICULO_H
