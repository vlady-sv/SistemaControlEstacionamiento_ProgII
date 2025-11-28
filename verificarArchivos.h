#include <iostream>
#include <fstream>
using namespace std;

/* ------------------- VERIFICAR QUE EL CASCARÓN DE ESTACIONAMIENTO ESTE CREADO ---------------- */
bool verificarCascaron(){
    int band;
    fstream val("espacios.dat", ios::binary|ios::in);
    if(!val) return false;
    if(!val.read(reinterpret_cast<char*>(&band), sizeof(int))){
        val.close();
        return false;
    }
    val.close();

    return true;
}

void cascaronCreado(){
    fstream val;
    val.open("espacios.dat", ios::binary|ios::out);
    int band = 1;
    val.write(reinterpret_cast<char*>(&band), sizeof(int));
    val.close();
}

/*VERIFICACIONES*/
bool verificarFolio(){
    
}