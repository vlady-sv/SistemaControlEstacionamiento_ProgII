/* DOCUMENTO PARA MANEJAR LOS ARCHIVOS DE VERIFICACIÓN Y ALMACENAMIENTO DE DATOS DE DE IDENTIFICACIÓN
(Contadores, Lógicas auxiliares para encontrar otros archivos, creación de cascarón, etc...)*/
#ifndef MANAGEARCH_H
#define MANAGEARCH_H
#include "validacionesPP.h"
#include "Espacio.h"
using namespace std;


/* ------------------ CREAR EL CASCARÓN DEL ARCHIVO DE ADMINISTRACIÓN DE ESPACIOS DEL ESTACIONAMIENTO -------------------------*/
int CrearArchivos(){
    fstream archivo;

    //Archivo para controlar espacios disponibles para autos
    archivo.open("estacionamiento.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    Espacio blanco;
    archivo.seekp(0, ios::beg);
    for(int i=1; i<=1500; i++){       //Espacios reservados para Automóviles
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Espacio));
    }

    archivo.close();

    return 1; //Si todo fue correcto retornamos 1 como indicador
}

 
/* --- CONTADORES DE CANTIDAD DE VEHICULOS QUE HAY EN EL ESTACIONAMIENTO POR CADA TIPO */

/* --------------ARCHIVO QUE MANEJA LA CANTIDAD DE AUTOMÓVILES EN EL ESTACIONAMIENTO ------------------- */
int contAutos(bool actualizar, int nCont = 0){
    fstream archivo;
    int cAutos;

    if(!actualizar){ //Si lo que se quiere es obtener el número de vehiculo de tipo automóvil que hay en el estacionamiento
        archivo.open("contAutos.dat", ios::binary|ios::in);
        if(!archivo){
            cout << "\n\t Archivo contador de camionetas no se abrio correctamente.";
            return -2; //-2 es el indicador de error
        }
        
        if(!archivo.read(reinterpret_cast<char*>(&cAutos), sizeof(int))){
            archivo.close();
            return 0;
        }
        archivo.close();
        return cAutos;

    }else{          /* Si lo que se quiere es actualizar (aumentar/disminuir) el número de vehiculo de tipo automóvil 
                    que hay en el estacionamiento*/
        archivo.open("contAutos.dat", ios::binary|ios::out|ios::trunc);
        if(!archivo){
            cout << "\n\t Archivo contador de autos no se abrio correctamente.";
            return -2;
        }

        archivo.seekp(0);
        if(!archivo.write(reinterpret_cast<char*>(&nCont), sizeof(int))){
            archivo.close();
            return -2;   // -2 para indicar error 
        }
        archivo.close();
    }

    return -2;    
}


/* --------------ARCHIVO QUE MANEJA LA CANTIDAD DE MOTOS EN EL ESTACIONAMIENTO ------------------- */
int contMotos(bool actualizar, int nCont = 0){
    fstream archivo;
    int cMotos;

    if(!actualizar){ //Si lo que se quiere es obtener el número de vehiculo de tipo moto que hay en el estacionamiento
        archivo.open("contMotos.dat", ios::binary|ios::in);
        if(!archivo){
            cout << "\n\t Archivo contador de camionetas no se abrio correctamente.";
            return -2; //-2 es el indicador de error
        }
        
        if(!archivo.read(reinterpret_cast<char*>(&cMotos), sizeof(int))){
            archivo.close();
            return 0;
        }
        archivo.close();
        return cMotos;

    }else{          /* Si lo que se quiere es actualizar (aumentar/disminuir) el número de vehiculo de tipo moto 
                    que hay en el estacionamiento*/
        archivo.open("contMotos.dat", ios::binary|ios::out|ios::trunc);
        if(!archivo){
            cout << "\n\t Archivo contador de autos no se abrio correctamente.";
            return -2;
        }

        archivo.seekp(0);
        if(!archivo.write(reinterpret_cast<char*>(&nCont), sizeof(int))){
            archivo.close();
            return -1;   // -1 es el indicador de que todo se modifico correctamente 
        }
        archivo.close();
    }

    return -2;    
}

/* --------------ARCHIVO QUE MANEJA LA CANTIDAD DE CAMIONES EN EL ESTACIONAMIENTO ------------------- */
int contCamiones(bool actualizar, int nCont = 0){   
    fstream archivo;
    int cCamiones;

    if(!actualizar){ //Si lo que se quiere es obtener el número de vehiculo de tipo camión que hay en el estacionamiento
        archivo.open("contCamiones.dat", ios::binary|ios::out|ios::in);
        if(!archivo){
            cout << "\n\t Archivo contador de camionetas no se abrio correctamente.";
            return -2; //-2 es el indicador de error
        }
        
        if(!archivo.read(reinterpret_cast<char*>(&cCamiones), sizeof(int))){
            archivo.close();
            return 0;
        }
        archivo.close();
        return cCamiones;
        
    }else{          /* Si lo que se quiere es actualizar (aumentar/disminuir) el número de vehiculo de tipo camión 
                    que hay en el estacionamiento*/
        archivo.open("contCamiones.dat", ios::binary|ios::out|ios::trunc);
        if(!archivo){
            cout << "\n\t Archivo contador de autos no se abrio correctamente.";
            return -2;
        }

        archivo.seekp(0);
        if(!archivo.write(reinterpret_cast<char*>(&nCont), sizeof(int))){
            archivo.close();
            return -1;   // -1 es el indicador de que todo se modifico correctamente 
        }
        archivo.close();
    }

    return -2;    
}

// Función sobrecargada para devolver el contador de cada vehículo apoyandose de la función con el mismo nombre
int contAutos(int)       { return contAutos(false); }
int contCamiones(int)    { return contCamiones(false); }
int contMotos(int)       { return contMotos(false); }

/* --------------------- ARCHIVOS QUE MANEJAN LOS FOLIOS DEL ESTACIONAMIENTO ----------------------- */
int leer_folios(){
    int folio;
    fstream archivo;
    archivo.open("folios.dat", ios::binary|ios::in);
    if(!archivo){
        cout << "\n\t Lo sentimos hubo un fallo en el sistema [FOLIOS].";
    }
    archivo.seekg(0, ios::end);
    size_t size = archivo.tellg();
    if(size >= sizeof(int)){
        archivo.seekg(size - sizeof(int), ios::beg);
        archivo.read(reinterpret_cast<char*>(&folio), sizeof(int));
    }
    archivo.close();
    
    return folio;
}

void actualizar_folios(int folio = -1){
    fstream archivo;
    archivo.open("folios.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
         cout << "\n\t Lo sentimos hubo un fallo en el sistema [FOLIOS].";
    }
    archivo.seekp(0, ios::end);
    archivo.write(reinterpret_cast<char*>(&folio), sizeof(int));
    archivo.close();
}
#endif