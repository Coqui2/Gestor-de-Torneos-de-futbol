#include<iostream>
#include <string>
#include <cstring>
using namespace std;
#include "FuncionesUtiles.h"
#include "Eliminatoria.h"
#include "torneo.h"
#include "Menues.h"

string Torneo ::getNombre(){
    return _Nombre;

}
int Torneo ::getID(){

    return _ID;
}
int Torneo ::getCantidadEquipos(){
    return _CantidadEquipos;
}
int Torneo ::getFormato()
{

    return _Formato;
}
int Torneo ::getPartidosJugados()
{
    return _PartidosJugados;

}

bool Torneo::getFinalizado(){
    return _torneoFinalizado;
}

void Torneo ::setNombre(string nombre){

strcpy(_Nombre,nombre.c_str());

}
void Torneo ::setID(int id){
_ID=id;

}
void Torneo ::setCantidadEquipos(int cantidadEquipos){
_CantidadEquipos=cantidadEquipos;
}
void Torneo ::setFormato(int formato){
_Formato=formato;

}
void Torneo ::setPartidosJugados(int partidosJugados){

_PartidosJugados=partidosJugados;
}

int Torneo::getTotalPartidos(){
    return _totalPartidos;
}

///CONSTRUCTOR
Torneo::Torneo(string nombre, int cantidad, int formato){
    FuncionesUtiles func;
    strcpy(_Nombre,nombre.c_str());
    _ID=func.getProximoIDTorneo();
    _CantidadEquipos=cantidad;
    _Formato=formato;
    ///LA CANTIDAD DE PARTIDOS A JUGAR SE CALCULA EN FUNCION DEL FORMATO
    if(_Formato==1){
        _totalPartidos=((float)_CantidadEquipos/2)*(_CantidadEquipos-1);
    }
    else if(_Formato==2){
        _totalPartidos=6*_CantidadEquipos/4;
    }
    if(_Formato==3){
        _totalPartidos=_CantidadEquipos-1;
    }
}

///MANEJO DE ARCHIVOS
bool Torneo::leerDeDisco(int pos){
    FILE* pFile=fopen("torneos.dat","rb");
    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,sizeof(Torneo)*pos,0);
    bool leyo=fread(this,sizeof(Torneo),1,pFile);
    fclose(pFile);
    return leyo;
}

bool Torneo::modificarRegistro(){
    FILE* pFile=fopen("torneos.dat","rb+");
    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,(getID()-1)*sizeof(Torneo),0);
    bool modifico=fwrite(this,sizeof(Torneo),1,pFile);
    fclose(pFile);
    return modifico;
}

bool Torneo::grabarEnDisco(){
    FILE* pFile=fopen("torneos.dat","ab");
    if(pFile==nullptr){
        return false;
    }
    bool grabo=fwrite(this,sizeof(Torneo),1,pFile);
    fclose(pFile);
    return grabo;
}

int Torneo::getCantidadDeRegistros(){
    FILE* pFile=fopen("torneos.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int cantidadDeRegistros=ftell(pFile)/sizeof(Torneo);
    fclose(pFile);
    return cantidadDeRegistros;
}

void Torneo::goleadores(){}
void Torneo::fairPlay(){}
void Torneo::VallaMenosVencida(){}


///CREACION DE FIXTURE
void Torneo::crearFixture(){
    FuncionesUtiles fu;
    switch(_Formato){
        case 1:         ///FORMATO LIGA
            {


            int* arrayIDEquiposLiga = new int[_CantidadEquipos];
            if(arrayIDEquiposLiga==nullptr){
                cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
                exit(1);
            }
            ///SE CARGA ARRAY CON LOS EQUIPOS DEL TORNEO
            cargarArrayIdEquipos(arrayIDEquiposLiga);
            ///SE SORTEAN LOS PARTIDOS EN FUNCION DEL FORMATO
            fu.sorteadorDePartidos(arrayIDEquiposLiga,_CantidadEquipos,_Formato,_ID);
            delete [] arrayIDEquiposLiga;
            break;
            }
        case 2: ///FORMATO COPA
            {

            int* arrayIDEquiposGrupos = new int[_CantidadEquipos];
            if(arrayIDEquiposGrupos==nullptr){
                cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
                exit(1);
            }

            ///SE CARGA ARRAY CON LOS EQUIPOS DEL TORNEO
            cargarArrayIdEquipos(arrayIDEquiposGrupos);
            ///SE SORTEAN LOS GRUPOS
            ///DENTRO DEL SORTEO DE GRUPOS SE SORTEAN TAMBIÉN LOS PARTIDOS
            fu.sorteadorDeGrupos(arrayIDEquiposGrupos,_CantidadEquipos,_ID);
            delete [] arrayIDEquiposGrupos;
            break;
            }
        case 3:   ///ELIMINATORIA

            int* arrayIDEquipos = new int[_CantidadEquipos];
            if(arrayIDEquipos==nullptr){
                cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
                exit(1);
            }
            ///SE CARGA EL ARRAY CON LOS EQUIPOS DEL TORNEO
            cargarArrayIdEquipos(arrayIDEquipos);
            ///SE CREA EL OBJETO ELIMINATORIA CON LOS DATOS
            Eliminatoria elim(_ID,_CantidadEquipos,arrayIDEquipos);
            ///SE GUARDA EN EL MIEMBRO DEL TONREO
            _eliminatoria=elim;
            ///SE CREA LA RONDA
            _eliminatoria.armarRonda();
            ///SE MODIFICA EL REGISTRO DEL TORNEO
            modificarRegistro();
            delete [] arrayIDEquipos;
            break;
    }
}

///CARGA LOS ID DE LOS EQUIPOS DEL TORNEO EN UN ARRAY DADO
void Torneo::cargarArrayIdEquipos(int* arrayIDEquipos){
    Equipo equipo;
    int posEquipo=0, posArray=0;
    while(equipo.leerDeDisco(posEquipo++)){
        if(equipo.getIdTorneo()==_ID){
            arrayIDEquipos[posArray]=equipo.getIdEquipo();
            posArray++;
        }
    }
}

///LUEGO DE LA CARGA DE UN RESULTADO DE PARTIDO
///CHEQUEA EL ESTADO DEL TORNEO Y SI LLEGÓ A SU FIN
void Torneo::condicionFinal(){
    if(_Formato==1){ ///LIGA - SI SE CUMPLE TEMRINA EL TORNEO
        if(_PartidosJugados==_totalPartidos){
            finTorneo();
        }
    }
    if(_Formato==2){///COPA - SI SE CUMPLE UNA PRIMERA CONDICION TERMINA FASE DE GRUPOS
                    ///Y COMINEZA LA ELIMINATORIA POST-GRUPOS
        if(_eliminacion==0){
            if(_PartidosJugados==_totalPartidos){
                inicioEliminatoriaPostGrupos();
            }
        }
        else{
            if(_eliminatoria.finalRonda()){
                if(_eliminatoria.finalEliminatoria()){
                    finTorneo();
                }
                else{
                    _eliminatoria.armarRonda();
                }
            }
        }
    }
    if(_Formato==3){ ///ELIMINATORIA - SI SE CUMPLE TEMRINA EL TORNEO
        if(_eliminatoria.finalRonda()){
                if(_eliminatoria.finalEliminatoria()){
                    finTorneo();
                }
                else{
                    _eliminatoria.armarRonda();
                }
            }
    }
}


///TOMA TODOS LOS EQUIPOS DEL TORNEO Y CARGA UN ARRAY
///DEVUELVE LOS EQUIPOS ORDENADOS POR PUNTOS
void Torneo::setArrayEquiposPorPuntos(Equipo* arrayEquipos){
    FuncionesUtiles fu;
    int i=0;
    int posArchivo=0;
    Equipo aux;
    while(aux.leerDeDisco(posArchivo++)){
        if(aux.getIdTorneo()==_ID){
            arrayEquipos[i++]=aux;
        }
    }
    fu.ordenarEquiposDescendente(arrayEquipos,_CantidadEquipos);
}


///DA INICIO A LA ELIMINATORIA UNA VEZ TERMIANDA LA FASE DE GRUPOS EN COPA
void Torneo::inicioEliminatoriaPostGrupos(){
    FuncionesUtiles fu;
    ///MARCA EN TORNEO QUE YA ESTA EN ELIMINATORIA
    _eliminacion=1;
    int cantidad=4;
    ///SI SON 4 EQUIPOS EN EL TORNEO NO SE DESCARTAN EQUIPOS
    if(_CantidadEquipos!=4){
        cantidad=_CantidadEquipos/2;
    }
    _totalPartidos+=cantidad-1;
    int* arrayIDEquipos=new int[cantidad];
    if(arrayIDEquipos==nullptr){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        exit(1);
    }
    Equipo* auxEquipos;
    auxEquipos=new Equipo[_CantidadEquipos];
    if(auxEquipos==nullptr){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        exit(1);
    }
    ///DEVUELVE EL ARRAY CON LOS EQUIPOS ORDENADOS POR PUNTOS
    setArrayEquiposPorPuntos(auxEquipos);
    ///SE QUEDA CON LA PRIMERA MITAD DEL ARRAY(LOS QUE PASAN DE RONDA - SOLO LOS IDS)
    fu.getMejorMitadDeEquipos(arrayIDEquipos,auxEquipos,cantidad);
    ///CREA LA ELIMINATORIA
    Eliminatoria elim(_ID,cantidad,arrayIDEquipos);
    ///LA GUARDA EN EL TORNEO
    _eliminatoria=elim;
    ///CREA LOS PARTIDOS
    _eliminatoria.armarRonda();
    ///GUARDA EL TORNEO MODIFICADO
    modificarRegistro();
    delete [] auxEquipos;
    delete [] arrayIDEquipos;
}

///REVISA LOS EQUIPOS DEL TORNEO Y SE QUEDA CON EL PRIMERO CON EL PUNTAJE MÁS ALTO
int Torneo::getIdEquipoMayorPuntaje(){
    Equipo equipo;
    int pos=0,maxPuntos=0,idMax;
    while(equipo.leerDeDisco(pos++)>0){
        if(equipo.getIdTorneo()==_ID&&equipo.getPuntosEquipo()>maxPuntos){
            maxPuntos=equipo.getPuntosEquipo();
            idMax=equipo.getIdEquipo();
        }
    }
    return idMax;
}

///SE EJECUTA AL TERMINAR EL TORNEO
void Torneo::finTorneo(){
    _torneoFinalizado=1;
    FuncionesUtiles func;
    if(_Formato==1){
        _idCampeon=getIdEquipoMayorPuntaje();
    }
    else{
        _idCampeon=_eliminatoria.getCampeon();
    }
    modificarRegistro();
    func.finTorneo(_idCampeon);
    menuFinTorneo();
}

///SUMA PARTIDO JUGADO AL OBJETO
void Torneo::addPartidoJugado(){
    _PartidosJugados++;

}

///SUMA PARTIDO JUGADO A LA ELIMINATORIA
void Torneo::addPartidoElim(int idPerdedor){
    _eliminatoria.addPartidoJugado();
    _eliminatoria.borrarPerdedor(idPerdedor);
}
