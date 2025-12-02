/* Arhcivo con las opciones para la administración del sistema de estacionamiento*/ 
#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define CADMIN "0123"
#define CAPAGAR "0000"
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
    static bool validarCodigo(const string& codigo);
    static void mostrarMenu(bool &valido);
    static void panelAdministracion();
    static void pausar();
    static void limpiar();
};

void Administrador::administrador(bool &valido) {
    string codigo;
    int cont = 0;
    bool correcta = false;


    do {
        cout << u8"\n\t Ingresa el código de administrador (4 números): ";
        cin >> codigo;

        if (codigo.length() != 4) {
            cout << u8"\n\t Debe tener exactamente 4 dígitos.\n";
            continue;
        }
        bool soloDigitos = true;
        for (char c : codigo) if (!isdigit(c)) soloDigitos = false;

        if (!soloDigitos) {
            cout << u8"\n\t Solo números.\n";
            continue;
        }

        if (codigo == CADMIN) {
            correcta = true;
        } else {
            ++cont;
            cout << u8"\n\t Código de administrador incorrecto.\n\n";
        }

        if (cont == 3) {
            cout << u8"\n\t Intentos de inicio de sesión agotados.\n\n";
            pausar();
            return;
        }
    } while (!correcta);

    cout << "\n\t Bienvenido Administrador";
    mostrarMenu(valido);
}


void Administrador::mostrarMenu(bool &valido) {
    int opc;
    do {
        limpiar();
        cout << "\n\t [1] Administrar el sistema del estacionamiento";
        cout << "\n\t [2] Volver a la pantalla principal";
        cout << "\n\t [0] Apagar el sistema";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc) {
            case 1: 
                panelAdministracion(); 
                break;
            case 2: {
                char r;
                do {
                    cout << "\n\t Regresar a la pantalla principal? s/n: ";
                    cin >> r;
                }while (r != 's' && r != 'S' && r != 'n' && r != 'N');
                if (r=='s' || r=='S') return;
                break;
            }
            case 0:{
                string code;
                int intentos = 0;
                bool ok = false;
                do{
                    cout << u8"\n\t Ingresa el código para apagar el equipo (4 números): ";
                    cin >> code;
                    if (code == CAPAGAR) { ok = true; valido = true; }
                    else { cout << u8"\n\t Código incorrecto\n"; intentos++; }
                }while (!ok && intentos < 3);
                if (ok) cout << u8"\n\t SISTEMA APAGADO.\n";
                return;
            }
            default: cout << u8"\n\t Opción inválida"; pausar(); break;
        }
    } while (true);
}

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
