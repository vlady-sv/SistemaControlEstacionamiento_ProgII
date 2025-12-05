/* Arhcivo con las opciones para la administración del sistema de estacionamiento*/ 
#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define AUTOS 500
#define Camiones 500
#define MOTOS 500

int contAutos();
int contCamiones();
int contMotos();

class Administrador {
public:
    static void administrador(bool &valido);
    
private:
    static void panelAdministracion();
    static void pausar();
    static void limpiar();
};

void Administrador::panelAdministracion() {
    limpiar();
    cout << u8"\n\t=== PANEL DE ADMINISTRACIÓN ===\n\n";
    cout << u8"\t [1] Ver ocupación actual\n";
    cout << u8"\t [2] Ver ingresos del día al momento\n";
    cout << "\t [3] Realizar corte de caja\n";
    cout << "\t [4] Ver ganancias totales\n";
    cout << "\t [5] Ver convenios\n";
    cout << "\t [0] Volver\n\n\tOpción: ";
    int op; cin >> op;
    switch(op) {
        case 1:
            cout << "\n\tAutos:      " << contAutos()      << " / " << AUTOS      << endl;
            cout << "\tCamiones: " << contCamiones() << " / " << Camiones << endl;
            cout << "\tMotos:      " << contMotos()      << " / " << MOTOS      << endl;
            break;
        case 2:
            cout << "\n\tIngresos del día: en desarrollo...\n"; 
            break;
        case 3: cout << "\n\t Corte de caja\n";
            break;
        case 4: cout << "\n\t Gananacias totales del estacionamiento\n";
            break;
        case 5: 
            cout << "\n\t\t ====> Convenios <====" << 
            u8"\n\t - MEXABANK | Código: 3578" << 
            u8"\n\t - SIS | Código: 1598" << 
            u8"\n\t - SEGURO | Código: 6482\n"; 
            break;
    
    }
    pausar();
}

void Administrador::pausar() {
    cout << "\n\n\tPresiona Enter para continuar...";
    cin.ignore(); cin.get();
}

void Administrador::limpiar() {
    system("cls");
}
#endif
