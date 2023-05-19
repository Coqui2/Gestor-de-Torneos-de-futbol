#ifndef PARTIDO_H
#define PARTIDO_H
#include<iostream>
using namespace std;
#include "Equipo.h"
#include "Resultado.h"


///Pendientes de desarrollo:
/// leer y grabar en disco





class Partido
{
  private:
    Equipo _local;
    Equipo _visitante;
    int _IdPartido;
    int _IdTorneo;
    Resultado _ResultadoPartido;
    int _Formato;//normal o eliminacion directa
    bool _Jugado;
    int _FechaTorneo;

public:
    Equipo getEquipos(int);
    Partido();
    Partido (int idTorneo, int idEquipo1, int idEquipo2,int tipo, int Fecha);
    Equipo getLocal();
    Equipo getVisitante();
    int getIdPartido();
    int getIdTorneo();
    Resultado getResultadoPartido();
    int getTipo();
    bool getJugado();
    int getFechaTorneo();
    void setEquipos(Equipo equip1,Equipo equip2);
    void setIdPartido(int idPartido);
    void setIdTorneo(int idTorneo);
    void setResultadoPartido(Resultado result);
    void setTipo(int tipo);
    void setJugado(bool jugado);
    void setFechaTorneo(int FechaT);
    void Ganador();
    void cargarResultado();
    int getIdGanador();
    int getIdPerdedor();



    bool modificarRegistro();
    bool leerDeDisco(int posicion);
    bool grabarEnDisco();
    int getCantidadDeRegistros();
    int getProximoIdPartido();          ///Devuelve el siguiente id para poder adicionar un partido a los registros

};

#endif // PARTIDO_H
