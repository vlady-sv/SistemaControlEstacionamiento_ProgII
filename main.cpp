#include <windows.h>
#include <algorithm>
#include "Espacio.h"
#include "verificar.h"
#include "ManageArchivos.h"
#include "usuario.h"

/*CODIGOS DE VERIFICACION EN ORDEN:
ADMNISTRADOR, APAGAR SISTEMA, CONVENIO MEXABANK, CONVENIO SECRETARIA DE INNOVACIÓN SOCIAL, CONVENIO EMPRESA DE SEGUROS*/
#define CADMIN "0123"
#define CAPAGAR "0000"

/* MAXIMA CAPACIDAD DE ALOJO POR VEHICULO*/
 
#define AUTOS 600  /* Cajones de estacionamiento del 1-500 */
#define CAMIONETAS 300 /*Cajones de estacionamiento del 501-1000*/
#define MOTOS 600  /*Cajones de estacionamiento del 1001-1500*/

//Prototipos

void usuario();
void salir();
void administrador(bool &valido);
bool apagar();

// Menú principal

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int opc, cAutos, cCamionetas, cMotos;
    bool valido = false;

    if(!verificarCascaron()){
        if(CrearArchivos() == 1){
            cascaronCreado();
        }else{
            cout << "\n\t Fallo al crear el cascaron.";
            return 0;
        }
    }


    do{
        do{
            cout << "\n\t [1] Ingresar al estacionamiento";
            cout << "\n\t [2] Salir del estacionamiento";
            cout << "\n\t [3] Administrador";
            cout << u8"\n\n\t Elige una opción: ";
            cin >> opc;
        }while(opc != 1 && opc != 2);

        switch(opc){
            case 1: usuario();
                break;
            case 2: salir();
                break;
            case 3: administrador(valido);
                break;
            default: cout << u8"\n\tOpción inválida\n";
                break;
        }
    }while(valido == false);

    return 0;
}

/* ======================== OPCIONES PARA MOSTRAR AL USUARIO ======================= */

void salir(){
    int opcion, folio;
    bool siEsta = false;
    fstream archivo;
    Espacio e, blanco;

    do{
        cout << "\n---------------------------------------------------\n";
        cout << u8"\n\t ---> MENÚ <---";
        cout << u8"\n\t [1] Ingresar el número de folio del ticket.";
        cout << u8"\n\t [2] Ticket o folio perdido.";
        cout << u8"\n\n\t Elige una opción: ";

        if(opcion == 2){
            cout << u8"\n\t Por favor, dirijase a la oficina de ayuda del estacionamiento.";
            return;
        }
        do{
            cout << u8"\n\t Ingrese el número de folio del ticket.";
            cin >> folio;
            if(!verificarFolio()) cout << u8"\n\t Por favor, ingrese un número de folio válido.";
        }while(!verificarFolio());

        string tVehiculo;
        if(folio / 100000 == 1){
            tVehiculo = "autos.dat";
        }else if(folio / 100000 == 2){
            tVehiculo = "camionetas.dat";
        }else{
            tVehiculo = "motos.dat";
        }
        
        
        // Implementar logica para buscar el espacio segun el folio del ticket //
        archivo.open(tVehiculo, ios::binary|ios::in|ios::out);
        if(!archivo){
            cout << "\n\t Lo sentimos, ha ocurrido un error en el sistema [ESTACIONAMIENTO ESPACIOS].";
        }
        archivo.seekg(ios::beg);
        while(archivo.eof()){
            archivo.read(reinterpret_cast<char*>(&e), sizeof(Espacio));
            if(e.get_folio() == folio){
                siEsta = true;
                break;
            }
        }

        if(!siEsta){
            cout << "\n\t Lo sentimos el folio no se ha encontrado, intente ingresarlo nuevamente.";
        }else{
            //Implementar logica para mostrar ticket de cobro

            blanco = Espacio(e.get_numEspacio(), 0, nullptr, nullptr, "", false);
            //archivo.seekp()
        }


    }while(!siEsta);

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
                }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
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





