#include<iostream>
#include<cstring>
using namespace std;
#include "rlutil.h"
#include "Jugador.h"
#include "FuncionesUtiles.h"

string Jugador::getNombre()
{
    return _Nombre;
}
int Jugador::getEdad()
{
    return _Edad;
}
int Jugador::getIdTorneo()
{
    return _IdTorneo;

}
int Jugador::getIdEquipo()
{
    return _IdEquipo;
}
int Jugador::getNumeroCamiseta()
{

    return _NumeroCamiseta;
}
int Jugador::getGoles()
{

    return _Goles;
}
int Jugador::getAsistencias()
{
    return _Asistencias;
}
int Jugador::getTarjetasRojas()
{
    return _TarjetasRojas;
}
int Jugador::getTarjetasAmarillas()
{
    return _TarjetasAmarillas;

}

int Jugador::getIdJugador(){
    return _idJugador;
}

void Jugador::setNombre(string nombre){
    strcpy(_Nombre,nombre.c_str());
}

void Jugador::setEdad(int edad)
{

    _Edad=edad;

}
void Jugador::setIdTorneo(int idTorneo)
{
    _IdTorneo=idTorneo;
}
void Jugador::setIdEquipo(int idEquipo)
{
    _IdEquipo=idEquipo;
}
void Jugador::setNumeroCamiseta(int numeroCamiseta)
{
    _NumeroCamiseta=numeroCamiseta;

}
void Jugador::setGoles(int goles)
{
    _Goles=goles;

}
void Jugador::setAsistencias(int asistencias)
{

    _Asistencias=asistencias;
}
void Jugador::setTarjetasRojas(int tarjetasRojas)
{

    _TarjetasRojas= tarjetasRojas;

}
void Jugador::setTarjetasAmarillas(int tarjetasAmarillas)
{

    _TarjetasAmarillas=tarjetasAmarillas;

}

void Jugador::addGoles(int cantGoles){
    _Goles+=cantGoles;
}
void Jugador::addAsistencias(int cantAss){
    _Asistencias+=cantAss;
}
void Jugador::addTarjetaRoja(){
    _TarjetasRojas++;
}
void Jugador::addTarjetaAmarilla(){
    _TarjetasRojas++;
}
void Jugador::mostrar(int pos){

rlutil::setBackgroundColor(rlutil::color::BLUE);

    rlutil::locate(1,3);
    cout<<"ID ";
    rlutil::locate(13,3);
    cout<<"NOMBRE";
    rlutil::locate(25,3);
    cout<<"EDAD";
    rlutil::locate(30,3);
    cout<<"ID EQUIPO";
    rlutil::locate(40,3);
    cout<<"N.DE CAMISETA";
    rlutil::locate(55,3);
    cout<<"GOLES";
    rlutil::locate(65,3);
    cout<<"ASISTENCIAS";
    rlutil::locate(80,3);
    cout<<"T. ROJAS";
    rlutil::locate(96,3);
    cout<<"T. AMARILLAS";
 rlutil::setBackgroundColor(rlutil::color::BLACK);

    rlutil::locate(1,pos);
    cout<<_idJugador;
    rlutil::locate(13,pos);
    cout<< _Nombre;
    rlutil::locate(25,pos);
    cout<<_Edad;
    rlutil::locate(30,pos);
    cout<<_IdEquipo;
    rlutil::locate(40,pos);
    cout<<_NumeroCamiseta;
    rlutil::locate(55,pos);
    cout<<_Goles;
    rlutil::locate(65,pos);
    cout<<_Asistencias;
    rlutil::locate(80,pos);
    cout<<_TarjetasRojas;
    rlutil::locate(96,pos);
    cout<<_TarjetasAmarillas;

}

Jugador::Jugador(){

_Goles=0;
_Asistencias=0;
_TarjetasAmarillas=0;
_TarjetasRojas=0;

}

Jugador::Jugador(string nombre, int edad,int nroCamiseta,int idtorneo,int idEquipo){
    FuncionesUtiles func;
    setNombre(nombre);
    setEdad(edad);
    setNumeroCamiseta(nroCamiseta);
    setIdTorneo(idtorneo);
    setIdEquipo(idEquipo);
    _idJugador=func.getProximoIDJugador();
}

bool Jugador::leerDeDisco(int pos){
    FILE* pFile=fopen("jugadores.dat","rb");
    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,sizeof(Jugador)*pos,0);
    bool leyo=fread(this,sizeof(Jugador),1,pFile);
    fclose(pFile);
    return leyo;
}

bool Jugador::modificarRegistro(){
    FILE* pFile=fopen("jugadores.dat","rb+");
    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,(_idJugador-1)*sizeof(Jugador),0);
    bool modifico=fwrite(this,sizeof(Jugador),1,pFile);
    fclose(pFile);
    return modifico;
}

bool Jugador::grabarEnDisco(){
    FILE* pFile=fopen("jugadores.dat","ab");
    if(pFile==nullptr){
        return false;
    }
    bool grabo=fwrite(this,sizeof(Jugador),1,pFile);
    fclose(pFile);
    return grabo;
}

