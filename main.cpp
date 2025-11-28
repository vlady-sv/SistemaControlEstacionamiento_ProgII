#include <windows.h>
#include <algorithm>
#include "Espacio.h"
#include "verificar.h"
#include "ManageArchivos.h"

/*CODIGOS DE VERIFICACION EN ORDEN:
ADMNISTRADOR, APAGAR SISTEMA, CONVENIO MEXABANK, CONVENIO SECRETARIA DE INNOVACIÓN SOCIAL, CONVENIO EMPRESA DE SEGUROS*/
#define CADMIN "0123"
#define CAPAGAR "0000"
#define MEXABANK "3578"
#define SIS "1598"
#define SEGURO "6482"

/* MAXIMA CAPACIDAD DE ALOJO POR VEHICULO*/
 
#define AUTOS 500  /* Cajones de estacionamiento del 1-500 */
#define CAMIONETAS 500 /*Cajones de estacionamiento del 501-1000*/
#define MOTOS 500  /*Cajones de estacionamiento del 1001-1500*/

//Prototipos

void usuario();
void salir();
void administrador(bool &valido);
bool apagar();
bool validarPlaca(const string);
bool verificar4Digits(const string codigo);
bool verificarFormatoPlaca(const string placa, bool moto);
Convenio* codeConvenio();

// Menú principal

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int opc, cAutos, cCamionetas, cMotos;
    bool valido = false;

    if(!verificarCascarones()){
        if(CrearArchivos() == 1){
            cascaronesCreados();
        }else{
            cout << "\n\t Fallo al crear el cascaron.";
            return 0;
        }
    }


    do{
        //Obtener cantidad de lugares ocupados
        cAutos =  contAutos();
        cCamionetas = contCamionetas();
        cMotos = contMotos();
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

void usuario(){
    Vehiculo* v;
    int tipoVehiculo;
    bool auxVe = true, formato = false, moto;
    string placa, vehiculo;
    do{
        cout << "\n\t [1] Auto";
        cout << "\n\t [2] Moto";
        cout << "\n\t [3] Camioneta";
        cout << u8"\n\n\t Tipo de vehículo: ";
        cin >> tipoVehiculo;

        switch(tipoVehiculo){
            case 1:
                v = new Auto();
                auxVe=false;
                moto = false;
                break;
            case 2:
                v = new Moto();
                auxVe=false;
                moto = true;
                break;
            case 3:
                v = new Camioneta();
                auxVe=false;
                moto = false;
                break;
            default: cout << u8"\n\n\t Opción inválida";
                break;
        }
        
    }while(auxVe);

    /* ----------- LLENAR LOS DATOS PARA EL ESPACIO EN EL ESTACIONAMIENTO ---------------- */

    //Verificar que haya espacio suficiente dependiendo del tipo de vehiculo del usuario
    int cAutos, cCamionetas, cMotos;

    if(tipoVehiculo == 1){
        cAutos = contAutos();
        if(cAutos == AUTOS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cAutos;
    }else if(tipoVehiculo == 2){
        cCamionetas = contCamionetas();
        if(cCamionetas == CAMIONETAS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cCamionetas;
    }else{
        cMotos = contMotos();
        if(cMotos == MOTOS){
            cout << u8"\n\t Lo sentimos, el estacionamiento se encuentra lleno.";
            cout << u8"\n\t Por favor, dé la vuelta. Gracias por su visita.";
            return;
        }
        ++cMotos;
    }


    /* INGRESAR LA PLACA DEL AUTO Y VERIFICAR EL FORMATO CORRECTO DE LA MISMAA*/
    do{
        cout << "\n\t\t ====> FORMATO DE LA PLACA <====";
        if(!moto) cout << "\n\t 'AAA-000-A' (Los guiones tambien deben ingresarse)";
        else cout << "\n\t '00AAA0' (Sin guiones)";
        cout << u8"\n\t Ingresa el número de la placa de tu vehículo en el formato solicitado: ";
        cin.ignore();
        cin >> placa;
        transform(placa.begin(), placa.end(), placa.begin(), ::toupper); //Ponerlo todo en mayusculas, en caso de que no lo este
        formato  = validarPlaca(placa, moto);
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

    Convenio* conve = nullptr;
    if(conv){
       conve = codeConvenio(); 
    }

    //Actualizar la cantidad de lugares ocupados para vehiculos
    string tVehiculo;
    if(tipoVehiculo == 1){
        actualizarAutos(cAutos);
        tVehiculo = "autos"; //Usado para saber que archivo de estacionamiento hay que abrir
    }else if(tipoVehiculo == 2){
        actualizarCamionetas(cCamionetas);
        tVehiculo = "camionetas";
    }else{
        actualizarMotos(cMotos);
        tVehiculo = "motos";
    }

    //Guardar todo en el espacio de estacionamiento

    fstream archivo;
    Espacio aux;
    tVehiculo = tVehiculo + ".dat";
    archivo.open(tVehiculo, ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Lo sentimos ha ocurrido un error en el sistema.";
    }
    archivo.seekg(ios::beg);
    while(!archivo.eof()){
        archivo.read(reinterpret_cast<char*>(&aux), sizeof(Espacio));
        if(!aux.get_ocupado()) break; //Si el cajon de estacionamiento se encuentra vacio se ocupa ese lugar
    }

    int numEspacio = aux.get_numEspacio();
    int folio = leer_folios() + 1;
    Espacio e(numEspacio, folio, v, conve, tarifa, true); //Guarda todos los datos en una variable de espacio para posteriormente registrarla

    if(tipoVehiculo == 1){
        archivo.seekp((numEspacio-1));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else if(tipoVehiculo == 2){
        archivo.seekp((numEspacio-501));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }else{
        archivo.seekp((numEspacio-1001));
        archivo.write(reinterpret_cast<char*>(&e), sizeof(Espacio));
    }

    archivo.close();

    //Mostrarle al usuario su ticket de ingreso y especificarle que necesita su folio para salir

    
}

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

/*-------------------------- VERIFICAR FORMATO CORRECTO DE PLACA -------------------*/

bool validarPlaca(const string placa, bool moto){
    //Verificar longitud de la cadena

    //Si el vehiculo es un auto
    if(!moto){
        if(placa.length() == 9){
            //Verificar cada digito del formato "AAA-000-A"
            if(placa[0] < 'A' || placa[0] > 'Z') return false;
            if(placa[1] < 'A' || placa[1] > 'Z') return false;
            if(placa[2] < 'A' || placa[2] > 'Z') return false;
            if(placa[3] != '-') return false;
            if(!isdigit(placa[4])) return false;
            if(!isdigit(placa[5])) return false;
            if(!isdigit(placa[6])) return false;
            if(placa[7] < 'A' || placa[7] > 'Z') return false;

            //Formato cumplido
            return true;    
        }
    }else{
        //Si el vehiculo es una moto
        if(placa.length() == 6){
            //Verificar cada digito del formato "00AAA0"
            if(placa[0] < 'A' || placa[0] > 'Z') return false;
            if(placa[1] < 'A' || placa[1] > 'Z') return false;
            if(!isdigit(placa[2])) return false;
            if(!isdigit(placa[3])) return false;
            if(!isdigit(placa[4])) return false;
            if(placa[5] < 'A' || placa[7] > 'Z') return false;

            //Formato cumplido
            return true;    
        }
    }
    //Formato no cumplido
    return false;
}