#ifndef CALCULOTIEMPO_H
#define CALCULOTIEMPO_H

#include <chrono>
using namespace std::chrono;
using reloj = system_clock;
using tiempo = system_clock::time_point;

/* 12 horas de apertura del estacionamiento (formato 24 hrs)*/
#define ABIERTO 8 // Hora de apertura del estacionamiento
#define CERRADO 20 // Hora de cierre del estacionamiento

int stringToSegundos(const string hms){
    int hh = stoi(hms.substr(0,2));
    int mm = stoi(hms.substr(3,2));
    int ss = stoi(hms.substr(6,2));

    return hh*3600 + mm*60 + ss; //Devuelve la hora en segundos
}

int horasCobrar(string llegada, string salida){
    int llegadaSegs = stringToSegundos(llegada);
    int salidaSegs = stringToSegundos(salida);

    if(salidaSegs < llegadaSegs){
        cout << "\n\t [Error] Hay un error en las horas de llegada y salida (Salida > llegada)";
        return 0;
    }

    int totalSegs = salidaSegs - llegadaSegs;

    int horas = totalSegs / 3600; //Obtención de las horas
    int minutos = (totalSegs % 3600) / 60; //Obtención de los minutos
    
    if(minutos > 15) horas++; /* Manejo de una tolerancia de 15 minutos por hora, si 
    pasaron mas de 15 minutos se cobra la hora completa*/

    return horas;
}

int diasCobrar(string llegada, string salida){
    int llegadaSegs = stringToSegundos(llegada);
    int salidaSegs = stringToSegundos(salida);

    if(salidaSegs < llegadaSegs){
        cout << "\n\t [Error] Hay un error en las horas de llegada y salida (Salida > llegada)";
        return 0;
    }
    
    int totalSegs = salidaSegs - llegadaSegs;
    if(totalSegs <= 0){
        cout << u8"\n\t [Error] Hay un error en las horas de llegada y salida (Cálculo <= 0)";
        return 0;
    }
    
    int dias = totalSegs / (24*3600); //Obtención de los días completos
    int restoSegs = totalSegs % (24*3600); //Obtención del tiempo restante (en segundos)

    if(dias == 0) dias++;
    if(dias > 1){
        if(restoSegs > (30 * 60)) dias++; /*Tolerancia de 30 minutos, si en el último día que estuvo el cliente 
        estuvo por más de 30 minutos se cobra el día completo, esto solo aplica del segundo día en adelante*/
    }
    return dias;
}
#endif