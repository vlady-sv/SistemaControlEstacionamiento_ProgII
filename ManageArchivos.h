/* DOCUMENTO PARA MANEJAR LOS ARCHIVOS DE VERIFICACIÓN Y ALMACENAMIENTO DE DATOS DE DE IDENTIFICACIÓN
(Contadores, Lógicas auxiliares para encontrar otros archivos, creación de cascarón, etc...)*/
#include <iostream>
using namespace std;

int CrearArchivos(){
    Convenio* c = new Convenio("", 0.0);
    fstream archivo;

    //Archivo para controlar espacios disponibles para autos
    archivo.open("autos.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    Vehiculo* v = new Auto();
    Espacio blanco(0, v, c, "");
    for(int i=0; i<500; i++){
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Espacio));
    }
    archivo.close();


    //Archivo para controlar espacios disponibles para camionetas
    archivo.open("camionetas.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    v = new Camioneta();
    Espacio blanco(0, v, c, "");
    for(int i=0; i<500; i++){
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Espacio));
    }
    archivo.close();

    //Archivo para controlar espacios disponibles para motos
    archivo.open("motos.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t No se pudo abrir el archivo.";
        return -1;
    }
    v = new Moto();
    Espacio blanco(0, v, c, "");
    for(int i=0; i<500; i++){
        archivo.write(reinterpret_cast<char*>(&blanco), sizeof(Espacio));
    }
    archivo.close();

    return 1; //Si todo fue correcto retornamos 1 como indicador
}

 /* --- CONTADORES DE CANTIDAD DE VEHICULOS QUE HAY EN EL ESTACIONAMIENTO POR CADA TIPO */

 //Contador Autos
int contAutos(){
    fstream archivo;
    int cAutos;
    
    archivo.open("contAutos.dat", ios::binary|ios::in);
    if(!archivo){
        cout << "\n\t Archivo contador de autos no se abrio correctamente.";
        return -1;
    }
    
    if(!archivo.read(reinterpret_cast<char*>(&cAutos), sizeof(int))){
        archivo.close();
        return 0;
    }
    archivo.close();

    return cAutos;
}

//Contador Camionetas
int contCamionetas(){   
    fstream archivo;
    int cCamionetas;

    archivo.open("contCamionetas.dat", ios::binary|ios::in);
    if(!archivo){
        cout << "\n\t Archivo contador de camionetas no se abrio correctamente.";
        return -1;
    }
    
    if(!archivo.read(reinterpret_cast<char*>(&cCamionetas), sizeof(int))){
        archivo.close();
        return 0;
    }
    archivo.close();

    return cCamionetas;
}

//Contador Motos
int contMotos(){
    fstream archivo;
    int cMotos;

    archivo.open("contMotos.dat", ios::binary|ios::in);
    if(!archivo){
        cout << "\n\t Archivo contador de motos no se abrio correctamente.";
        return -1;
    }

    if(!archivo.read(reinterpret_cast<char*>(&cMotos), sizeof(int))){
        archivo.close();
        return 0;
    }
    archivo.close();

    return cMotos;
}

/* ACTUALIZAR LA CANTIDAD DE VEHICULOS EN EL ESTACIONAMIENTO POR TIPO */

//Actualizacion de autos
bool actualizarAutos(int cAutos){
    fstream archivo;

    archivo.open("contAutos.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de autos no se abrio correctamente.";
        return false;
    }

    archivo.seekp(0);
    if(!archivo.write(reinterpret_cast<char*>(&cAutos), sizeof(int))){
        archivo.close();
        return false;
    }
    archivo.close();

    return true;
}

//Actualizacion de camionetas
bool actualizarCamionetas(int cCamionetas){
    fstream archivo;

    archivo.open("contAutos.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de autos no se abrio correctamente.";
        return false;
    }

    archivo.seekp(0);
    if(!archivo.write(reinterpret_cast<char*>(&cCamionetas), sizeof(int))){
        archivo.close();
        return false;
    }
    archivo.close();

    return true;
}

//Actualizacion de motos
bool actualizarMotos(int cMotos){
    fstream archivo;

    archivo.open("contAutos.dat", ios::binary|ios::in|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de autos no se abrio correctamente.";
        return false;
    }

    archivo.seekp(0);
    if(!archivo.write(reinterpret_cast<char*>(&cMotos), sizeof(int))){
        archivo.close();
        return false;
    }
    archivo.close();

    return true;
}