#ifndef FACTURAS_H
#define FACTURAS_H
#include "TicketSalida.h"

/* Función auxiliar para extraer la fecha del nombre del archivo y hacer cortes de caja*/
string extraerFecha(const string nombreArchivo){
    size_t lastGuionBajo = nombreArchivo.rfind('_'); //Busca la ultima posicion donde aparece el caracter indicado
    size_t punto = nombreArchivo.rfind('.'); //Busca el punto de .dat para saber donde nos detendremos

    if(lastGuionBajo == string::npos || punto == string::npos){
        cout << "\n\t Error";
        return "";
    }
    return nombreArchivo.substr(lastGuionBajo+1, punto - lastGuionBajo -1);
}   

/* Funcion auxiliar para convertir la string de la fecha en una variable de tiempo y faciliar comparaciones*/
tm stringToTiempo(const string fecha){
    tm tmFecha = {};
    istringstream ss(fecha);
    ss >> get_time(&tmFecha, "%d-%m-%Y");
    return tmFecha;
}

/* Funcion auxiliar para leer el contenido de los archivo de Ticket_Salida*/
TicketSalida leerTicketSalida(const fs::path& archivoPath) {
    fstream archivo(archivoPath, ios::binary | ios::in);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de ticket salida");
    }

    //Leer Espacio
    Espacio e;
    archivo.read(reinterpret_cast<char*>(&e), sizeof(Espacio));

    //Leer los campos especificos de TicketSalida
    char horaSalida[15];
    char diaSalida[15];
    archivo.read(reinterpret_cast<char*>(&horaSalida), sizeof(horaSalida));
    archivo.read(reinterpret_cast<char*>(&diaSalida), sizeof(diaSalida));

    double totalPagar;
    int duracion;
    archivo.read(reinterpret_cast<char*>(&totalPagar), sizeof(double));
    archivo.read(reinterpret_cast<char*>(&duracion), sizeof(int));

    archivo.close();
    return TicketSalida(e, horaSalida, diaSalida, totalPagar, duracion);
}

class Facturas_CorteCaja{
    private:
        double totalGanancias;
        int cantTickets;

    public:
        Facturas_CorteCaja(double, int);
        Facturas_CorteCaja(Facturas_CorteCaja&);
        void set_totalGanancias(double);
        void set_cantTickets(int);
        double get_totalGanancias();
        int get_cantTickets();
        void mostrarFactura(string);
        friend void corteCaja(Facturas_CorteCaja&);
        friend void facturaSemana(Facturas_CorteCaja&);
        friend void facturaMes(Facturas_CorteCaja&);
        friend void facturaGeneral(Facturas_CorteCaja&);
        friend Facturas_CorteCaja consultarTicket(string, string);
        friend void guardarArchivo(const Facturas_CorteCaja&, string);
        Facturas_CorteCaja& operator=(const Facturas_CorteCaja&);
};

Facturas_CorteCaja::Facturas_CorteCaja(double totalGanancias=0.0, int cantTickets=0){
    this->totalGanancias = totalGanancias;
    this->cantTickets = cantTickets;
}

Facturas_CorteCaja::Facturas_CorteCaja(Facturas_CorteCaja& obj){
    totalGanancias = obj.totalGanancias;
    cantTickets = obj.cantTickets;
}

void Facturas_CorteCaja::set_totalGanancias(double totalGanancias){
    this->totalGanancias = totalGanancias;
}

void Facturas_CorteCaja::set_cantTickets(int cantTickets){
    this->cantTickets = cantTickets;
}

double Facturas_CorteCaja::get_totalGanancias(){
    return totalGanancias;
}

int Facturas_CorteCaja::get_cantTickets(){
    return cantTickets;
}

void Facturas_CorteCaja::mostrarFactura(string tipo){
    if(tipo == "corte"){
        cout << "\n\t\t\t **** CORTE DE CAJA " << tiempoToStringFecha(reloj::now()) << " ****";
        cout << "\n\t - Tickets contabilizados: " << cantTickets;
        cout << u8"\n\t - Ganancias del día $" << totalGanancias;
    }else if(tipo == "semana"){
        cout << "\n\t\t\t **** GANANCIAS DE LA ULTIMA SEMANA ****";
        cout << "\n\t - Cortes contabilizados: " << cantTickets;
        cout << u8"\n\t - Ganancias de la semana $" << totalGanancias;
    }else if(tipo == "mes"){
        cout << "\n\t\t\t **** GANANCIAS DEL ULTIMO MES ****";
        cout << "\n\t - Cortes contabilizados: " << cantTickets;
        cout << u8"\n\t - Ganancias del mes $" << totalGanancias;
    }else if(tipo == "general"){
        cout << "\n\t\t\t **** GANANCIAS GENERALES ****";
        cout << "\n\t - Cortes contabilizados: " << cantTickets;
        cout << u8"\n\t - Ganancias totales $" << totalGanancias;
    }
}

void corteCaja(Facturas_CorteCaja& obj){
    tiempo hoy = reloj::now(); 
    string fechaHoy = tiempoToStringFecha(hoy); //Convertimos la fecha a string

    fs::path carpeta = "Tickets_Salida";

    for(auto& tck: fs::directory_iterator(carpeta)){
        string nombre = tck.path().filename().string();
        string fechaArchivo = extraerFecha(nombre);

        if(fechaArchivo == fechaHoy){ //Si la fecha del archivo es exactamente igual a la fecha del dia de hoy entramos
            fstream archivo(tck.path(), ios::binary|ios::in);
            if(!archivo.is_open()){
                cout << "\n\t Error al abrir un archivo";
            }else{
                TicketSalida tS = leerTicketSalida(tck.path());
                obj.totalGanancias += tS.get_totalPagar(); //Vamos guardando el total de ganancias
                archivo.close();
                obj.cantTickets++; //Y la cantidad de tickets que se cuentan
            }

        }
    }


    fs::path cortes = "Cortes_Caja";
    if(!fs::exists(cortes)){
        fs::create_directories(cortes);
    }
    string nomArchivo;
    nomArchivo = "Corte-Caja_" + fechaHoy + ".dat";
    fs::path saveArchivo = cortes/nomArchivo;
    
    fstream corteCaja;
    corteCaja.open(saveArchivo, ios::binary|ios::out);
    if(!corteCaja.is_open()){
        cout << u8"\n\t El archivo de corte de caja no se abrio correctamente [Error en crear archivo de corte de caja]";
        return;
    }
    if(!corteCaja.write(reinterpret_cast<const char*>(&obj), sizeof(Facturas_CorteCaja))){
        cout << "\n\t Error al guardar el ticket [Error en guardar ticket salida]";
    }
    corteCaja.close();
}

void facturaSemana(Facturas_CorteCaja& obj){
    tiempo hoy = reloj::now();
    tiempo semana = hoy - chrono::hours(24*7);

    string fechaHoy = tiempoToStringFecha(hoy);
    string fechaSemana = tiempoToStringFecha(semana);

    for(auto& tck: fs::directory_iterator("Tickets_Salida")){
        string nombre = tck.path().filename().string();
        string fechaArchivo = extraerFecha(nombre); //Extraemos la fecha de cada archivo

        /* Convertimos los string a variables de tiempo para poder compararlas*/
        tm tmArchivo = stringToTiempo(fechaArchivo);
        tm tmHoy = stringToTiempo(fechaHoy);
        tm tmSemana = stringToTiempo(fechaSemana);

        time_t tArchivo = mktime(&tmArchivo);
        time_t tHoy = mktime(&tmHoy);
        time_t tSemana = mktime(&tmSemana);

        if(tArchivo >= tSemana && tArchivo <= tHoy){
            fstream archivo(tck.path(), ios::binary|ios::in);
            if(!archivo.is_open()){
                cout << "\n\t Error al abrir un archivo";
            }else{
                TicketSalida tS = leerTicketSalida(tck.path());
                obj.totalGanancias += tS.get_totalPagar(); //Ganancias
                archivo.close();
                obj.cantTickets++; //Tickets contados
            }
        }
    }

    fs::path semanal = "Facturas_Semanales";
    if(!fs::exists(semanal)) fs::create_directories(semanal);

    string nomArchivo;
    nomArchivo = "FSemanal_" + fechaSemana + "_" + fechaHoy + ".dat";
    fs::path saveArchivo = semanal/nomArchivo;

    fstream facSemana;
    facSemana.open(saveArchivo, ios::binary|ios::out);
    if(!facSemana.is_open()){
        cout << u8"\n\t El archivo de factura por semana no se abrio correctamente [Error en crear archivo de factura semanal]";
        return;
    }
    if(!facSemana.write(reinterpret_cast<const char*>(&obj), sizeof(Facturas_CorteCaja))){
        cout << "\n\t Error al guardar el ticket [Error en guardar ticket salida]";
    }
    facSemana.close();
}

void facturaMes(Facturas_CorteCaja& obj){
    tiempo hoy = reloj::now();
    string fechaHoy = tiempoToStringFecha(hoy);
    
    //Extraer mes y año del día actual
    string mesHoy = fechaHoy.substr(3,2);
    string anioHoy = fechaHoy.substr(6,4);

    for(auto& tck: fs::directory_iterator("Tickets_Salida")){
        string nombre = tck.path().filename().string();
        string fechaArchivo = extraerFecha(nombre); //Extraemos la fecha de cada archivo

        /* Extraer mes y año del archivo*/
        string mesArchivo = fechaArchivo.substr(3, 2);
        string anioArchivo = fechaArchivo.substr(6, 4);

        if(mesArchivo == mesHoy && anioArchivo == anioHoy){
            fstream archivo(tck.path(), ios::binary|ios::in);
            if(!archivo.is_open()){
                cout << "\n\t Error al abrir un archivo";
            }else{
                TicketSalida tS = leerTicketSalida(tck.path());
                obj.totalGanancias += tS.get_totalPagar(); //Ganancias
                archivo.close();
                obj.cantTickets++; //Tickets contados
            }
        }
    }

    fs::path mensual = "Facturas_Mensuales";
    if(!fs::exists(mensual)) fs::create_directories(mensual);

    string nomArchivo;
    nomArchivo = "FMensual_" + mesHoy + "-" + anioHoy  + ".dat";
    fs::path saveArchivo = mensual/nomArchivo;

    fstream facMes;
    facMes.open(saveArchivo, ios::binary|ios::out);
    if(!facMes.is_open()){
        cout << u8"\n\t El archivo de factura por semana no se abrio correctamente [Error en crear archivo de factura semanal]";
        return;
    }
    if(!facMes.write(reinterpret_cast<const char*>(&obj), sizeof(Facturas_CorteCaja))){
        cout << "\n\t Error al guardar el ticket [Error en guardar ticket salida]";
    }
    facMes.close();
}

void facturaGeneral(Facturas_CorteCaja& obj){
    tiempo hoy = reloj::now();
    string fechaHoy = tiempoToStringFecha(hoy);

    for(auto& tck: fs::directory_iterator("Tickets_Salida")){
        string nombre = tck.path().filename().string();
        //Leemos todos los tickets existentes
        fstream archivo(tck.path(), ios::binary|ios::in);
        if(!archivo.is_open()){
            cout << "\n\t Error al abrir un archivo";
        }else{
            TicketSalida tS = leerTicketSalida(tck.path());
            obj.totalGanancias += tS.get_totalPagar(); //Ganancias
            archivo.close();
            obj.cantTickets++; //Tickets contados
        }
        
    }

    fs::path general = "Facturas_Generales";
    if(!fs::exists(general)) fs::create_directories(general);

    string nomArchivo;
    nomArchivo = "FGeneral_" + fechaHoy  + ".dat";
    fs::path saveArchivo = general/nomArchivo;

    fstream facGeneral;
    facGeneral.open(saveArchivo, ios::binary|ios::out);
    if(!facGeneral.is_open()){
        cout << u8"\n\t El archivo de factura por semana no se abrio correctamente [Error en crear archivo de factura semanal]";
        return;
    }
    if(!facGeneral.write(reinterpret_cast<const char*>(&obj), sizeof(Facturas_CorteCaja))){
        cout << "\n\t Error al guardar el ticket [Error en guardar ticket salida]";
    }
    facGeneral.close();
}

Facturas_CorteCaja consultarTicket(string carpeta, string nombre){
    fs::path rutaArchivo;
    bool encontrado = false;
    if(carpeta == "Cortes_Caja"){
        for(auto& tck: fs::directory_iterator(carpeta)){
            fs::path ruta = tck.path();
            string nomArchivo = ruta.stem().string();
            if(nomArchivo == nombre){
                rutaArchivo = ruta;
                encontrado = true;
                break;
            }
        }
    }else if(carpeta == "Facturas_Semanales"){
        for(auto& tck: fs::directory_iterator(carpeta)){
            fs::path ruta = tck.path();
            string nomArchivo = ruta.stem().string();
            if(nomArchivo == nombre){
                rutaArchivo = ruta;
                encontrado = true;
                break;
            }
        }
    }else if(carpeta == "Facturas_Mensuales"){
        for(auto& tck: fs::directory_iterator(carpeta)){
            fs::path ruta = tck.path();
            string nomArchivo = ruta.stem().string();
            if(nomArchivo == nombre){
                rutaArchivo = ruta;
                encontrado = true;
                break;
            }
        }
    }else if(carpeta == "Facturas_Generales"){
        for(auto& tck: fs::directory_iterator(carpeta)){
            fs::path ruta = tck.path();
            string nomArchivo = ruta.stem().string();
            if(nomArchivo == nombre){
                rutaArchivo = ruta;
                encontrado = true;
                break;
            }
        }
    }

    if(!encontrado){
        cout << "\n\t El archivo con el nombre " << nombre << " no fue encontrado";
        return Facturas_CorteCaja(0.0, 0);
    }

    Facturas_CorteCaja factura;
    fstream archivo;
    archivo.open(rutaArchivo, ios::binary|ios::in);
    if(!archivo.is_open()){
        cout << u8"\n\t El archivo no se abrió correctamente";
        return Facturas_CorteCaja(0.0, 0);
    }
    archivo.read(reinterpret_cast<char*>(&factura), sizeof(Facturas_CorteCaja));
    archivo.close();
    return factura;
}

Facturas_CorteCaja& Facturas_CorteCaja::operator=(const Facturas_CorteCaja& fac){
    if(this != &fac){
        totalGanancias = fac.totalGanancias;
        cantTickets = fac.cantTickets;
    }
    return *this;
}

#endif