#include <windows.h>
#include "Espacio.h"
#define CADMIN "0123"
#define CAPAGAR "0000"

void usuario();
void administrador(bool &valido);
bool apagar();
bool verificar4Digits(const string codigo);
bool verificarFormatoPlaca(const string placa);

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
            case 1: cout << "U";//Llamada a metodo de usuario();
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
    Vehiculo* v;
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
                v->setTipo("Auto");
                auxVe=false;
                break;
            case 2:
                v->setTipo("Moto");
                auxVe=false;
                break;
            case 3:
                v->setTipo("Camioneta");
                auxVe=false;
                break;
            default: cout << u8"\n\n\t Opción inválida";
                break;
        }
        
    }while(auxVe);

    do{
        cout << "\n\t ====> FORMATO DE LA PLACA <====";
        cout << "\n\t\t ";
        cout << u8"\n\t Ingresa el número de la placa de tu vehículo en el formato solicitado: ";
        cin.ignore();
        cin >> placa;
        //Implementacion para validar formato
        v->setPlaca(placa);
    }while(formato == false);

    //Implementacion de llamada a espacio
    
}

void administrador(bool &valido){
    string codigo;
    int cont = 0;
    bool correcta = false, digits4 = false;
    do{ 
        do{
            cout << u8"\n\t Ingresa el código de administrador (4 números): ";
            cin >> codigo;
            digits4 = verificar4Digits(codigo); //Verficación de número con 4 dígitos
        }while(!digits4);

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
            case 1: cout << "Administrar"; ///////////////Agregar opciones de administracion
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
    bool digits4;
    do{
        do{
            cout << u8"\n\t Ingresa el código para apagar el equipo (4 números): ";
            cin >> code;
            digits4 = verificar4Digits(code);
        }while(!digits4);

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

/*-------------------------- VERIFICAR LA INSERCIÓN DE 4 NÚMEROS (ADMIN. O APAGADO) -------------------*/

bool verificar4Digits(const string codigo){
    if(codigo.length() != 4){
        return false;
    }else{
        bool esValido = true;
        for(char c : codigo){
            if(!isdigit(c)){
                esValido = false;
                break;
            }
        }

        if(!esValido) return false;
    }

    return true;
}