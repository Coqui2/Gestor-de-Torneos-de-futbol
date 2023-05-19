#ifndef TORNEO_H
#define TORNEO_H
#include<iostream>
#include <string>
#include <cstring>
using namespace std;
#include "equipo.h"
#include "Eliminatoria.h"

class Torneo
{
    private:
        char _Nombre[50];
        int _ID;
        int _CantidadEquipos;
        int _Formato;
        int _PartidosJugados=0;
        int _totalPartidos;
        bool _eliminacion=0;        ///indica si está en etapa de eliminacion o no
        Eliminatoria _eliminatoria;
        bool _torneoFinalizado=0;
        int _idCampeon;


    public:
        Torneo(){}
        Torneo(string nombre, int cantidad, int formato);
        string getNombre();
        int getID();
        int getCantidadEquipos();
        int getFormato();
        int getPartidosJugados();
        int getTotalPartidos();
        bool getFinalizado();

        void setNombre(string nombre);
        void setID(int id);
        void setCantidadEquipos(int cantidadEquipos);
        void setFormato(int formato);
        void setPartidosJugados(int partidosJugados);
        void goleadores();
        void fairPlay();
        void VallaMenosVencida();
        void crearFixture();
        void condicionFinal();
        int getCantidadDeRegistros();
        void cargarArrayIdEquipos(int* arrayIDEquipos);
        void setArrayEquiposPorPuntos(Equipo* arrayEquipos);
        void inicioEliminatoriaPostGrupos();
        bool grabarEnDisco();
        bool leerDeDisco(int);
        bool modificarRegistro();
        void addPartidoJugado();
        void addPartidoElim(int);
        int getIdEquipoMayorPuntaje();

        ///A DESARROLLAR
        void finTorneo();
};

#endif // TORNEO_H
