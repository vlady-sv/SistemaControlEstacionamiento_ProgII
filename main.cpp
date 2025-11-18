#include <windows.h>
#include <algorithm>
#include "Espacio.h"

/*CODIGOS DE VERIFICACION EN ORDEN:
ADMNISTRADOR, APAGAR SISTEMA, CONVENIO MEXABANK, CONVENIO SECRETARIA DE INNOVACIÓN SOCIAL, CONVENIO EMPRESA DE SEGUROS*/
#define CADMIN "0123"
#define CAPAGAR "0000"
#define MEXABANK "3578"
#define SIS "1598"
#define SEGURO "6482"

//Prototipos

void usuario();
void administrador(bool &valido);
bool apagar();
bool validarPlaca(const string);
bool verificar4Digits(const string codigo);
bool verificarFormatoPlaca(const string placa);
bool codeConvenio(Convenio*);

// Menú principal

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
            case 1: usuario();
                break;
            case 2: administrador(valido);
                break;
            default: cout << u8"\n\tOpción inválida\n";
                break;
        }
    }while(valido == false);

    return 0;
}

/* ======================== OPCIONES PARA MOSTRAR AL USUARIO ======================= */

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

    /* ----------- LLENAR EL ESPACIO EN EL ESTACIONAMIENTO ---------------- */

    //Verificar si hay espacios disponbles correspondientes al tipo de vehiculo, sino darle gracias al usuario y terminar el proceso de registro

    do{
        cout << "\n\t\t ====> FORMATO DE LA PLACA <====";
        cout << "\n\t 'AAA-000-A' (Los guiones tambien deben ingresarse)";
        cout << u8"\n\t Ingresa el número de la placa de tu vehículo en el formato solicitado: ";
        cin.ignore();
        cin >> placa;
        transform(placa.begin(), placa.end(), placa.begin(), ::toupper); //Ponerlo todo en mayusculas, en caso de que no lo este
        formato  = validarPlaca(placa);
    }while(!formato);
    v->setPlaca(placa);

    /* ------------- ELECCIÓN DE LA TARIFA DE PAGO ----------------*/
    int selTarifa;
    string tarifa;
    bool selec = false;
    do{
        cout << "\n\t ====> TARIFAS <====";
        cout << "\n\n\t [1] Por Horas (15 min. de tolerancia por hora)";
        cout << u8"\n\t [2] Por día (24 horas completas de pago)";
        cout << u8"\n\t [3] Pensión (Pago por un mes completo)"; ///////////////////////////////Verificar si era por mes o por semana
        cout << "\n\n\t Elige la tarifa que se adapte a tus necesidades: ";
        cin >> selTarifa;

        switch(selTarifa){
            case 1:
                tarifa = "horas";
                selec = true;
                break;
            case 2:
                tarifa = "dia";
                selec = true;
                break;
            case 3:
                tarifa = "pension";
                selec = true;
                break;
        }
    }while(!selec);

    /* ---------- VERIFICAR CONVENIO CON EMPRESA ---------- */
    int resp;
    bool conv;
    do{
        cout << u8"\n\t Tienes un código de convenio de empresa?";
        cout << u8"\n\n\t [1] Sí";
        cout << u8"\n\t [2] No";
        cin >> resp;

        switch(resp){
            case 1:
                conv = true;
                break;
            case 2: conv = false;
                break;
            default: cout << u8"\n\t Respuesta inválida";
                break;
        }
    }while(resp != 1 && resp != 2);

    Convenio* conve;
    if(conv){
       codeConvenio(conve); 
    }

    Espacio(0, v, conve, tarifa); //Falta la parte de el numero de espacio y logica para que numeros seran destinados a que vehiculos
    
}

/* ======================== ADMINISTRACIÓN DEL SISTEMA ======================= */

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
            case 1: cout << "Administrar"; ///////////////Agregar opciones de administracion (Implementación en archivo.h)
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

/*-------------------------- INGRESAR CODIGO DE CONVENIO -------------------*/

bool codeConvenio(Convenio &conve){
    string code;
    bool verifyCode = false, digits4 = false;
    int cont = 0;
    do{
        do{
            cout << u8"Ingresa el código de convenio (4 números): ";
            cin >> code;
            digits4 = verificar4Digits(code); //Verficación de número con 4 dígitos
        }while(!digits4);
        
        if(code == MEXABANK){
            conve = MexaBank();
            verifyCode = true;
            return true;
        }else if(code == SIS){
            conve = Sis();
            verifyCode = true;
            return true;
        }else if(code == SEGURO){
            conve = Seguro();
            verifyCode = true;
            return true;
        }else{
            ++cont;
        }
    }while(!verifyCode && cont != 3);

    cout << u8"\n\t Intentos de registro de código agotados (3 intentos)";
    return false;
}

/*-------------------------- VERIFICAR FORMATO CORRECTO DE PLACA -------------------*/

bool validarPlaca(const string placa){
    //Verificar longitud de la cadena
    if(placa.length() == 9){
        //Verificar cada digito del formato "AAA-000-A"
        if(!(!isdigit(placa[0]))) return false;
        if(!(!isdigit(placa[1]))) return false;
        if(!(!isdigit(placa[2]))) return false;
        if(placa[3] != '-') return false;
        if(!isdigit(placa[4])) return false;
        if(!isdigit(placa[5])) return false;
        if(!isdigit(placa[6])) return false;
        if(!(!isdigit(placa[7]))) return false;

        //Formato cumplido
        return true;    
    }
    //Formato no cumplido
    return false;
}