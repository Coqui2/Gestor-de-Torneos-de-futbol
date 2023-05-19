#include<iostream>
#include<cstring>
using namespace std;
#include "equipo.h"
#include "rlutil.h"
#include "FuncionesUtiles.h"

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);//limpieza de buffer
}

string Equipo::getNombre()
{
    return _Nombre;
}
int Equipo::getIdTorneo()
{
    return _IDTorneo;
}
int Equipo::getIdEquipo()
{
    return _IDEquipo;
}
int Equipo::getPartidosJugados()
{
    return _PartidosJugados;

}
int Equipo::getPartidosGanados()
{
    return _PartidosGanados;
}
int Equipo::getPartidosEmpatados()
{
    return _PartidosEmpatados;

}
int Equipo::getPartidosPerdidos()
{
    return _PartidosPerdidos;
}
int Equipo::getPuntosEquipo()
{
    return _PuntosEquipo;
}
int Equipo::getGolesEquipoGenerales()
{
    return _GolesEquipoGenerales;

}
int Equipo::getGolesPartido(){
return _GolesPartido;
}

void Equipo::setNombre(string nombre) {
    strcpy(_Nombre,nombre.c_str());
}
void Equipo::setIdTorneo(int idTorneo ) {
_IDTorneo=idTorneo;
}
void Equipo::setIdEquipo(int idEquipo) {
_IDEquipo=idEquipo;
}
void Equipo::setPartidosJugados(int pj) {
_PartidosJugados=pj;
}
void Equipo::setPartidosGanados(int pg) {
_PartidosGanados=pg;
}
void Equipo::setPartidosEmpatados(int pe) {
_PartidosEmpatados=pe;
}
void Equipo::setPartidosPerdidos(int pp) {
_PartidosPerdidos=pp;
}
void Equipo::setPuntosEquipo(int pEquipo) {
_PuntosEquipo=pEquipo;
}
void Equipo::setGolesEquipoGenerales(int golesEquipo) {
_GolesEquipoGenerales+=golesEquipo;
}
void Equipo::setGolesPartido(int golesPartido){
_GolesPartido+=golesPartido;

}

void Equipo::addPartidoJugado(){
    _PartidosJugados++;
}

void Equipo::addPartidoGanado(){
    _PartidosGanados++;
}

void Equipo::addPartidoPerdido(){
    _PartidosPerdidos++;
}

void Equipo::addPartidoEmpatado(){
    _PartidosEmpatados++;
}

void Equipo::addPuntos(int puntos){
    _PuntosEquipo+=puntos;
}

void Equipo::addVictoria(){
    addPartidoJugado();
    addPartidoGanado();
    addPuntos(3);
}

void Equipo::addDerrota(){
    addPartidoJugado();
    addPartidoPerdido();
}

void Equipo::addEmpate(){
    addPartidoJugado();
    addPartidoEmpatado();
    addPuntos(1);
}

void Equipo::addGoles(int goles){
    _GolesEquipoGenerales+=goles;
}



void Equipo::cargar(){
    cout << "Nombre: " ;cargarCadena(_Nombre,50);
    cout << "ID torneo: "; cin >> _IDTorneo;
    cout << "ID equipo: "; cin >> _IDEquipo;
    cout << "Partidos jugados: "; cin >> _PartidosJugados;
    cout << "Partidos Ganados: "; cin >> _PartidosGanados;
    cout << "Partidos empataos: "; cin >> _PartidosEmpatados;
    cout << "Partidos perdidos: "; cin >> _PartidosPerdidos;
    cout << "Puntos Equipo: "; cin >> _PuntosEquipo;
    cout << "Goles equipo generales: "; cin >> _GolesEquipoGenerales;
    cout << "Goles partido: "; cin >> _GolesPartido;
}

void Equipo::mostrar(){
    cout << _Nombre << endl;
    cout << _IDTorneo << endl;
    cout << _IDEquipo << endl;
    cout << _PartidosJugados << endl;
    cout << _PartidosGanados << endl;
    cout << _PartidosEmpatados << endl;
    cout << _PartidosPerdidos << endl;
    cout << _PuntosEquipo << endl;
    cout << _GolesEquipoGenerales << endl;
    cout << _GolesPartido << endl;
}

void Equipo::listarJugadoresEquipo(int idEquipo) {
Jugador aux;
int pos=0;
int pos1=7;
bool existe=false;
while(aux.leerDeDisco(pos++)){
if (idEquipo==aux.getIdEquipo()){
aux.mostrar(pos1++);
existe=true;
cout <<endl<<endl;

}
}
if(existe==false){cout<<"EL ID DE EQUIPO ES INVALIDO"<<endl;}
}

void Equipo::listarJugadoresTodosEquipo() {
Jugador aux;
int pos=0;
int pos1=7;


while(aux.leerDeDisco(pos++)){

aux.mostrar(pos1++);
cout <<endl<<endl;

}

}

void Equipo::listaHistoricaEquipos(){
int pos=0,pos1=5;
Equipo aux;
rlutil::setBackgroundColor(rlutil::color::BLUE);
 rlutil::locate(10,1);
cout<<"LISTADO HISTORICO DE EQUIPOS";
 rlutil::locate(15,3);
    cout<<"ID ";
    rlutil::locate(30,3);
    cout<<"NOMBRE";
    rlutil::setBackgroundColor(rlutil::color::BLACK);
while(aux.leerDeDisco(pos++)){
   rlutil::locate(15,pos1);
    cout<<aux.getIdEquipo();
    rlutil::locate(30,pos1);
    cout<<aux.getNombre();
    pos1++;
}
cout<<endl;
}

void Equipo::maximoGoleadorEquipo() {
Equipo equipo;
Jugador jugador;
int pos=0;
int POS2=5;
                rlutil::setBackgroundColor(rlutil::color::BLUE);
                rlutil::locate(10,1);
                cout<<"MAXIMO GOLEADOR POR EQUIPO ";
    rlutil::locate(15,3);
    cout<<"EQUIPO ";
    rlutil::locate(30,3);
    cout<<"NOMBRE JUGADOR";
    rlutil::locate(45,3);
    cout<<"GOLES";
    rlutil::setBackgroundColor(rlutil::color::BLACK);
while(equipo.leerDeDisco(pos)){
   int pos1=0,maximo=0;
           Jugador aux;
    while(jugador.leerDeDisco(pos1)){
        if(equipo.getIdEquipo()==jugador.getIdEquipo()){
            if(jugador.getGoles()>maximo){
           aux=jugador;
           }

        }
        pos1++;
    }
    rlutil::locate(15,POS2);
    cout<<equipo.getNombre();
    rlutil::locate(30,POS2);
    cout<<aux.getNombre();
    rlutil::locate(45,POS2);
    cout<<aux.getGoles();
    POS2++;
    pos++;
}
}
bool Equipo::leerDeDisco(int pos){
        FILE *p;
        p=fopen("equipos.dat", "rb");
        if(p==NULL) return false;
        fseek(p, sizeof(Equipo)*pos,0);
        bool leyo=fread(this, sizeof(Equipo),1, p);
        fclose(p);
        return leyo;
    }

bool Equipo::grabarEnDisco(){
        FILE *p;
        p=fopen("equipos.dat", "ab");
        if(p==NULL) return false;
        bool grabo=fwrite(this, sizeof(Equipo),1, p);
        fclose(p);
        return grabo;
    }

bool Equipo::modificarRegistro(){
    FILE *p;
    p=fopen("equipos.dat", "rb+");
    if(p==NULL) return false;
    fseek(p, sizeof(Equipo)*(_IDEquipo-1),0);
    bool modifico=fwrite(this, sizeof(Equipo),1, p);
    fclose(p);
    return modifico;
}

Equipo::Equipo(){}

Equipo::Equipo(string nombre, int idTorneo){
    FuncionesUtiles func;
    _IDEquipo=func.getProximoIDEquipo();
    strcpy(_Nombre,nombre.c_str());
    _IDTorneo=idTorneo;
    _PartidosJugados=0;
    _PartidosGanados=0;
    _PartidosEmpatados=0;
    _PartidosPerdidos=0;
    _PuntosEquipo=0;
    _GolesEquipoGenerales=0;
    _GolesPartido=0;
}
