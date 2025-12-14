//CLASE - TICKET DE SALIDA
#ifndef TICKETENTRADA_H
#define TICKETENTRADA_H
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "Vehiculo.h"
#include "calculoTiempo.h"
#include "Espacio.h"
namespace fs = std::filesystem;
using namespace std;

class TicketEntrada{
    private:
        Espacio e;
        bool siConvenio;
        friend void guardarTicketE(TicketEntrada&);

    public:
        TicketEntrada(Espacio e, bool siConvenio){
            this -> e = e;
            this -> siConvenio = siConvenio;
        }

        void set_Espacio(Espacio e){
            this -> e = e;
        }

        void set_siConvenio(bool siConvenio){
            this -> siConvenio = siConvenio;
        }

        Espacio get_Espacio() const{
            return e;
        }

        bool get_siConvenio() const{
            return siConvenio;
        }

        void mostrarTicketEntrada() const{
            //validacion en caso de que se quiera imprimir un ticket sin haber registro
            if (e.get_numEspacio() == 0) {
                cout << "\n\t [ERROR] Ticket sin vehículo asignado." << endl;
                cout << "-------------------------------------" << endl;
                return;
            }

            cout << "\n\t\t\t ***** PLAZA PARKING *****\n";
            cout << "\n\t ---- Ticket de Entrada ----" << endl; 
            e.mostrarEspacio(false);
            cout << u8"\n\t Para salir del estacionamiento se necesita este ticket, favor de guardarlo así como "
                 << "su número de folio.";

            cout << "\n-------------------------------------" << endl;
        }
};

void guardarTicketE(TicketEntrada& obj){//Crear lógica para guardar el ticket con funcion amiga

    fs::path carpeta = "Tickets_Entrada"; //Carpeta donde se estaran guardando todos los tickets de salida
    if(!fs::exists(carpeta)){
        fs::create_directories(carpeta);  //Si aun no existe se crea
    }
    string nomTicket;
    nomTicket = "Ticket_" + to_string(obj.e.get_folio());
    nomTicket = nomTicket + "_" + obj.e.get_diaLlegada();
    nomTicket = nomTicket + ".dat"; //Construimos el nombre completo del archivo

    fs::path archivo = carpeta/nomTicket; //La ruta + el nombre

    fstream ticket;
    ticket.open(archivo, ios::binary|ios::out);
    if(!ticket.is_open()){
        cout << u8"\n\t El ticket no se abrio correctamente [Error en crear ticket entrada]";
        return;
    }

    ticket.write(reinterpret_cast<char*>(&obj.e), sizeof(Espacio));
    ticket.write(reinterpret_cast<char*>(&obj.siConvenio), sizeof(bool));

    ticket.close();
}

#endif
