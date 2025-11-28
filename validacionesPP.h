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
    //Verificar longitud de la cadena

    //Si el vehiculo es un auto
    if(tVehiculo == 1){
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
    }else if (tVehiculo == 2){
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
    }else{
        //Si el vehiculo es un camión
        
    }
    //Formato no cumplido
    return false;
}
