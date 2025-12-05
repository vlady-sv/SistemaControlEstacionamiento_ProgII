#include "Espacio.h"

int horasCobrar(tiempo llegada, tiempo salida){
    const int ABIERTO = 8; // Hora de apertura del estacionamiento
    const int CERRADO = 20; // Hora de cierre del estacionamiento
    const int TOLERANCIA_MIN = 15; // Tolerancia de 15 minutos para cobrar la hora completa
    int horasTotales = 0; /* Horas que el cliente estuvo en el estacionamiento en el
    horario de cada dia */

    //Conversión de las horas a variable time_t para hacer los calculos con mayor facilidad
    time_t inicio = reloj::to_time_t(llegada);
    time_t fin = reloj::to_time_t(salida);


    while(inicio < fin){
        tm tmInicio;

        #ifdef _WIN32
            localtime_s(&tmInicio, &inicio);
        #else
            tmInicio = *localtime(&inicio);
        #endif

        //Obtener los valores del dia actual para hacer los calculos

        //Apertura
        tm tmApertura = tmInicio;
        tmApertura.tm_hour = ABIERTO;
        tmApertura.tm_min = 0;
        tmApertura.tm_sec = 0;

        //Cierre
        tm tmCierre = tmInicio;
        tmCierre.tm_hour = CERRADO;
        tmCierre.tm_min = 0;
        tmCierre.tm_sec = 0;

        time_t abiertoDia = mktime(&tmApertura);
        time_t cerradoDia = mktime(&tmCierre);

        //Determinar el inicio de cobro del día
        time_t inicioCobro = max(inicio, abiertoDia);
        //Determinar el final de cobro del día
        time_t finCobro = max(fin, cerradoDia);

        if(inicioCobro < finCobro){
            int segundos = (int)(finCobro - inicioCobro);
            int minutos = (segundos % 3600) / 60;
            int horas = segundos / 3600;
            
            //Revisar la tolerancia de 15 minutos
            if(minutos > 15) horas++; //Si es mayor se redondea hacia arriba

            horasTotales += horas; //Se acumulan el total de horas
        }

        // Pasamos al día siguiente (se valida en el while principal si es que hay otro día)
        tmInicio.tm_mday += 1;
        tmInicio.tm_hour = 0;
        tmInicio.tm_min = 0;
        tmInicio.tm_sec = 0;
        inicio = mktime(&tmInicio);
    }

    return horasTotales;
}

int diasCobrar(tiempo llegada, tiempo salida){
    int totalDias;

    return totalDias;
}