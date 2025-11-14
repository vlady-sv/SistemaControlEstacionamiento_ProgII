//PROTOTIPO DE LA CLASE TICKET


#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <ctime>
#include <fstream>
#include "Vehiculo.h"

using namespace std;

class Ticket{
    private:
        Vehiculo* vehiculo;
        time_t horaEntrada;
        time_t horaSalida;
        int numeroEspacio;
        double totalPagar;
        bool activo;

    public:
        Ticket(Vehiculo* v = nullptr, int espacio = -1){
            vehiculo = v;
            numeroEspacio = espacio;
            horaEntrada = time(nullptr);
            horaSalida = 0;
            totalPagar = 0;
            activo = true;
        }

        void registrarSalida(){
            horaSalida = time(nullptr);
            activo = false;
        }
        //hace el calculo de la hora de entrada con hra de salida y calcula la(s) horas que estuvo el vehiculo
        double calcularTiempo() const{
            if (horaSalida == 0) return 0;
            double segundos = difftime(horaSalida, horaEntrada);
            return segundos / 3600.0; // Tiempo en horas
        }

        double calcularCosto(double tarifaBase){
            double horas = calcularTiempo();
            totalPagar = horas * tarifaBase;
            return totalPagar;
        }

        void imprimirTicket() const{
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

        bool estaActivo() const{
            return activo;
        }
        Vehiculo* getVehiculo() const{
            return vehiculo;
        }
        double getTotal() const{
            return totalPagar;
        }
};

#endif
