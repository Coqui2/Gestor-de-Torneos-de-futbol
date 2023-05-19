#include<iostream>
using namespace std;
#include "Partido.h"
#include "Equipo.h"
#include "Resultado.h"
#include "FuncionesUtiles.h"



Partido::Partido(){}

Partido::Partido (int idTorneo, int idEquipo1, int idEquipo2,int tipo, int fecha){
    FuncionesUtiles func;
    _IdPartido=func.getProximoIDPartido();
    _local.leerDeDisco(idEquipo1-1);
    _visitante.leerDeDisco(idEquipo2-1);
    _IdTorneo=idTorneo;
    _Formato=tipo;
    _FechaTorneo=fecha;
    _Jugado=0;


}

Equipo Partido::getLocal(){
    return _local;
}

Equipo Partido::getVisitante(){
    return _visitante;
}

int Partido::getIdPartido(){
    return _IdPartido;
}

int Partido::getIdTorneo(){
    return _IdTorneo;
}

Resultado Partido::getResultadoPartido(){
    return _ResultadoPartido;
}


int Partido::getTipo(){
    return _Formato;
}

bool Partido::getJugado(){
    return _Jugado;
}

int Partido::getFechaTorneo(){
    return _FechaTorneo;
}

void Partido::setEquipos(Equipo equip1,Equipo equip2){
        _local = equip1;
        _visitante= equip2;
}

void Partido::setIdPartido(int idPartido){
    _IdPartido=idPartido;
}

void Partido::setIdTorneo(int idTorneo){
    _IdTorneo=idTorneo;
}

void Partido::setResultadoPartido(Resultado result){
_ResultadoPartido=result;
}

void Partido::setTipo(int tipo){
    _Formato=tipo;
}

void Partido::setJugado(bool jugado){
    _Jugado=jugado;
}

void Partido::setFechaTorneo(int FechaT){
    _FechaTorneo=FechaT;
}


void Partido::Ganador() {//muestra el ganador del partido y tambien si hubo empate
        if(_local.getIdEquipo() == _ResultadoPartido.enviaResultado()){
            cout <<"Ganador el equipo: " <<_local.getNombre()<<endl;
            _local.setPartidosJugados(1);
            _local.setPartidosGanados(1);
            _visitante.setPartidosPerdidos(1);
            _visitante.setPartidosJugados(1);
        }
        else if (_visitante.getIdEquipo() == _ResultadoPartido.enviaResultado() )
            {
            cout <<"Ganador el equipo: " <<_visitante.getNombre()<<endl;
             _visitante.setPartidosJugados(1);
            _visitante.setPartidosGanados(1);
            _local.setPartidosPerdidos(1);
            _local.setPartidosJugados(1);
        }
        else if(_ResultadoPartido.enviaResultado()== -1){
            if(_Jugado){
            cout <<"Hubo empate"<<endl;
            _local.setPartidosJugados(1);
            _visitante.setPartidosJugados(1);
            _visitante.setPartidosEmpatados(1);
            _local.setPartidosEmpatados(1);

            }
        }


    int vGoles[2]{};

    *vGoles=_ResultadoPartido.getCantGoles();


    _local.setGolesEquipoGenerales(vGoles[0]);
    _local.setGolesPartido(vGoles[0]);
     _visitante.setGolesEquipoGenerales(vGoles[1]);
    _visitante.setGolesPartido(vGoles[1]);
}


bool Partido::leerDeDisco(int posicion){
    FILE* pFile=fopen("partidos.dat","rb");
    if(pFile==nullptr){
        return 0;
    }
    fseek(pFile,sizeof(Partido)*posicion,0);
    bool leyo=fread(this,sizeof(Partido),1,pFile);
    fclose(pFile);
    return leyo;
}

bool Partido::modificarRegistro(){
    FILE* pFile=fopen("partidos.dat","rb+");
    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,(_IdPartido-1)*sizeof(Partido),0);
    bool modifico=fwrite(this,sizeof(Partido),1,pFile);
    fclose(pFile);
    return modifico;
}

int Partido::getCantidadDeRegistros(){
    FILE* pFile=fopen("partidos.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int cantidadDeRegistros=ftell(pFile)/sizeof(Partido);
    fclose(pFile);
    return cantidadDeRegistros;
}

bool Partido::grabarEnDisco(){
    FILE* pFile=fopen("partidos.dat","ab");
    if(pFile==nullptr){
        return false;
    }
    bool grabo=fwrite(this,sizeof(Partido),1,pFile);
    fclose(pFile);
    return grabo;
}

int Partido::getIdGanador(){
    int idGanador=_ResultadoPartido.enviaResultado();
    return idGanador;
}

int Partido::getIdPerdedor(){
    if(_ResultadoPartido.getGolesLocal()>_ResultadoPartido.getGolesVisitante()){
        return _visitante.getIdEquipo();
    }
    else if(_ResultadoPartido.getGolesLocal()<_ResultadoPartido.getGolesVisitante()){
        return _local.getIdEquipo();
    }
}

void Partido::cargarResultado(){
    Resultado resultado;
    Jugador jugador;
    FuncionesUtiles func;
    resultado.setIdEquipo(_local.getIdEquipo(),_visitante.getIdEquipo());
    ///CAGA LOS EQUIPOS
    _local.leerDeDisco(_local.getIdEquipo()-1);
    _visitante.leerDeDisco(_visitante.getIdEquipo()-1);
    ///CARGA GOLES
    int golesLocal=0,golesVisitante=0;
    cout<<"RESULTADO DEL PARTIDO"<<endl;
    cout<<"GOLES EQUIPO LOCAL "<<_local.getNombre()<<": ";
    cin>>golesLocal;
    while(cin.fail()||golesLocal<0){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
        cin>>golesLocal;
    }
    cout<<"GOLES EQUIPO VISITANTE "<<_visitante.getNombre()<<": ";
    cin>>golesVisitante;
    while(cin.fail()||golesVisitante<0){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
        cin>>golesVisitante;
    }
    _local.addGoles(golesLocal);
    _visitante.addGoles(golesVisitante);
    resultado.setCantGoles(golesLocal,golesVisitante);
    if(golesLocal==golesVisitante){
        _local.addEmpate();
        _visitante.addEmpate();
    }
    else if(golesLocal>golesVisitante){
        _local.addVictoria();
        _visitante.addDerrota();
    }
    else{
        _local.addDerrota();
        _visitante.addVictoria();
    }
    system("cls");
    Jugador aux;
    if(golesLocal>0){
            cout<<"DETALLE DE GOLES EQUIPO LOCAL"<<endl;
        for(int i=0;i<golesLocal;i++){
            int nroCamisetaGol,nroCamisetaAsistencia=0;
            cout<<"NUMERO CAMISETA DEL GOLEADOR(0 para saltear): ";
            cin>>nroCamisetaGol;
            while(cin.fail()||nroCamisetaGol<0){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamisetaGol;
            }
            if(nroCamisetaGol!=0){
                aux=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaGol);
                while(aux.getNumeroCamiseta()==-1){
                    cout<<"EL JUGADOR INGRESADO NO EXISTE, INTENTE NUEVAMENTE"<<endl;
                    cin>>nroCamisetaGol;
                    while(cin.fail()||nroCamisetaGol<0){
                        cin.clear();
                        cin.ignore(256,'\n');
                        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                        cin>>nroCamisetaGol;
                    }
                    if(nroCamisetaGol!=0){
                        aux=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaGol);
                    }
                    else{
                        break;
                    }
                }
                if(nroCamisetaGol!=0){
                    jugador=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaGol);
                    jugador.addGoles(1);
                    jugador.modificarRegistro();
                }

                ///CARGA ASISTENCIA
                cout<<"NUMERO CAMISETA DEL ASISTENTE(0 para saltear): ";
                cin>>nroCamisetaAsistencia;
                while(cin.fail()||nroCamisetaAsistencia<0){
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                    cin>>nroCamisetaAsistencia;
                }
                if(nroCamisetaAsistencia!=0){
                    aux=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaAsistencia);
                    while(aux.getNumeroCamiseta()==-1||nroCamisetaAsistencia==0){
                        cout<<"EL JUGADOR INGRESADO NO EXISTE, INTENTE NUEVAMENTE"<<endl;
                        cin>>nroCamisetaAsistencia;
                        while(cin.fail()||nroCamisetaAsistencia<0){
                            cin.clear();
                            cin.ignore(256,'\n');
                            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                            cin>>nroCamisetaAsistencia;
                        }
                        if(nroCamisetaAsistencia!=0){
                            aux=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaAsistencia);
                        }
                        else{
                            break;
                        }
                    }
                    if(nroCamisetaAsistencia>0){
                        jugador=func.buscarIdJugador(_local.getIdEquipo(),nroCamisetaAsistencia);
                        jugador.addAsistencias(1);
                        jugador.modificarRegistro();

                    }
                }
            }
        }
    }
    system("cls");
    if(golesVisitante>0){
            cout<<"DETALLE DE GOLES EQUIPO LOCAL"<<endl;
        for(int i=0;i<golesVisitante;i++){
            int nroCamisetaGol,nroCamisetaAsistencia=0;
            cout<<"NUMERO CAMISETA DEL GOLEADOR(0 para saltear): ";
            cin>>nroCamisetaGol;
            while(cin.fail()||nroCamisetaGol<0){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamisetaGol;
            }
            if(nroCamisetaGol!=0){
                aux=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaGol);
                while(aux.getNumeroCamiseta()==-1){
                    cout<<"EL JUGADOR INGRESADO NO EXISTE, INTENTE NUEVAMENTE"<<endl;
                    cin>>nroCamisetaGol;
                    while(cin.fail()||nroCamisetaGol<0){
                        cin.clear();
                        cin.ignore(256,'\n');
                        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                        cin>>nroCamisetaGol;
                    }
                    if(nroCamisetaGol!=0){
                        aux=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaGol);
                    }
                    else{
                        break;
                    }
                }
                if(nroCamisetaGol!=0){
                    jugador=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaGol);
                    jugador.addGoles(1);
                    jugador.modificarRegistro();
                }

                ///CARGA ASISTENCIA
                cout<<"NUMERO CAMISETA DEL ASISTENTE(0 para saltear): ";
                cin>>nroCamisetaAsistencia;
                while(cin.fail()||nroCamisetaAsistencia<0){
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                    cin>>nroCamisetaAsistencia;
                }
                if(nroCamisetaAsistencia!=0){
                    aux=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaAsistencia);
                    while(aux.getNumeroCamiseta()==-1||nroCamisetaAsistencia==0){
                        cout<<"EL JUGADOR INGRESADO NO EXISTE, INTENTE NUEVAMENTE"<<endl;
                        cin>>nroCamisetaAsistencia;
                        while(cin.fail()||nroCamisetaAsistencia<0){
                            cin.clear();
                            cin.ignore(256,'\n');
                            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                            cin>>nroCamisetaAsistencia;
                        }
                        if(nroCamisetaAsistencia!=0){
                            aux=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaAsistencia);
                        }
                        else{
                            break;
                        }
                    }
                    if(nroCamisetaAsistencia>0){
                        jugador=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamisetaAsistencia);
                        jugador.addAsistencias(1);
                        jugador.modificarRegistro();

                    }
                }
            }
        }
    }

    system("cls");

    ///CARGA AMONESTACIONES
    cout<<"AMONESTACIONES DEL PARTIDO"<<endl;
    cout<<"AMONESTACIONES EQUIPO LOCAL "<<_local.getNombre()<<": ";
    int tarjetasLocal,tarjetasVisitante;
    int amarillasLocal,amarillasVisitante,rojasLocal,rojasVisitante;
    cin>>tarjetasLocal;
    while(cin.fail()){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
        cin>>tarjetasLocal;
    }
    cout<<"AMONESTACIONES EQUIPO VISITANTE "<<_visitante.getNombre()<<": ";
    cin>>tarjetasVisitante;
    while(cin.fail()){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
        cin>>tarjetasVisitante;
    }
    system("cls");
    if(tarjetasLocal>0){
        cout<<"DETALLE DE TARJETAS EQUIPO LOCAL"<<endl;
        cout<<"TARJETAS AMARILLAS: ";
        cin>>amarillasLocal;
        while(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
            cin>>amarillasLocal;
        }
        int nroCamiseta;
        for(int i=0;i<amarillasLocal;i++){
            cout<<"NUMERO CAMISETA DEL AMONESTADO(0 para saltear): ";
            cin>>nroCamiseta;
            while(cin.fail()){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamiseta;
            }
            jugador=func.buscarIdJugador(_local.getIdEquipo(),nroCamiseta);
            if(jugador.getNumeroCamiseta()!=-1){
                jugador.addTarjetaAmarilla();
                jugador.modificarRegistro();
            }
        }
        cout<<"TARJETAS ROJAS: ";
        cin>>rojasLocal;
        while(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
            cin>>rojasLocal;
        }
        for(int i=0;i<rojasLocal;i++){
            cout<<"NUMERO CAMISETA DEL AMONESTADO(0 para saltear): ";
            cin>>nroCamiseta;
            while(cin.fail()){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamiseta;
            }
            jugador=func.buscarIdJugador(_local.getIdEquipo(),nroCamiseta);
            if(jugador.getNumeroCamiseta()!=-1){
                jugador.addTarjetaRoja();
                jugador.modificarRegistro();
            }
        }
    }
    system("cls");
    if(tarjetasVisitante>0){
        cout<<"DETALLE DE TARJETAS EQUIPO VISITANTE"<<endl;
        cout<<"TARJETAS AMARILLAS: ";
        cin>>amarillasVisitante;
        while(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
            cin>>amarillasVisitante;
        }
        int nroCamiseta;
        for(int i=0;i<amarillasVisitante;i++){
            cout<<"NUMERO CAMISETA DEL AMONESTADO(0 para saltear): ";
            cin>>nroCamiseta;
            while(cin.fail()||nroCamiseta<0){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamiseta;
            }
            jugador=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamiseta);
            if(jugador.getNumeroCamiseta()!=-1){
                jugador.addTarjetaAmarilla();
                jugador.modificarRegistro();
            }
        }
        cout<<"TARJETAS ROJAS: ";
        cin>>rojasVisitante;
        while(cin.fail()||rojasVisitante<0){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
            cin>>rojasVisitante;
        }
        for(int i=0;i<rojasVisitante;i++){
            cout<<"NUMERO CAMISETA DEL AMONESTADO(0 para saltear): ";
            cin>>nroCamiseta;
            while(cin.fail()){
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"DEBE INGRESAR UN NUMERO ENTERO MAYOR O IGUAL A CERO"<<endl;
                cin>>nroCamiseta;
            }
            jugador=func.buscarIdJugador(_visitante.getIdEquipo(),nroCamiseta);
            if(jugador.getNumeroCamiseta()!=-1){
                jugador.addTarjetaRoja();
                jugador.modificarRegistro();
            }
        }
    }
    ///GUARDA TODOS LOS REGISTROS MODIFICADOS
    resultado.setCantAmarillas(amarillasLocal,amarillasVisitante);
    resultado.setCantRojas(rojasLocal,rojasVisitante);
    setJugado(true);
    _local.modificarRegistro();
    _visitante.modificarRegistro();
    _ResultadoPartido=resultado;
}
