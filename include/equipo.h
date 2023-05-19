#ifndef EQUIPO_H
#define EQUIPO_H
#include<iostream>
#include <string>
using namespace std;


class Equipo
{
private :
    char _Nombre[50];
    int _IDTorneo;
    int _IDEquipo;
    int _PartidosJugados;
    int _PartidosGanados;
    int _PartidosEmpatados;
    int _PartidosPerdidos;
    int _PuntosEquipo;
    int _GolesEquipoGenerales;
    int _GolesPartido;

public:
    Equipo();
    Equipo(string nombre,int idTorneo);
    string getNombre();
    int getIdTorneo();
    int getIdEquipo();
    int getPartidosJugados();
    int getPartidosGanados();
    int getPartidosEmpatados();
    int getPartidosPerdidos();
    int getPuntosEquipo();
    int getGolesEquipoGenerales();
    int getGolesPartido();

    void setNombre(string nombre);
    void setIdTorneo(int idTorneo );
    void setIdEquipo(int idEquipo);
    void setPartidosJugados(int pj);
    void setPartidosGanados(int pg);
    void setPartidosEmpatados(int pe);
    void setPartidosPerdidos(int pp);
    void setPuntosEquipo(int pEquipo);
    void setGolesEquipoGenerales(int golesEquipo);
    void setGolesPartido(int golesPartido);
    void listarJugadoresEquipo(int idEquipo);
    void listarJugadoresTodosEquipo();
    void listaHistoricaEquipos();
    void maximoGoleadorEquipo();


    void addPartidoJugado();
    void addPartidoGanado();
    void addPartidoPerdido();
    void addPartidoEmpatado();
    void addPuntos(int puntos);
    void addVictoria();
    void addDerrota();
    void addEmpate();
    void addGoles(int goles);


    void cargar();
    void mostrar();

    bool leerDeDisco(int pos);
    bool grabarEnDisco();
    bool modificarRegistro();
};


#endif // EQUIPO_H
