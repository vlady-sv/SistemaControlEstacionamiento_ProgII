//CLASE - TICKET DE SALIDA

#ifndef TICKETENTRADA_H
#define TICKETENTRADA_H

#include <iostream>
#include <ctime>
#include <fstream>
#include "Vehiculo.h"

using namespace std;

class TicketEntrada{
    private:
        Vehiculo* vehiculo;
        time_t horaEntrada;
        string folio;

    public:
        TicketEntrada(Vehiculo* vehiculo = nullptr, time_t horaEntrada= 0.0, string folio = "0000"){
            this -> vehiculo = vehiculo;
            this -> horaEntrada = horaEntrada;
            this -> folio = folio;
        }

        void mostrarTicketEntrada() const{
            cout << "***** Ticket de Estacionamiento *****" << endl;

            //validacion en caso de que se quiera imprimir un ticket sin haber registro
            if (vehiculo == nullptr) {
                cout << "[ERROR] Ticket sin vehículo asignado." << endl;
                cout << "-------------------------------------" << endl;
                return;
            }

            //composicion de la clase Vehiculo
            vehiculo->mostrarInfo();

            cout << "Espacio: " << numeroEspacio << endl;
            cout << "Hora de entrada: " << ctime(&horaEntrada);

            if (!activo)
                cout << "Hora de salida: " << ctime(&horaSalida);

            cout << "Total a pagar: $" << totalPagar << endl;
            cout << "-------------------------------------" << endl;
        }
        
        Vehiculo* getVehiculo() const{
            return vehiculo;
        
};

#endif
