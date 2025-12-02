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
        int folio;
        int numEspacio;
        string tarifa;

    public:
        TicketEntrada(Vehiculo* vehiculo = nullptr, time_t horaEntrada= 0.0, int folio = 0, int numEspacio = -1, string tarifa = ""){
            this -> vehiculo = vehiculo;
            this -> horaEntrada = horaEntrada;
            this -> folio = folio;
            this -> numEspacio = numEspacio;
            this -> tarifa = tarifa;
        }

        void set_Vehiculo(Vehiculo* vehiculo){
            this -> vehiculo = vehiculo;
        }
        
        void set_horaEntrada(time_t horaEntrada){
            this -> numEspacio = numEspacio;
        }
        
        void set_folio(int folio){
            this -> folio = folio;
        }

        void set_numEspacio(int numEspacio){
            this -> numEspacio = numEspacio;
        }

        void set_tarifa(string tarifa){
            this -> tarifa = tarifa;
        }

        Vehiculo* get_Vehiculo() const{
            return vehiculo;
        }

        time_t get_horaEntrada() const{
            return horaEntrada;
        }

        int get_folio(){
            return folio;
        }

        int get_numEspacio(){
            return numEspacio;
        }

        string get_tarifa(){
            return tarifa;
        }
        

        void mostrarTicketEntrada() const{
            cout << "\n\t ***** Ticket de Estacionamiento *****" << endl;
            /////////////////////////PONERLE NOMBRE AL ESTACIONAMIENTO

            //validacion en caso de que se quiera imprimir un ticket sin haber registro
            if (vehiculo == nullptr) {
                cout << "\n\t [ERROR] Ticket sin vehículo asignado." << endl;
                cout << "-------------------------------------" << endl;
                return;
            }

            //composicion de la clase Vehiculo
            vehiculo->mostrarInfo();

            cout << "\n\t Espacio: " << numEspacio << endl;
            cout << "\n\t Hora de entrada: " << ctime(&horaEntrada);
            cout << "\n\t Fecha: "; ////Mostrar la fecha
            cout << "\n\t Tarifa elegida: " << tarifa;

            cout << "-------------------------------------" << endl;
        }
};

#endif
