/* Arhcivo con las opciones para la administración del sistema de estacionamiento*/ 
#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
#include <string>
#include "Facturas.h"
#include "ManageArchivos.h"
using namespace std;

#define AUTOS 600  /* Cajones de estacionamiento del 1-600 */
#define MOTOS 600 /*Cajones de estacionamiento del 601-1200*/ //Cambiar por camiones
#define CAMIONES 300  /*Cajones de estacionamiento del 1201-1500*/

class Administrador {
public:
    static void administrador(bool &valido);
    void panelAdministracion();
    static void pausar();
    static void limpiar();
};

void Administrador::panelAdministracion() {
    int op;
    do{
        string nombre;
        Facturas_CorteCaja facturas;
        limpiar();
        
        cout << u8"\n\t=== PANEL DE ADMINISTRACIÓN ===\n\n";
        cout << u8"\t [1] Ver ocupación actual\n";
        cout << "\t [2] Realizar corte de caja\n";
        cout << u8"\t [3] Contabilizar ganancias de la última semana\n";
        cout << u8"\t [4] Contabilizar ganancias del último mes\n";
        cout << "\t [5] Contabilizar ganancias generales\n";
        cout << "\t [6] Ver convenios\n";
        cout << "\t [7] Consultar facturas de cortes\n";
        cout << "\t [8] Consultar facturas de semana\n";
        cout << "\t [9] Consultar facturas de mes\n";
        cout << "\t [10] Consultar facturas general\n";
        cout << u8"\t [0] Volver al menú anterior\n\n\tElige una opción: ";
        cin >> op;

        switch(op) {
            case 1:
                cout << "\n\tAutos:      " << contAutos(false)      << " / " << AUTOS      << endl;
                cout << "\tCamiones: " << contCamiones(false) << " / " << CAMIONES << endl;
                cout << "\tMotos:      " << contMotos(false)      << " / " << MOTOS      << endl;
                break;
            case 2:
                corteCaja(facturas);
                facturas.mostrarFactura("corte");
                break;
            case 3:
                facturaSemana(facturas);
                facturas.mostrarFactura("semana");
                break;
            case 4:
                facturaMes(facturas);
                facturas.mostrarFactura("mes");
                break;
            case 5:
                facturaGeneral(facturas);
                facturas.mostrarFactura("general");
                break;
            case 6: 
                cout << "\n\t\t ====> Convenios <====" << 
                u8"\n\t - MEXABANK | Código: 3578" << 
                u8"\n\t - SIS | Código: 1598" << 
                u8"\n\t - SEGURO | Código: 6482\n"; 
                break;
            case 7:
                cout << "\n\t Ingresa el nombre del archivo que deseas buscar: ";
                cin.ignore();
                getline(cin, nombre);
                facturas = consultarTicket("Cortes_Caja", nombre);
                cout << "\n\t Ingresos: " << facturas.get_totalGanancias();
                cout << "\n\t Tickets contados: " << facturas.get_cantTickets();
                break;
            case 8:
                cout << "\n\t Ingresa el nombre del archivo que deseas buscar: ";
                cin.ignore();
                getline(cin, nombre);
                consultarTicket("Facturas_Semanales", nombre);
                cout << "\n\t Ingresos: " << facturas.get_totalGanancias();
                cout << "\n\t Tickets contados: " << facturas.get_cantTickets();
                break;
            case 9:
                cout << "\n\t Ingresa el nombre del archivo que deseas buscar: ";
                cin.ignore();
                getline(cin, nombre);
                consultarTicket("Facturas_Mensuales", nombre);
                cout << "\n\t Ingresos: " << facturas.get_totalGanancias();
                cout << "\n\t Tickets contados: " << facturas.get_cantTickets();
                break;
            case 10:
                cout << "\n\t Ingresa el nombre del archivo que deseas buscar: ";
                cin.ignore();
                getline(cin, nombre);
                consultarTicket("Facturas_Generales", nombre);
                cout << "\n\t Ingresos: " << facturas.get_totalGanancias();
                cout << "\n\t Tickets contados: " << facturas.get_cantTickets();
                break;
            case 0: cout << u8"\n\t Regresando al menú anterior...";
                break;
            default: cout << "\n\n\t Opción inválida";
                break;
        }
        pausar();
    }while(op != 0);
    
}

void Administrador::pausar() {
    cout << "\n\n\tPresiona Enter para continuar...";
    cin.ignore(); cin.get();
}

void Administrador::limpiar() {
    system("cls");
}
#endif
