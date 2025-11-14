#ifndef VEHICULO_VEHICULO_H
#define VEHICULO_VEHICULO_H
#include <string>
#include <iostream>
using namespace std;

class Vehiculo{
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

        //metodo mostrar puro
        virtual void mostrarInfo() const = 0;

        //destructor virtual
        virtual ~Vehiculo() = default;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//clases derivadas

class Auto : public Vehiculo{
    public:
        Auto(){
            tipo = "Auto";
        }
        Auto(string p) : Vehiculo(p, "Auto") {}

       
        void mostrarInfo() const override{
            cout << "[AUTO] Placa: " << placa << " | Tipo: " << tipo << endl;
        }
};

class Moto : public Vehiculo {
    public:
        Moto(){
            tipo = "Moto";
        }
        Moto(string p) : Vehiculo(p, "Moto") {}

        void mostrarInfo() const override{
            cout << "[MOTO] Placa: " << placa << " | Tipo: " << tipo << endl;
        }
};

class Camioneta : public Vehiculo{
    public:
        Camioneta(){
            tipo = "Camioneta";
        }
        Camioneta(string p) : Vehiculo(p, "Camioneta") {}

        void mostrarInfo() const override{
            cout << "[CAMIONETA] Placa: " << placa << " | Tipo: " << tipo << endl;
        }
};

#endif //VEHICULO_VEHICULO_H
