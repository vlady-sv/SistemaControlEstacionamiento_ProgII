#ifndef VALIDACIONESPP_H
#define VALIDACIONESPP_H
#include <iostream>
#include <string>
using namespace std;

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

/*-------------------------- VERIFICAR FORMATO CORRECTO DE PLACA -------------------*/

bool validarPlaca(const string placa, int tVehiculo){
    //Si el vehiculo es un auto
    if(tVehiculo == 1){
        //Verificar longitud de la cadena
        if(placa.length() == 9){
            //Verificar cada digito del formato "AAA-000-A"
            if(placa[0] < 'A' || placa[0] > 'Z') return false;
            if(placa[1] < 'A' || placa[1] > 'Z') return false;
            if(placa[2] < 'A' || placa[2] > 'Z') return false;
            if(placa[3] != '-') return false;
            if(!isdigit(placa[4])) return false;
            if(!isdigit(placa[5])) return false;
            if(!isdigit(placa[6])) return false;
            if(placa[7] != '-') return false;
            if(placa[8] < 'A' || placa[8] > 'Z') return false;

            //Formato cumplido
            return true;    
        }
        //Si el vehiculo es una moto
    }else if (tVehiculo == 2){
        //Verificar longitud de la cadena
        if(placa.length() == 6){
            //Verificar cada digito del formato "00AAA0"
            if(!isdigit(placa[0])) return false;
            if(!isdigit(placa[1])) return false;
            if(placa[2] < 'A' || placa[2] > 'Z') return false;
            if(placa[3] < 'A' || placa[3] > 'Z') return false;
            if(placa[4] < 'A' || placa[4] > 'Z') return false;
            if(!isdigit(placa[5])) return false;

            //Formato cumplido
            return true;    
        }
        //Si el vehiculo es un camión
    }else{
        //Verificar longitud de la cadena
        if(placa.length() == 9){
            //Verificar cada digito del formato "AA-0000-A"
            if(placa[0] < 'A' || placa[0] > 'Z') return false;
            if(placa[1] < 'A' || placa[1] > 'Z') return false;
            if(placa[2] != '-') return false;
            if(!isdigit(placa[3])) return false;
            if(!isdigit(placa[4])) return false;
            if(!isdigit(placa[5])) return false;
            if(!isdigit(placa[6])) return false;
            if(placa[7] != '-') return false;
            if(placa[8] < 'A' || placa[8] > 'Z') return false;

            //Formato cumplido
            return true;  
        }
    }
    //Formato no cumplido
    return false;
}
#endif