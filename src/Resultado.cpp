# include<iostream>
# include<cstdlib>
using namespace std;
# include "Resultado.h"
#include "partido.h"
#include "jugador.h"




int Resultado::getIdPartido(){
    return _idPartido;
}

int Resultado::getIdEquipo(){
    return *_idEquipo;
}

int Resultado::getCantGoles(){
    return *_cantGoles;
}

int Resultado::getGolesLocal(){
    return _cantGoles[0];
}

int Resultado::getGolesVisitante(){
    return _cantGoles[1];
}

int Resultado::getCantAmarillas(){
    return *_cantAmarillas;
}

int Resultado::getCantRojas(){
    return *_cantRojas;
}




void Resultado::setIdPartido(int idPartido){
_idPartido = idPartido;
}

void Resultado::setIdEquipo(int local, int visitante){
_idEquipo[0] = local;
_idEquipo[1] = visitante;
}

void Resultado::setCantGoles(int local, int visitante){

_cantGoles[0] = local;
_cantGoles[1] = visitante;
}

void Resultado::setPuntosObtenidos(){
if(_cantGoles[0] > _cantGoles[1]){
    _puntosObtenidos[0] = 3;
    _puntosObtenidos[1] = 0;
}
else if(_cantGoles[0] < _cantGoles[1]){
    _puntosObtenidos[0] = 0;
    _puntosObtenidos[1] = 3;
}

else if (_cantGoles[0] == _cantGoles[1]){
    _puntosObtenidos[0] = 1;
    _puntosObtenidos[1] = 1;
}
}

void Resultado::setCantAmarillas(int local, int visitante){
    _cantAmarillas[0] = local;
    _cantAmarillas[1] = visitante;
}

void Resultado::setCantRojas(int local, int visitante){
    _cantRojas[0] = local;
    _cantRojas[1] = visitante;
}



void Resultado::asignarGoles(int idEquipo,int numeroCamiseta,int cantGoles){
Jugador aux;
aux.setIdEquipo(idEquipo);
aux.setNumeroCamiseta(numeroCamiseta);
aux.addGoles(cantGoles);

}
void Resultado::asignarAsistencias(int idEquipo,int numeroCamiseta,int cantAsistencias){
Jugador aux;
aux.setIdEquipo(idEquipo);
aux.setNumeroCamiseta(numeroCamiseta);
aux.addAsistencias(cantAsistencias);

}
void Resultado::asignarAmarillas(int idJugador){}
void Resultado::asignarRojas(int idJugador){}


int Resultado:: enviaResultado(){// me envia el id del equipo ganador o -1 si hubo empate
if(_puntosObtenidos[0]>_puntosObtenidos[1]){
   return _idEquipo[0];
}
else if(_puntosObtenidos[1]>_puntosObtenidos[0]){
   return _idEquipo[1];
}
else if (_puntosObtenidos[0] == _puntosObtenidos[1]){
    return -1;
}
}

void Resultado::crearResultado(){

         int ID1,ID2;
        cout<<"ID PARTIDO ";
        cin>>_idPartido;
        cout<<"ID EQUIPO LOCAL ";
         cin>>ID1;
          _idEquipo[0]=ID1; ///id en la primera posicion es local, y el almacenado en la segunda posicion es el visitante
        cout<<"ID EQUIPO VISITANTE ";
        cin>>ID2;
        _idEquipo[1]=ID2;

        cout<<"GOLES EQUIPO LOCAL ";
         int goles1,goles2;
         cin>>goles1;
         _cantGoles[0]=goles1;
         cout<<"GOLES EQUIPO VISITANTE ";
         cin>>goles2;
         _cantGoles[1]=goles2;

         cout<<"CANTIDAD AMARILLAS EQUIPO LOCAL ";
         int am1,am2;
         cin>>am1;
         _cantAmarillas[0]=am1;
         cout<<"CANTIDAD AMARILLAS EQUIPO VISITANTE ";
         cin>>am2;
         _cantAmarillas[1]=am2;

         cout<<"CANTIDAD ROJAS EQUIPO LOCAL ";
         int roj1,roj2;
         cin>>roj1;
         _cantRojas[0]=roj1;
        cout<<"CANTIDAD ROJAS EQUIPO VISITANTE ";
         cin>>roj2;
         _cantRojas[1]=roj2;

         if(_cantGoles[0]>0){
              int totalGoles=_cantGoles[0];
         do {cout<<"GOLEADORES Y ASISTENCIAS DEL EQUIPO LOCAL "<<endl;
            cout<<"NUMERO DE CAMISETA GOLEADOR "<<endl;
            int numeroCamiseta,cantGoles;
            cin>>numeroCamiseta;
            cout<<"CANTIDAD DE GOLES QUE HIZO ";
            cin>>cantGoles;
            asignarGoles(_idEquipo[0],numeroCamiseta,cantGoles);
            totalGoles-=cantGoles;
            }while(totalGoles >0);

            int totalAss=_cantGoles[0];
            do {
            cout<<"NUMERO DE CAMISETA DEL ASISTIDOR "<<endl;
            int numeroCamiseta,cantAss;
            cin>>numeroCamiseta;
            cout<<"CANTIDAD DE ASISTENCIAS QUE HIZO ";
            cin>>cantAss;
            asignarAsistencias(_idEquipo[0],numeroCamiseta,cantAss);
            totalAss-=cantAss;
            }while(totalAss >0);


         }

        if(_cantGoles[1]>0){

            int totalGoles=_cantGoles[1];
         do {cout<<"GOLEADORES Y ASISTENCIAS DEL EQUIPO VISITANTE "<<endl;
            cout<<"NUMERO DE CAMISETA GOLEADOR "<<endl;
            int numeroCamiseta,cantGoles;
            cin>>numeroCamiseta;
            cout<<"CANTIDAD DE GOLES QUE HIZO ";
            cin>>cantGoles;
            asignarGoles(_idEquipo[1],numeroCamiseta,cantGoles);
            totalGoles-=cantGoles;
            }while(totalGoles>0);

            int totalAss=_cantGoles[1];
            do {
            cout<<"NUMERO DE CAMISETA DEL ASISTIDOR "<<endl;
            int numeroCamiseta,cantAss;
            cin>>numeroCamiseta;
            cout<<"CANTIDAD DE ASISTENCIAS QUE HIZO ";
            cin>>cantAss;
            asignarAsistencias(_idEquipo[1],numeroCamiseta,cantAss);
            totalAss-=cantAss;
            }while(totalAss >0);
         }
}


