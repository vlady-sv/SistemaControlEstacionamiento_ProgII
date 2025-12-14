/* Archivo que solo se ejecutará una vez, cuando se configure por primera vez el programa,
este, se encarga de crear los archivos contadores de autos, motos, camiones y folios, los
crea con valores iniciales, este archivo solo se deberá ejecutar por la persona encargada de 
instalar el sistema la primera vez */
#ifndef INIARCH_H
#define INIARCH_H
#include <iostream>
#include <fstream>
using namespace std;

//Prototipos
int contAutos(int &);
int contMotos(int &);
int contCamiones(int &);
int folios(int &);

int main(){
    int total = 0, correctos = 0;
    correctos += contAutos(total);
    correctos += contMotos(total);
    correctos += contCamiones(total);
    correctos += folios(total);

    cout << "\n\t" << correctos << " de " << total << " archivos creados correctamente.";
    return 0;
}

int contAutos(int &total){ //Archivo contador de autos
    fstream archivo;
    ++total;

    archivo.open("contAutos.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de Autos no se abrio correctamente.";
        return 0;
    }

    int contInicial = 0;
    archivo.seekp(ios::beg);
    archivo.write(reinterpret_cast<char*>(&contInicial), sizeof(int));
    archivo.close();

    return 1;
}

int contMotos(int &total){ //Archivo contador de motos
    fstream archivo;
    ++total;

    archivo.open("contMotos.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de Motos no se abrio correctamente.";
        return 0;
    }

    int contInicial = 0;
    archivo.seekp(ios::beg);
    archivo.write(reinterpret_cast<char*>(&contInicial), sizeof(int));
    archivo.close();

    return 1;
}

int contCamiones(int &total){ //Archivo contador de camiones
    fstream archivo; 
    ++total;

    archivo.open("contCamiones.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de Camiones no se abrio correctamente.";
        return 0;
    }

    int contInicial = 0;
    archivo.seekp(ios::beg);
    archivo.write(reinterpret_cast<char*>(&contInicial), sizeof(int));
    archivo.close();

    return 1;
}

int folios(int &total){ //Archivo para guardar los folios que se van dando
    fstream archivo;
    ++total;

    archivo.open("folios.dat", ios::binary|ios::out);
    if(!archivo){
        cout << "\n\t Archivo contador de folios no se abrio correctamente.";
        return 0;
    }

    int folioInicial = 999; /* Este folio jamás se mostrará, solo es una referencia de donde empezar,
    los folios se empezaran a dar a partir del 1000 */
    archivo.seekp(ios::beg);
    archivo.write(reinterpret_cast<char*>(&folioInicial), sizeof(int));
    archivo.close();

    return 1;
}
#endif