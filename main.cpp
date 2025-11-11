#include <iostream>
#include <windows.h>
#define CADMIN "0123"
#define CAPAGAR "0000"
using namespace std;

void usuario();
void administrador(bool &valido);
bool apagar();

int main(){
    cout << CADMIN;
    cout << CAPAGAR;
    SetConsoleOutputCP(CP_UTF8);
    int opc;
    bool valido = false;

    do{
        do{
            cout << u8"\n\t [1] Ingresar al estacionamiento";
            cout << u8"\n\t [2] Administrador";
            cout << u8"\n\n\t Elige una opción: ";
            cin >> opc;
        }while(opc != 1 && opc != 2);

        switch(opc){
            case 1: cout << "U";//usuario();
                break;
            case 2: administrador(valido);
                break;
            default: cout << u8"\n\tOpción inválida\n";
                break;
        }
    }while(valido == false);

    return 0;
}

void usuario(){
    int tipoVehiculo;
    bool auxVe = true, formato = false;
    string placa, vehiculo;
    do{
        cout << "\n\t [1] Auto";
        cout << "\n\t [2] Moto";
        cout << "\n\t [3] Camioneta";
        cout << u8"\n\n\t Tipo de vehículo: ";
        cin >> tipoVehiculo;

        switch(tipoVehiculo){
            case 1:
                vehiculo = "Auto";
                auxVe=false;
                break;
            case 2:
                vehiculo = "Moto";
                auxVe=false;
                break;
            case 3:
                vehiculo = "Camioneta";
                auxVe=false;
                break;
            default: cout << u8"\n\n\t Opción inválida";
                break;
        }
        
    }while(auxVe);

    do{
        cout << "\n\t ====> FORMATO DE LA PLACA <====";
        cout << "\n\t\t ";
        cout << u8"\n\t Ingresa el número de la placa de tu vehículo: ";
        cin.ignore();
        cin >> placa;
    }while(formato == false);

    //Implementacion de llamada a espacio
}

void administrador(bool &valido){
    string codigo;
    int cont = 0;
    bool correcta = false;
    do{
        cout << u8"\n\t Ingresa el código de administrador: ";
        cin >> codigo;
        cout << CADMIN;
        if(codigo == CADMIN) correcta = true;

        if(codigo != CADMIN){
            ++cont;
            cout << u8"\n\t Código de administrador incorrecto.\n\n";
        }
        if(codigo != CADMIN && cont == 3){
            cout << u8"\n\t Intentos de inicio de sesión agotados.\n\n";
            return;
        }
        
    }while(correcta == false && cont < 3);

    cout << "\n\t Bienvenido Administrador";

    /* ------------> OPCIONES PARA LA ADMNISTRACION DEL SISTEMA <----------------- */
    int opc;

    do{
        cout << "\n\t [1] Administrar el sistema del estacionamiento";
        cout << "\n\t [2] Volver a la pantalla principal";
        cout << "\n\t [0] Apagar el sistema";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: cout << "Administrar"; ///////////////Agregar opcion de administrar
                break;
            case 2:{
                char resp;
                do{
                    cout << "\n\t Regresar a la pantalla principal? s/n: ";
                    cin >> resp; 
                }while(resp != 's' || resp != 'S' || resp != 'n' || resp != 'N');
                if(resp == 's' || resp == 'S') return;
                break;
                }
            case 0: valido = apagar();
                break;
            default: cout << "\n\n\tOpción inválida";
                break;
        }
    }while(valido == false);
}

bool apagar(){
    string code;
    int cont;
    do{
        cout << u8"\n\t Ingresa el código para apagar el equipo: ";
        cin >> code;

        if(code == CAPAGAR) return true;
        else{
            cout << u8"\n\n\t Código incorrecto";
            ++cont;
        }

        if(code != CAPAGAR && cont == 3){
            cout << "\n\t Intentos agotados";
        }
    }while(cont < 3);

    return false;
}