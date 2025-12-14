#ifndef USUARIO_H
#define USUARIO_H
#include <algorithm>
#include "Espacio.h"
#include "verificarArchivos.h"

/*CODIGOS DE VERIFICACION EN ORDEN:
CONVENIO MEXABANK, CONVENIO SECRETARIA DE INNOVACIÓN SOCIAL, CONVENIO EMPRESA DE SEGUROS*/
#define MEXABANK "3578"
#define SIS "1598"
#define SEGURO "6482"

/* MAXIMA CAPACIDAD DE ALOJO POR VEHICULO*/
 
#define AUTOS 600  /* Cajones de estacionamiento del 1-600 */
#define MOTOS 600 /*Cajones de estacionamiento del 601-1200*/ //Cambiar por camiones
#define CAMIONES 300  /*Cajones de estacionamiento del 1201-1500*/

//Prototipos
Convenio* codeConvenio();

void usuario(){
    Vehiculo* v;
    int tipoVehiculo;
    bool auxVe = true, formato = false;
    string placa, vehiculo[10];
    do{
        cout << "\n\t\t\t --- BIENVENIDO A PLAZA PARKING ---\n";
        cout << "\n\t\t\t ---> Registro para Ingresar <--\n";
        cout << "\n\t [1] Automóvil";
        cout << "\n\t [2] Moto";
        cout << u8"\n\t [3] Camión";
        cout << u8"\n\t [0] Volver al menú principal";
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
                v = new Camion();
                auxVe=false;
                break;
            case 0: return;
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
            delete v;
            return;
        }
        ++cAutos;
    }else if(tipoVehiculo == 2){
        cMotos = contMotos(false);
        if(cMotos == MOTOS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            delete v;
            return;
        }
        ++cMotos;
    }else if(tipoVehiculo == 3){
        cCamiones = contCamiones(false);
        if(cCamiones == CAMIONES){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            delete v;
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
        else if(tipoVehiculo == 3)
            cout  << "\n\t 'AA-0000-A' (Los guiones también deben ingresarse)";       //Caso Vehículo = Placa Camión 
        cout << u8"\n\t Ingrese el número de la placa de su vehículo en el formato solicitado: ";
        cin.ignore();
        cin >> placa;
        transform(placa.begin(), placa.end(), placa.begin(), ::toupper); //Ponerlo todo en mayusculas, en caso de que no lo este
        formato  = validarPlaca(placa, tipoVehiculo);
    }while(!formato);
    v->setPlaca(placa);

    char charPlaca[15];
    strcpy(charPlaca, placa.c_str());

    /* ------------- ELECCIÓN DE LA TARIFA DE PAGO ----------------*/
    int selTarifa;
    char tarifa[15];
    bool selec = false;
    do{
        cout << "\n\t ====> TARIFAS <====";
        cout << "\n\n\t [1] Por Horas (15 min. de tolerancia por hora)";
        cout << u8"\n\t [2] Por día (24 horas completas de pago)";
        cout << u8"\n\t [3] Pensión (Pago por un mes completo)";
        cout << "\n\n\t Elija la tarifa que se adapte a sus necesidades (NO HAY CAMBIOS DE TARIFA): ";
        cin >> selTarifa;

        switch(selTarifa){
            case 1:
                strcpy(tarifa, "horas");
                selec = true;
                break;
            case 2:
                strcpy(tarifa, "dia");
                selec = true;
                break;
            case 3:
                strcpy(tarifa, "pension");
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
        cout << u8"\n\n\t Elija una opción: ";
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

    //Vehiculo
    string tipoAuto = v->getTipo();
    
    //Convenio
    char empresa[30];
    double descuento;
    if(conv){
        strcpy(empresa, conve->get_empresa().c_str());
        descuento = conve ->get_descuento();
    }else{
        strcpy(empresa, "N/A");
        descuento = 0;
    }
    
    /* ------ ACTUALIZAR LA CANTIDAD DE LUGARES OCUPADOS ----------------*/
    if(tipoVehiculo == 1){
        contAutos(true, cAutos);
    }else if(tipoVehiculo == 2){
        contMotos(true, cMotos);
    }else{
        contCamiones(true, cCamiones);
    }

    /*Guardar datos en un espacio de estacionamiento*/

    //Encontrar el numero de espacio en el que entrará el cliente
    fstream archivo;
    Espacio aux;
    archivo.open("estacionamiento.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Lo sentimos ha ocurrido un error en el sistema.";
        delete v;
        delete conve;
        return;
    }
    
    int espacioLibre = -1;
    archivo.clear();
    archivo.seekg(0, ios::beg);
    if(tipoVehiculo == 1){
        for(int i=0; i<600; ++i){
            archivo.seekg(i*sizeof(Espacio), ios::beg);
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()){  //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
                espacioLibre = i;
                break;
            }
        }
    }else if(tipoVehiculo == 2){
        for(int i=600; i<1200; ++i){
            archivo.seekg((i)*sizeof(Espacio), ios::beg);
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()){  //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
                espacioLibre = i;
                break;
            }
        }
    }else{
        for(int i=1200; i<1500; ++i){
            archivo.seekg((i)*sizeof(Espacio), ios::beg);
            archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
            if(!aux.get_ocupado()){ //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
                espacioLibre = i;
                break; 
            }
        }
    }

    if(espacioLibre == -1){
        cout << u8"\n\t Lo sentimos, no hay espacio de estacionamiento disponibles para su tipo de vehículo.";
        delete v;
        delete conve;
        archivo.close();
        return;
    }

    int numEspacio = espacioLibre+1; 
    int folio = leer_folios() + 1;
    char charTvehiculo[10];
    strcpy(charTvehiculo, v->getTipo().c_str());
    Espacio e(numEspacio, folio, charTvehiculo, charPlaca, empresa, descuento, ".", ".", tarifa, true); //Guarda todos los datos en una variable de espacio para posteriormente registrarla

    //Establecer la hora de llegada del usuario
    e.establecerLlegada();

    if(tipoVehiculo == 1){

        archivo.seekp((numEspacio-1)* sizeof(Espacio), ios::beg);
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else if(tipoVehiculo == 2){
        archivo.seekp((numEspacio-1)* sizeof(Espacio), ios::beg);
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else{
        archivo.seekp((numEspacio-1)* sizeof(Espacio), ios::beg);
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }

    archivo.close();
    actualizar_folios(folio); //Actualizamos la entrada del folio
    
    //Construir el ticket de entrada del usuario 
    TicketEntrada tE(e, conv);

    ///Mostrarle al usuario su ticket de ingreso
    tE.mostrarTicketEntrada();
    guardarTicketE(tE);
    cout << endl;
    system("pause");

    delete v;
    delete conve;
}


/*-------------------------- INGRESAR CODIGO DE CONVENIO -------------------*/
Convenio* codeConvenio(){
    string code;
    int cont = 0;
    while(cont<3){
        cout << u8"\n\t Ingresa el código de convenio (4 números): ";
        cin >> code;
        
        if(!verificar4Digits(code)){ //Verficación de número con 4 dígitos
            cout << u8"\n\t Código inválido. Deben ser 4 dígitos númericos";
        }
        if(code == MEXABANK) return new MexaBank();
        if(code == SIS) return new Sis();
        if(code == SEGURO) return new Seguro();
        
        cout << u8"\n\t Código incorrecto";
        ++cont;
    }

    cout << u8"\n\t Intentos de registro de código agotados (3 intentos)";
    return nullptr;
}
#endif