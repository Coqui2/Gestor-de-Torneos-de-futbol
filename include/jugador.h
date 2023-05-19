#ifndef JUGADOR_H
#define JUGADOR_H
#include<iostream>
using namespace std;

class Jugador
{
private:
    int _idJugador;
    char _Nombre[50];
    int _Edad;
    int _IdTorneo;
    int _IdEquipo;
    int _NumeroCamiseta;
    int _Goles;
    int _Asistencias;
    int _TarjetasRojas;
    int _TarjetasAmarillas;
public:
    Jugador();//defecto
    Jugador(string nombre, int edad,int nroCamiseta,int idtorneo,int idEquipo);//omision
    string getNombre();
    int getEdad();
    int getIdTorneo();
    int getIdEquipo();
    int getNumeroCamiseta();
    int getGoles();
    int getAsistencias();
    int getTarjetasRojas();
    int getTarjetasAmarillas();
    int getIdJugador();
    void setNombre(string nombre);
    void setEdad(int edad);
    void setIdTorneo(int idTorneo);
    void setIdEquipo(int idEquipo);
    void setNumeroCamiseta(int numeroCamiseta);
    void setGoles(int goles);
    void setAsistencias(int asistencias);
    void setTarjetasRojas(int tarjetasRojas);
    void setTarjetasAmarillas(int tarjetasAmarillas);

    void addGoles(int cantGoles);
    void addAsistencias(int cantAss);
    void addTarjetaRoja();
    void addTarjetaAmarilla();
    void mostrar(int pos);


    bool leerDeDisco(int);
    bool grabarEnDisco();
    bool modificarRegistro();
};

#endif // JUGADOR_H
