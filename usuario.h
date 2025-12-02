#include <windows.h>
#include <algorithm>
#include "Espacio.h"
#include "verificarArchivos.h"
#include "ManageArchivos.h"
#include "validacionesPP.h"

/*CODIGOS DE VERIFICACION EN ORDEN:
ADMNISTRADOR, APAGAR SISTEMA, CONVENIO MEXABANK, CONVENIO SECRETARIA DE INNOVACIÓN SOCIAL, CONVENIO EMPRESA DE SEGUROS*/
#define CADMIN "0123"
#define MEXABANK "3578"
#define SIS "1598"
#define SEGURO "6482"

/* MAXIMA CAPACIDAD DE ALOJO POR VEHICULO*/
 
#define AUTOS 600  /* Cajones de estacionamiento del 1-600 */
#define MOTOS 600 /*Cajones de estacionamiento del 601-1200*/ //Cambiar por camiones
#define CAMIONES 300  /*Cajones de estacionamiento del 1201-1500*/

void usuario(){
    Vehiculo* v;
    int tipoVehiculo;
    bool auxVe = true, formato = false;
    string placa, vehiculo;
    do{
        cout << "\n\t [1] Automóvil";
        cout << "\n\t [2] Moto";
        cout << u8"\n\t [3] Camión";
        cout << u8"\n\n\t Tipo de vehículo: ";
        cin >> tipoVehiculo;

        switch(tipoVehiculo){
            case 1:
                v = new Auto();
                auxVe=false;
                break;
            case 2:
                v = new Moto();
                auxVe=false;
                break;
            case 3:
                v = new Camiones();
                auxVe=false;
                break;
            default: cout << u8"\n\n\t Opción inválida";
                break;
        }
        
    }while(auxVe);

    /* ----------- LLENAR LOS DATOS PARA EL ESPACIO EN EL ESTACIONAMIENTO ---------------- */

    //Verificar que haya espacio suficiente dependiendo del tipo de vehiculo del usuario
    int cAutos, cMotos, cCamiones;

    if(tipoVehiculo == 1){
        cAutos = contAutos(false);
        if(cAutos == AUTOS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cAutos;
    }else if(tipoVehiculo == 2){
        cMotos = contMotos(false);
        if(cMotos == MOTOS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cMotos;
    }else{
        cCamiones = contCamiones(false);
        if(cCamiones == CAMIONES){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cCamiones;
    }


    /* INGRESAR LA PLACA DEL AUTO Y VERIFICAR EL FORMATO CORRECTO DE LA MISMA*/
    do{
        cout << "\n\t\t ====> FORMATO DE LA PLACA <====";
        if(tipoVehiculo == 1) 
            cout << u8"\n\t 'AAA-000-A' (Los guiones tambien deben ingresarse)";   //Caso Vehículo = Placa Automóvil
        else if(tipoVehiculo == 2) 
            cout << "\n\t '00AAA0' (Sin guiones)";      //Caso Vehículo = Placa Moto
        else 
            cout  << "\n\t 'dda' (Los guiones también deben ingresarse)";       //Caso Vehículo = Placa Camión  ////////////////////////////////////Averiguar cual es la placa de los camiones (formato)
        cout << u8"\n\t Ingrese el número de la placa de su vehículo en el formato solicitado: ";
        cin.ignore();
        cin >> placa;
        transform(placa.begin(), placa.end(), placa.begin(), ::toupper); //Ponerlo todo en mayusculas, en caso de que no lo este
        formato  = validarPlaca(placa, tipoVehiculo);
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
        cout << "\n\n\t Elija la tarifa que se adapte a sus necesidades (NO HAY CAMBIOS DE TARIFA): ";
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

    /* ------------------------------ VERIFICAR CONVENIO CON EMPRESA ---------------------------------- */
    int resp;
    bool conv;
    do{
        cout << u8"\n\t Tiene un código de convenio de empresa?";
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

    Convenio* conve = nullptr;
    if(conv){
       conve = codeConvenio();      //Si el usuario tiene un convenio pedirlo y verificar que sea real
    }

    
    
    /* ------ ACTUALIZAR LA CANTIDAD DE LUGARES OCUPADOS ----------------*/
    if(tipoVehiculo == 1){
        contAutos(true, cAutos);
    }else if(tipoVehiculo == 2){
        contMotos(true, cMotos);
    }else{
        contCamiones(true, cCamiones);
    }

    //Guardar todo en el espacio de estacionamiento

    fstream archivo;
    Espacio aux;
    archivo.open("estacionamiento.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Lo sentimos ha ocurrido un error en el sistema.";
    }
    
    if(tipoVehiculo == 1){
        int cont = 0;
        while(cont <= 599){
            archivo.seekg((cont)*sizeof(Espacio));
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()) break; //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
            ++cont;
        }
    }else if(tipoVehiculo == 2){
        int cont = 600;
        while(cont <= 1199){
            archivo.seekg((cont)*sizeof(Espacio));
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()) break; //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
            ++cont;
        }
    }else{
        int cont = 1200;
        while(cont <= 1499){
            archivo.seekg((cont)*sizeof(Espacio));
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()) break; //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
            ++cont;
        }
    }

    int numEspacio = aux.get_numEspacio();
    int folio = leer_folios() + 1;
    Espacio e(numEspacio, folio, v, conve, tarifa, true); //Guarda todos los datos en una variable de espacio para posteriormente registrarla

    if(tipoVehiculo == 1){
        archivo.seekp((numEspacio-1));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else if(tipoVehiculo == 2){
        archivo.seekp((numEspacio-601));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else{
        archivo.seekp((numEspacio-1201));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }

    archivo.close();

    ////////////////////////////////////Mostrarle al usuario su ticket de ingreso y especificarle que necesita su folio para salir

    
}


/*-------------------------- INGRESAR CODIGO DE CONVENIO -------------------*/
Convenio* codeConvenio(){
    string code;
    bool digits4 = false;
    int cont = 0;
    do{
        do{
            cout << u8"Ingresa el código de convenio (4 números): ";
            cin >> code;
            digits4 = verificar4Digits(code); //Verficación de número con 4 dígitos
        }while(!digits4);
        
        if(code == MEXABANK){
            return new MexaBank();
        }else if(code == SIS){
            return new Sis();
        }else if(code == SEGURO){
            return new Seguro();
        }else{
            ++cont;
        }
    }while(cont != 3);

    cout << u8"\n\t Intentos de registro de código agotados (3 intentos)";
    return nullptr;
}