//CLASE - TICKET DE SALIDA
#ifndef TICKETSALIDA_H
#define TICKETSALIDA_H
#include "TicketEntrada.h"
#include <iomanip>
using namespace std;

#define TAUTOHORA 18
#define TMOTOHORA 14
#define TCAMIONHORA 25 
#define TAUTODIA 180 //Por dia se descuentan el equivalente a dos horas
#define TMOTODIA 140
#define TCAMIONDIA 250
#define TAUTOMES 6156 //Por mes se descuenta el equivalente a 1 1/2 días de servicio (18 horas)
#define TMOTOMES 4816
#define TCAMIONMES 8550

class TicketSalida{
    private:
        Espacio e;
        char horaSalida[15];
        char diaSalida[15];
        double totalPagar;
        int duracion;
        friend void guardarTicketS(TicketSalida&);

    public:
        TicketSalida(Espacio e = Espacio(), const char horaSalida[15] = ".", const char diaSalida[15] = ".", double totalPagar = 0.0, int duracion  = 0){
            this->e = e;
            strcpy(this->horaSalida, horaSalida);
            strcpy(this->diaSalida, diaSalida);
            this->totalPagar = totalPagar;
            this->duracion = duracion;
        }

        //Setters
        void set_Espacio(Espacio e){
            this->e = e;
        }

        void set_horaSalida(char horaSalida[15]){
            strcpy(this->horaSalida, horaSalida);
        }

        void set_diaSalida(char diaSalida[15]){
            strcpy(this->diaSalida, diaSalida);
        }

        void set_totalPagar(double totalPagar){
            this->totalPagar = totalPagar;
        }

        void set_duracion(int duracion){
            this->duracion = duracion;
        }

        //Getters
        Espacio get_Espacio() const{
            return e;
        }

        const char* get_horaSalida() const{
            return horaSalida;
        }

        const char* get_diaSalida() const{
            return diaSalida;
        }

        double get_totalPagar(){
            return totalPagar;
        }

        int get_duracion() const{
            return duracion;
        }

        //Función para establecer dia y hora de salida
        void establecerSalida(){
            tiempo ahora = reloj::now();
            strcpy(horaSalida, tiempoToStringHora(ahora).c_str());
            strcpy(diaSalida, tiempoToStringFecha(ahora).c_str());
        }

        // Función para calcular el tiempo que el cliente estuvo en el estacionamiento
        void calcularDuracion(){
            if(strcmp(e.get_tarifa(), "horas") == 0){
                duracion  = horasCobrar(e.get_horaLlegada(), horaSalida);
            }else if(strcmp(e.get_tarifa(), "dia") == 0){
                duracion = diasCobrar(e.get_horaLlegada(), horaSalida);
            }else{
                duracion = 1; //En el caso de tarifa por mes, solo esta permitido que el auto se quede un mes, no mas
            }
        }

        void calcularPago(){
            
            if(e.get_descuento() != 0){
                /* CON CONVENIO DE DESCUENTO*/
                if(strcmp(e.get_tarifa(),"horas") == 0){
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTOHORA; //Tarifa de hora para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTOHORA; //Tarifa de hora para moto
                    }else{
                        totalPagar  = duracion*TCAMIONHORA; //Tarifa de hora para camion
                    }
                    totalPagar = totalPagar - (totalPagar*e.get_descuento());
                }else if(strcmp(e.get_tarifa(), "dia") == 0){
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTODIA; //Tarifa de dia para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTODIA; //Tarifa de dia para moto
                    }else{
                        totalPagar  = duracion*TCAMIONDIA; //Tarifa de dia para camion
                    }
                    totalPagar = totalPagar - (totalPagar*e.get_descuento());
                }else{
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTOMES; //Tarifa de mes para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTOMES; //Tarifa de mes para moto
                    }else{
                        totalPagar  = duracion*TCAMIONMES; //Tarifa de mes para camion
                    }
                    totalPagar = totalPagar - (totalPagar*e.get_descuento());
                }
            }else{
                /* SIN CONVENIO DE DESCUENTO*/
                if(strcmp(e.get_tarifa(), "horas") == 0){
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTOHORA; //Tarifa de hora para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTOHORA; //Tarifa de hora para moto
                    }else{
                        totalPagar  = duracion*TCAMIONHORA; //Tarifa de hora para camion
                    }
                }else if(strcmp(e.get_tarifa(), "dia") == 0){
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTODIA; //Tarifa de dia para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTODIA; //Tarifa de dia para moto
                    }else{
                        totalPagar  = duracion*TCAMIONDIA; //Tarifa de dia para camion
                    }
                }else{
                    if(strcmp(e.get_tipoVehiculo(), "Auto") == 0){
                        totalPagar  = duracion*TAUTOMES; //Tarifa de mes para auto
                    }else if(strcmp(e.get_tipoVehiculo(), "Moto") == 0){
                        totalPagar  = duracion*TMOTOMES; //Tarifa de mes para moto
                    }else{
                        totalPagar  = duracion*TCAMIONMES; //Tarifa de mes para camion
                    }
                }
            }
        }

        void imprimirTicket() const{
            //validacion en caso de que se quiera imprimir un ticket sin haber registro
            if (e.get_numEspacio() == 0) {
                cout << "[ERROR] Ticket sin vehículo asignado." << endl;
                cout << "-------------------------------------" << endl;
                return;
            }

            cout << "\n\t\t\t ***** PLAZA PARKING *****\n";
            cout << "\n\t\t\t---- Ticket de Salida ----" << endl; 
            e.mostrarEspacio(false); 
            cout << "\n\t Hora de salida: " << horaSalida;
            cout << u8"\n\t Día de salida: " << diaSalida;
            cout << u8"\n\t Duración: " << duracion;
            if(strcmp(e.get_tarifa(), "pension") == 0){
                if(duracion == 0 || duracion > 1) cout << " meses";
                else cout << " mes";
            }else if(strcmp(e.get_tarifa(), "horas") == 0){
                if(duracion == 0 || duracion > 1) cout << " horas";
                else cout << " hora";
            }else if(strcmp(e.get_tarifa(), "dia") == 0){
                if(duracion == 0 || duracion > 1) cout << u8" días";
                else cout << u8" día";
            } 
            cout << "\n\t Total a pagar: $" << totalPagar << endl;
            cout << "-------------------------------------" << endl;
        }
};

void guardarTicketS(TicketSalida& obj){ //Crear lógica para guardar el ticket con funcion amiga

    fs::path carpeta = "Tickets_Salida"; //Carpeta donde se estaran guardando todos los tickets de salida
    if(!fs::exists(carpeta)){
        fs::create_directories(carpeta);  //Si aun no existe se crea
    }
    string nomTicket;
    nomTicket = "Ticket_" + to_string(obj.e.get_folio());
    nomTicket = nomTicket + "_" + obj.get_diaSalida();
    nomTicket = nomTicket + ".dat"; //Construimos el nombre completo del archivo

    fs::path archivo = carpeta/nomTicket; //La ruta + el nombre

    fstream ticket;
    ticket.open(archivo, ios::binary|ios::out);
    if(!ticket.is_open()){
        cout << u8"\n\t El ticket no se abrio correctamente [Error en crear ticket salida]";
        return;
    }

    ticket.write(reinterpret_cast<char*>(&obj.e), sizeof(Espacio));
    ticket.write(obj.horaSalida, sizeof(obj.horaSalida));
    ticket.write(obj.diaSalida, sizeof(obj.diaSalida));
    ticket.write(reinterpret_cast<char*>(&obj.totalPagar), sizeof(obj.totalPagar));
    ticket.write(reinterpret_cast<char*>(&obj.duracion), sizeof(obj.duracion));
    ticket.close();
}

#endif
