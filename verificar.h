#include <iostream>
#include <fstream>
using namespace std;

bool verificarCascarones(){
    int carro;
    int camioneta;
    int moto;
    fstream val("autos.dat", ios::binary|ios::in);
    if(!val) return false;
    if(!val.read(reinterpret_cast<char*>(&carro), sizeof(int))){
        val.close();
        return false;
    }
    val.close();

    fstream val("camionetas.dat", ios::binary|ios::in);
    if(!val) return false;
    if(!val.read(reinterpret_cast<char*>(&camioneta), sizeof(int))){
        val.close();
        return false;
    }
    val.close();

    fstream val("motos.dat", ios::binary|ios::in);
    if(!val) return false;
    if(!val.read(reinterpret_cast<char*>(&moto), sizeof(int))){
        val.close();
        return false;
    }
    val.close();

    //Verificar que exista carro, camioneta y moto
    if(carro == 1 && camioneta == 1 && moto == 1) return true;
    return false;
}

void cascaronesCreados(){
    fstream val;
    val.open("autos.dat", ios::binary|ios::out);
    int autos = 1;
    val.write(reinterpret_cast<char*>(&autos), sizeof(int));
    val.close();

    val.open("camionetas.dat", ios::binary|ios::out);
    int  camioneta = 1;
    val.write(reinterpret_cast<char*>(&camioneta), sizeof(int));
    val.close();

    val.open("motos.dat", ios::binary|ios::out);
    int moto = 1;
    val.write(reinterpret_cast<char*>(&moto), sizeof(int));
    val.close();
}


/*VERIFICACIONES*/
bool verificarFolio(){
    
}