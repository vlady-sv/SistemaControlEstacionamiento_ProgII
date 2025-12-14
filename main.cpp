#ifndef MAIN
#define MAIN
#include <windows.h>
#include "Administrador.h"
#include "usuario.h"
#include "Facturas.h"

/* 12 horas de apertura del estacionamiento (formato 24 hrs - de 8hrs a 20hrs)*/

/*CODIGOS DE VERIFICACION EN ORDEN:
ADMNISTRADOR, APAGAR SISTEMA */
#define CADMIN "0123"
#define CAPAGAR "0000"

/* MAXIMA CAPACIDAD DE 
ALOJO POR VEHICULO */
 
#define AUTOS 600  /* Cajones de estacionamiento del 1-500 */
#define CAMIONES 300 /*Cajones de estacionamiento del 501-1000*/
#define MOTOS 600  /*Cajones de estacionamiento del 1001-1500*/

//Prototipos

void usuario();
void salir();
void administrador(bool &valido);
bool apagar();

// Menú principal

int main(){
    cout << "\n\t INICIO";
    SetConsoleOutputCP(CP_UTF8);
    int opc;
    bool valido = false, salirDelSistema = false;

    if(!verificarCascaron()){
        cout << "\n\t INICIO";
        if(CrearArchivos() == 1){
            cout << "\n\t INICIO";
            cascaronCreado();
        }else{
            cout << "\n\t INICIO";
            cout << "\n\t Fallo al crear el cascaron.";
        }
    }

    cout << "\n\t INICIO";
    do{
        do{
            system("cls");
            cout << "\n\t\t\t --- ESTACIONAMIENTO PLAZA PARKING ---";
            cout << "\n\t [1] Ingresar al estacionamiento";
            cout << "\n\t [2] Salir del estacionamiento";
            cout << "\n\t [3] Administrador";
            cout << u8"\n\n\t Elija una opción: ";
            cin >> opc;
        }while(opc < 1 || opc > 3);

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

        if(valido) salirDelSistema = true;
    }while(!salirDelSistema);

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
        cout << u8"\n\t\t ---> MENÚ <---";
        cout << u8"\n\t [1] Ingresar el número de folio del ticket.";
        cout << u8"\n\t [2] Ticket o folio perdido.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opcion;

        if(opcion == 2){
            cout << u8"\n\t Por favor, dirijase a la oficina de ayuda del estacionamiento.\n\n";
            system("pause");
            return;
        }
        do{
            cout << u8"\n\t Ingrese el número de folio del ticket: ";
            cin >> folio;
            if(!verificarFolio(folio)) cout << u8"\n\t Por favor, ingrese un número de folio válido.";
        }while(!verificarFolio(folio));
        
        // Lógica para buscar el espacio según el folio del ticket //
        archivo.open("estacionamiento.dat", ios::binary|ios::in|ios::out);
        if(!archivo){
            cout << "\n\t Lo sentimos, ha ocurrido un error en el sistema [ESTACIONAMIENTO ESPACIOS].";
            return;
        }
        archivo.seekg(0, ios::beg);
        while(archivo.read(reinterpret_cast<char*>(&e), sizeof(Espacio))){
            if(e.get_folio() == folio && e.get_ocupado()){
                siEsta = true;
                break;
            }
        }

        if(!siEsta){
            cout << "\n\t Lo sentimos el folio no se ha encontrado, intente ingresarlo nuevamente.";
        }else{
            int contVehiculo;
            //Tomamos el contador del vehiculo
            if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                contVehiculo = contAutos(false);
                contVehiculo--;
                contVehiculo = contAutos(true, contVehiculo);
            }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                contVehiculo = contMotos(false);
                contVehiculo--;
                contVehiculo = contMotos(true, contVehiculo);
            }else{
                contVehiculo = contCamiones(false);
                contVehiculo--;
                contVehiculo = contCamiones(true, contVehiculo);
            }

            //Construimos el ticket de salida y llenamos los atributos con las funciones establecidas en su misma clase
            TicketSalida tS(e, ".", ".", 0.0, 0);
            tS.establecerSalida();
            tS.calcularDuracion();
            tS.calcularPago();
            guardarTicketS(tS);
            //Mostrandole el ticket al usuario
            tS.imprimirTicket();
            cout << u8"\n\n\t Favor de pagar el monto de cobro del estacionamiento.\n\n";
            system("pause");

            cout << u8"\n\n\t Gracias por visitar Plaza Parking, vuelva pronto!\n\n"; 
            system("pause");
            archivo.clear();
            //Vaciar el espacio del estacionamiento
            int auxnumEspacio = e.get_numEspacio();
            blanco = Espacio(e.get_numEspacio(), 0, ".", ".", ".", 0.0, ".", ".", ".", false);
            archivo.seekp((auxnumEspacio-1) * sizeof(Espacio), ios::beg);
            archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Espacio));

            archivo.close();
        }
    }while(!siEsta);

}

/* ======================== ADMINISTRACIÓN DEL SISTEMA ======================= */

void administrador(bool &valido){
    Administrador admin;
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

    cout << "\n\t\t\t --> Bienvenido Administrador <-- ";

    /* ------------> OPCIONES PARA LA ADMNISTRACION DEL SISTEMA <----------------- */
    int opc;

    do{
        cout << "\n\t [1] Administrar el sistema del estacionamiento";
        cout << "\n\t [2] Volver a la pantalla principal";
        cout << "\n\t [0] Apagar el sistema";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: admin.panelAdministracion();
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
            cout << u8"\n\n\t Código incorrecto\n";
            cout << "\n-----------------------------\n";
            ++cont;
        }

        if(code != CAPAGAR && cont == 3){
            cout << "\n\t Intentos agotados";
        }
    }while(cont < 3);

    return false;
}
#endif
