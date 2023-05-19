#ifndef FUNCIONESUTILES_H
#define FUNCIONESUTILES_H

#include<iostream>

using namespace std;

#include <ctime>
#include <algorithm>
#include "partido.h"
#include "equipo.h"
#include "jugador.h"



class FuncionesUtiles{

    public:
        bool checkeaNroRepetido(int* arr, int nro, int tam);

        ///PARA GRUPOS O ELIMINATORIA SOLO POTENCIAS DE 2
        void sorteadorDePartidos(int* arrayIDEquipos,int cantidad, int tipo, int idTorneo);
        void sorteadorDeGrupos(int* arrayIDEquipos, int cantidadEquipos, int idTorneo);
        ///ABRE Y CIERRA LOS ARCHIVOS PARA ASEGURARSE QUE EXISTEN
        bool chequeoDeArchivos();
        int calcularTotalRondas(int cantidadEquipos);
        void ordenarEquiposDescendente(Equipo* arrayEquipos,int cantidad);
        void getMejorMitadDeEquipos(int* arrayEquipos,Equipo* auxEquipos,int cantidad);
        int getTorneoActivo();
        void setTorneoActivo(int idtorneo);
        void crearTorneoNuevo();
        bool esCantidadValida(int cantidad);
        void crearEquipo();
        void crearJugador(int idEquipo);
        int getProximoIDEquipo();
        int getProximoIDTorneo();
        int getProximoIDJugador();
        int getProximoIDPartido();
        int getCantidadTorneos();
        void listarTodosTorneos();
        bool listarTorneosEnCurso();
        bool listarTorneosFinalizados();
        void listarEquiposDeTorneoActivo();
        bool listarPartidosPendientesDeTorneoActivo();
        bool listarTodosPartidos();
        Jugador buscarIdJugador(int idEquipo, int nroCamiseta);
        void cargarResultado(int);
        void finTorneo(int);
        bool validacionSeleccionPartido(int idPartido);
        bool validacionSeleccionTorneo(int idTorneo);
        void tablaPosiciones();

};

#endif // FUNCIONESUTILES_H

