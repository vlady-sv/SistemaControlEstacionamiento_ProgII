#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <chrono>
#include "Espacio.h"

using namespace std;
namespace fs = std::filesystem;

// Convierte tiempo (system_clock::time_point) a string legible
static string tiempoToString(const tiempo &t) {
    time_t tt = reloj::to_time_t(t);
    string s = ctime(&tt);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}

void guardarTicketSalida(const Espacio &e, double totalPagar) {

    string nombre = "Ticket" + to_string(e.get_folio()) + ".txt";
    ofstream ticket(nombre);

    if (!ticket) {
        cout << "\n[ERROR] No se pudo crear el archivo del ticket.\n";
        return;
    }
    Vehiculo* v = e.get_vehiculo();
    Convenio* conv = e.get_convenio();

    ticket << "=================== TICKET DE SALIDA ===================\n";
    ticket << "Folio: " << e.get_folio() << "\n";
    ticket << "Numero de espacio: " << e.get_numEspacio() << "\n";

    if (v != nullptr) {
        ticket << "Placas: " << v->getPlacas() << "\n";
        ticket << "Tipo: " << v->getTipo() << "\n";
        ticket << "Propietario: " << v->getNombre() << "\n";
    }

    if (conv != nullptr) {
        ticket << "Convenio: " << conv->getNombreEmpresa() << "\n";
        ticket << "Descuento aplicado: " << conv->getPorcentajeDescuento() << "%\n";
    }

    ticket << "Tarifa usada: " << e.get_tarifa() << "\n\n";

    ticket << "Hora de llegada: " << tiempoToString(e.get_horaLlegada()) << "\n";
    ticket << "Hora de salida:  " << tiempoToString(e.get_horaSalida()) << "\n\n";
    ticket << "Horas cobradas: " << e.get_horasDuracion() << "\n";
    ticket << "Dias cobrados:  " << e.get_diasDuracion() << "\n\n";

  
    ticket << fixed << setprecision(2);
    ticket << "TOTAL A PAGAR: $" << totalPagar << "\n";
    ticket << "========================================================\n";

    ticket.close();
}



//lectura de tickets para el corte de caja 
double corteDeCaja() {
    double total = 0.0;

    for (const auto &file : fs::directory_iterator(".")) {

        string nombre = file.path().filename().string();
        if (nombre.rfind("Ticket", 0) != 0) continue; // Solo Ticket*.txt

        ifstream t(nombre);
        if (!t) continue;

        string linea;
        while (getline(t, linea)) {
            size_t pos = linea.find("TOTAL A PAGAR:");
            if (pos != string::npos) {
                size_t signo = linea.find("$", pos);
                if (signo != string::npos) {
                    double monto = stod(linea.substr(signo + 1));
                    total += monto;
                }
            }
        }
    }

    return total;
}

#endif
