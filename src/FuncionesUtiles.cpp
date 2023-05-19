# include<iostream>
# include<cstdlib>

using namespace std;
#include <ctime>
#include <algorithm>
#include "FuncionesUtiles.h"
#include "torneo.h"
#include "jugador.h"
#include "rlutil.h"
#include "Menues.h"
#include "equipo.h"


bool FuncionesUtiles::checkeaNroRepetido(int* arr, int nro, int tam){
    for(int i=0;i<tam;i++){
        if(arr[i]==nro){
            return true;
        }
    }
    return false;
}


///PARA GRUPOS O ELIMINATORIA SOLO POTENCIAS DE 2, MAYORES QUE 2
void FuncionesUtiles::sorteadorDePartidos(int* arrayIDEquipos,int cantidad, int tipo, int idTorneo){

    switch(tipo){
        case 1:                 ///liga
            {

            ///chequea si son equipos impares
            bool fechaLibre=0;
            if(cantidad%2!=0){
                cantidad+=1;
                fechaLibre=1;
            }

            int* arrayEquiposCorregido = new int[cantidad];
            if(arrayEquiposCorregido==nullptr){
                cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
                exit(1);
            }
            ///en caso de ser impares agrega un equipo fantasma para fechas libres
            for(int i=0;i<cantidad;i++){
                if(fechaLibre&&i==(cantidad-1)){
                    arrayEquiposCorregido[cantidad-1]=-1;
                }
                else{
                    arrayEquiposCorregido[i]=arrayIDEquipos[i];
                }
            }
            int fechas = (cantidad - 1);
            int halfSize = cantidad / 2;

            int* arraySinPrimerEquipo = new int[fechas];
            if(arraySinPrimerEquipo==nullptr){
                cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
                exit(1);
            }

            ///ordena de manera decreciente la primera mitad del array, en la segunda mitad del nuevo array
            for(int i=1;i<halfSize;i++){
                arraySinPrimerEquipo[fechas-i]=arrayEquiposCorregido[i];
            }

            ///ordena de manera creciente la primera mitad del array, en la primera mitad del nuevo array
            for(int i=halfSize; i<cantidad;i++){
                arraySinPrimerEquipo[i-halfSize]=arrayEquiposCorregido[i];
            }

            for (int fecha = 0; fecha < fechas; fecha++){
            ///ROTACION ROUND ROBIN
            ///PRIMER EQUIPO SE MANTIENE EN EL LUGAR Y EL RESTO ROTA DE MANERA ANTI-HORARIA
                int idSinPrimero = fecha % fechas;
                ///PARTIDOS EQUIPO 1
                if(arraySinPrimerEquipo[idSinPrimero]!=-1){
                    Partido partido(idTorneo,arrayEquiposCorregido[0],arraySinPrimerEquipo[idSinPrimero],1,fecha+1);
                    partido.grabarEnDisco();
                }
                ///RESTO DELOS PARTIDOS
                for (int i = 1; i < halfSize; i++){
                    int equipo1 = (fecha + i) % fechas;
                    int equipo2 = (fecha  + fechas - i) % fechas;
                    if(arraySinPrimerEquipo[equipo1]!=-1&&arraySinPrimerEquipo[equipo2]!=-1){
                        Partido partido2(idTorneo,arraySinPrimerEquipo[equipo1],arraySinPrimerEquipo[equipo2],1,fecha+1);
                        partido2.grabarEnDisco();
                    }
                }
            }
            delete [] arrayEquiposCorregido;
            delete [] arraySinPrimerEquipo;
            break;
            }
        case 2:                 ///FIXTURE DE GRUPO
            ///EN PARTE HARDCODEADO PARA MANTENER ORDEN RELATIVO ENTRE ID DE PARTIDO Y FECHA DE TORNEO
            {
            {
                Partido partido(idTorneo,arrayIDEquipos[2],arrayIDEquipos[3],1,1);
                partido.grabarEnDisco();
            }

            for(int i=0;i<2;i++){
                Partido partido(idTorneo,arrayIDEquipos[0],arrayIDEquipos[i+1],1,i+1);
                partido.grabarEnDisco();
            }
            for(int i=2;i>0;i--){
                Partido partido(idTorneo,arrayIDEquipos[1],arrayIDEquipos[i+1],1,4-i);
                partido.grabarEnDisco();
            }
            {
                Partido partido(idTorneo,arrayIDEquipos[0],arrayIDEquipos[3],1,3);
                partido.grabarEnDisco();
            }
            break;
            }

    }





}

///SORTEA LOS GRUPOS
void FuncionesUtiles::sorteadorDeGrupos(int* arrayIDEquipos, int cantidadEquipos, int idTorneo){
    ///ALEATORIZA EL ORDEN DE LOS EQUIPOS DENTRO DEL ARRAY
    random_shuffle(&arrayIDEquipos[0],&arrayIDEquipos[cantidadEquipos]);
    int tamGrupo=4;
    int cantidadGrupos=cantidadEquipos/tamGrupo;
    int arrayIDgrupo[4];
    ///SEPARA LOS EQUIPOS EN GRUPOS DE 4 Y CREA LOS PARTIDOS CORRESPONDIENTES AL GRUPO
    for(int i=0;i<cantidadGrupos;i++){
        for(int j=0;j<tamGrupo;j++){
            arrayIDgrupo[j]=arrayIDEquipos[(i*tamGrupo)+j];
        }
        sorteadorDePartidos(arrayIDgrupo,tamGrupo, 2,idTorneo);  ///tipo 2=grupos
    }
}

///ABRE Y CIERRA LOS ARCHIVOS PARA ASEGURARSE QUE EXISTAN
bool FuncionesUtiles::chequeoDeArchivos(){
    FILE* pFile=fopen("partidos.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    pFile=fopen("torneos.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    pFile=fopen("jugadores.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    pFile=fopen("equipos.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    pFile=fopen("torneoactivo.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    return true;
}

///CALCULA EL TOTAL DE RONDAS EN UNA ELIMINATORIA
int FuncionesUtiles::calcularTotalRondas(int cantidadEquipos){
    if(cantidadEquipos==32) return 5;
    if(cantidadEquipos==16) return 4;
    if(cantidadEquipos==8) return 3;
    if(cantidadEquipos==4) return 2;
}

///ORDENA UN ARRAY DE EQUIPOS DE MANERA DESCENDENTE
void FuncionesUtiles::ordenarEquiposDescendente(Equipo* arrayEquipos,int cantidad){
    for(int i=0;i<cantidad;i++){
        for(int j=i+1;j<cantidad;j++){
            if(arrayEquipos[i].getPuntosEquipo()<arrayEquipos[j].getPuntosEquipo()){
                Equipo aux;
                aux=arrayEquipos[i];
                arrayEquipos[i]=arrayEquipos[j];
                arrayEquipos[j]=aux;
            }
        }
    }
}

///RECIBE UN ARRAY DE EQUIPOS Y EL ID DE LA PRIMERA MITAD EN OTRO ARRAY
void FuncionesUtiles::getMejorMitadDeEquipos(int* arrayEquipos,Equipo* auxEquipos,int cantidad){
    for(int i=0;i<cantidad;i++){
        arrayEquipos[i]=auxEquipos[i].getIdEquipo();
    }
}

///REVISA QUE TORNEO ESTA ACTIVO EN EL ARCHIVO
int FuncionesUtiles::getTorneoActivo(){
    FILE* p;
    p=fopen("torneoactivo.dat","rb");
    if(p==nullptr) return -1;
    int torneoActivo;
    fread(&torneoActivo,sizeof(int),1,p);
    fclose(p);
    return torneoActivo;
}

///GUARDA EN ARCHIVO EL ID DEL TORNEO ACTIVO
void FuncionesUtiles::setTorneoActivo(int idtorneo){
    FILE* p;
    p=fopen("torneoactivo.dat","wb");
    if(p==nullptr) return;
    fwrite(&idtorneo,sizeof(int),1,p);
    fclose(p);
}

///VALIDA CANTIDAD DE EQUIPOS INGRESADA
bool FuncionesUtiles::esCantidadValida(int cantidad){
    if(cantidad==32) return true;
    if(cantidad==16) return true;
    if(cantidad==8) return true;
    if(cantidad==4) return true;
    return false;
}

//CREA UN TORNEO NUEVO
void FuncionesUtiles::crearTorneoNuevo(){
    system("cls");
    setlocale(LC_ALL,"spanish");
    FuncionesUtiles func;
    ///SOLICITA LOS DATOS DEL TORNEO AL USUARIO
    string nombre;
    int cantidadEquipos,formato;
    cout<<"INGRESE EL NOMBRE DEL TORNEO (-1 para volver): ";
    fflush(stdin);
    getline(cin,nombre);
    string salir="-1";
    if(salir==nombre){
        menuPrincipal();
    }

    cout<<"INGRESE EL FORMATO DEL TORNEO:\n1 - LIGA\n2 - COPA\n3 - ELIMINACION DIRECTA\n";
    cin>>formato;
    while(formato<1||formato>3){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"INGRESE UNA OPCIÓN CORRECTA"<<endl;
        cout<<"INGRESE EL FORMATO DEL TORNEO:\n1 - LIGA\n2 - COPA\n3 - ELIMINACION DIRECTA\n";
        cin>>formato;
    }
    system("cls");
    if(formato!=1){
            cout<<"LOS TORNEOS EN ESTE FORMATO PUEDEN SER DE 32, 16, 8 o 4 EQUIPOS"<<endl;
    }
    bool okCantidad=0;
    ///VALIDA CANTIDAD DE EQUIPOS
    while(!okCantidad){
        cout<<"INGRESE CANTIDAD DE EQUIPOS: ";
        cin>>cantidadEquipos;
        if(formato==1){
            if(cantidadEquipos>1){
                okCantidad=1;
            }
        }
        else{
            okCantidad=func.esCantidadValida(cantidadEquipos);
        }
        if(!okCantidad){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"INGRESE UNA CANTIDAD VÁLIDA"<<endl;
        }
    }

    ///CREA TORNEO CON LOS DATOS IGRESADOS Y GUARDA EN DISCO
    Torneo torneo(nombre,cantidadEquipos,formato);
    torneo.grabarEnDisco();

    ///SE SETEA EL ID DEL TORNEO NUEVO COMO ACTIVO
    func.setTorneoActivo(torneo.getID());

    ///SE CREAN LOS EQUIPOS
    for(int i=0;i<cantidadEquipos;i++){

        system("cls");
        cout<<"EQUIPO "<<i+1<<" DE "<<cantidadEquipos<<":"<<endl;
        crearEquipo();
    }
    ///SE CREA EL FIXTURE
    torneo.crearFixture();
}

///SE CREAN LOS EQUIPOS CON LOS DATOS INGRESADOS
void FuncionesUtiles::crearEquipo(){
    int idTorneo=getTorneoActivo();
    string nombre;
    int cantidadJugadores;
    cout<<"INGRESE EL NOMBRE DEL EQUIPO: ";
    fflush(stdin);
    getline(cin,nombre);
    Equipo equipo(nombre,idTorneo);
    equipo.grabarEnDisco();
    cout<<"INGRESE LA CANTIDAD DE JUGADORES: ";
    cin>>cantidadJugadores;
    while(cin.fail()||cantidadJugadores<0){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"INGRESE UNA CANTIDAD VÁLIDA"<<endl;
        cin>>cantidadJugadores;
    }
    for(int i=0;i<cantidadJugadores;i++){
        system("cls");
        cout<<"JUGADOR "<<i+1<<" DE "<<cantidadJugadores<<" DEL EQUIPO "<<equipo.getNombre()<<":"<<endl;
        crearJugador(equipo.getIdEquipo());
    }
}

///SE CREA JUGADOR CON LOS DATOS INGRESADOS
void FuncionesUtiles::crearJugador(int idEquipo){
    int idtorneo=getTorneoActivo();
    Jugador aux;
    string nombre;
    int edad, nroCamiseta;
    cout<<"INGRESE NOMBRE DEL JUGADOR: ";
    fflush(stdin);
    getline(cin,nombre);
    cout<<"INGRESE EDAD DEL JUGADOR: ";
    cin>>edad;
    while(edad<1){
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"INGRESE UN NÚMERO ENTERO POSITIVO"<<endl;
        cin>>edad;
    }
    cout<<"INGRESE NÚMERO DE CAMISETA: ";
    cin>>nroCamiseta;
    while(nroCamiseta<1){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"INGRESE UN NÚMERO ENTERO POSITIVO"<<endl;
            cin>>nroCamiseta;
        }
    aux=buscarIdJugador(idEquipo,nroCamiseta);
    while(aux.getNumeroCamiseta()!=-1){
        cout<<"EL NÚMERO DE CAMISETA SE ENCUENTRA TOMADO, ELIJA OTRO: ";
        cin>>nroCamiseta;
        while(nroCamiseta<1){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"INGRESE UN NÚMERO POSITIVO"<<endl;
            cin>>nroCamiseta;
        }
        aux=buscarIdJugador(idEquipo,nroCamiseta);
    }
    Jugador jugador(nombre,edad,nroCamiseta,idtorneo,idEquipo);
    jugador.grabarEnDisco();
}

///FUNCIONES PARA GENERAR PROXIMOS ID EN FUNCION
///A LA CANTIDAD DE REGISTROS
int FuncionesUtiles::getProximoIDEquipo(){
    int proximoID;
    FILE* p;
    p=fopen("equipos.dat","rb");
    if(p==nullptr){
        return -1;
    }
    fseek(p,0,SEEK_END);
    proximoID=ftell(p)/sizeof(Equipo)+1;
    return proximoID;
}

int FuncionesUtiles::getProximoIDTorneo(){
    FILE* pFile=fopen("torneos.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int proximoID=ftell(pFile)/sizeof(Torneo)+1;
    fclose(pFile);
    return proximoID;
}

int FuncionesUtiles::getProximoIDPartido(){
    FILE* pFile=fopen("partidos.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int proximoID=ftell(pFile)/sizeof(Partido)+1;
    fclose(pFile);
    return proximoID;
}

int FuncionesUtiles::getCantidadTorneos(){
    FILE* pFile=fopen("torneos.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int cantidadRegistros=ftell(pFile)/sizeof(Torneo);
    fclose(pFile);
    return cantidadRegistros;
}

int FuncionesUtiles::getProximoIDJugador(){
    FILE* pFile=fopen("jugadores.dat","rb");
    if(pFile==nullptr){
        return -1;
    }
    fseek(pFile,0,SEEK_END);
    int proximoID=ftell(pFile)/sizeof(Jugador)+1;
    fclose(pFile);
    return proximoID;
}

///SE LISTAN TODOS LOS TORNEOS
void FuncionesUtiles::listarTodosTorneos(){
    Torneo torneo;
    int pos=0;
    cout<<"LISTADO DE TORNEOS EXISTENTES"<<endl;
    cout<<"NRO TORNEO\t\tNOMBRE TORNEO"<<endl;
    while(torneo.leerDeDisco(pos++)){
        cout<<torneo.getID()<<"\t\t\t"<<torneo.getNombre()<<endl;
    }
    cout<<endl<<endl;
}

///SE LISTAN LOS TORNEOS EN CURSO
bool FuncionesUtiles::listarTorneosEnCurso(){
    Torneo torneo;
    int pos=0;
    bool hay=0;
    cout<<"LISTADO DE TORNEOS EN CURSO"<<endl;
    cout<<"NRO TORNEO\t\tNOMBRE TORNEO"<<endl;
    while(torneo.leerDeDisco(pos++)){
        if(!torneo.getFinalizado()){
                hay=1;
            cout<<torneo.getID()<<"\t\t\t"<<torneo.getNombre()<<endl;
        }
    }
    cout<<endl<<endl;
    return hay;
}

///SE LISTAN LOS TORNEOS FINALIZADOS
bool FuncionesUtiles::listarTorneosFinalizados(){
    Torneo torneo;
    bool hay=0;
    int pos=0;
    cout<<"LISTADO DE TORNEOS FINALIZADOS"<<endl;
    cout<<"NRO TORNEO\t\tNOMBRE TORNEO"<<endl;
    while(torneo.leerDeDisco(pos++)){
        if(torneo.getFinalizado()){
                hay=1;
            cout<<torneo.getID()<<"\t\t\t"<<torneo.getNombre()<<endl;
        }
    }
    cout<<endl<<endl;
    return hay;
}

///SE BUSCA Y DEVUELVE UN OBJETO JUGADOR EN BASE AL ID DE EQUIPO Y NRO DE CAMISETA
Jugador FuncionesUtiles::buscarIdJugador(int idEquipo, int nroCamiseta){
    Jugador aux;
    int pos=0;
    while(aux.leerDeDisco(pos++)){
        if(aux.getIdEquipo()==idEquipo&&aux.getNumeroCamiseta()==nroCamiseta){
            return aux;
        }
    }
    Jugador aux2("NA",-1,-1,-1,-1);
    return aux2;
}

///SE LISTAN LOS EQUIPOS DEL TORNEO ACTIVO
void FuncionesUtiles::listarEquiposDeTorneoActivo(){
    Equipo equipo;
    int torneoActivo=getTorneoActivo();
    int pos=0;
        cout<<"LISTADO DE EQUIPOS: "<<endl;
        cout<<"ID EQUIPO\t\tNOMBRE EQUIPO"<<endl;
    while(equipo.leerDeDisco(pos++)){
            if(equipo.getIdTorneo()==torneoActivo){
                cout<<equipo.getIdEquipo()<<"\t\t\t"<<equipo.getNombre()<<endl;
            }
    }
    cout<<endl<<endl;
}

///SE LISTAN TODOS LOS PARTIDOS
bool FuncionesUtiles::listarTodosPartidos(){
    Partido partido;
    bool hay=0;
    int torneoActivo=getTorneoActivo();
    int pos=0;
        cout<<"LISTADO DE PARTIDOS: "<<endl;
        cout<<"ID\tFECHA\t\tLOCAL\t\tvs\tVISITANTE"<<endl;
    while(partido.leerDeDisco(pos++)){
            if(partido.getIdTorneo()==torneoActivo){
                hay=1;
                cout<<partido.getIdPartido()<<"\tFECHA "<<partido.getFechaTorneo();
                cout<<"\t\t"<<partido.getLocal().getNombre()<<"\t\tvs\t"<<partido.getVisitante().getNombre()<<endl;
            }
    }
    cout<<endl<<endl;
    return hay;
}

///SE LISTAN LOS PARTIDOS SIN JUGAR DEL TORNEO ACTIVO
bool FuncionesUtiles::listarPartidosPendientesDeTorneoActivo(){
    Partido partido;
    bool hay=0;
    int torneoActivo=getTorneoActivo();
    int pos=0;
        cout<<"LISTADO DE PARTIDOS: "<<endl;
        cout<<"ID\tFECHA\t\tLOCAL\t\tvs\tVISITANTE"<<endl;
    while(partido.leerDeDisco(pos++)){
            if(partido.getIdTorneo()==torneoActivo&&!partido.getJugado()){
                hay=1;
                cout<<partido.getIdPartido()<<"\tFECHA "<<partido.getFechaTorneo();
                cout<<"\t\t"<<partido.getLocal().getNombre()<<"\t\tvs\t"<<partido.getVisitante().getNombre()<<endl;
            }
    }
    cout<<endl<<endl;
    return hay;
}

///PERMITE LA CARGA DE RESULTADO DE UN PARTIDO
void FuncionesUtiles::cargarResultado(int idPartido){
    Partido partido;
    Torneo torneo;
    torneo.leerDeDisco(getTorneoActivo()-1);
    partido.leerDeDisco(idPartido-1);
    partido.cargarResultado();
    partido.modificarRegistro();
    torneo.addPartidoJugado();
    if(partido.getTipo()==2){
        torneo.addPartidoElim(partido.getIdPerdedor());
    }
    torneo.modificarRegistro();
    torneo.condicionFinal();
    torneo.modificarRegistro();
}

///SE EJECUTA AL FINALIZAR UN TORNEO
void FuncionesUtiles::finTorneo(int idCampeon){
    Equipo aux;
    setlocale(LC_ALL,"spanish");
    aux.leerDeDisco(idCampeon-1);
    cout<<endl<<endl;
    cout<<"                                                      ___________     "<<endl;
    cout<<"                                                     '._==_==_=_.'    "<<endl;
    cout<<"                                                     .-\\:      /-.    "<<endl;
    cout<<"                                                    | (|:.     |) |   "<<endl;
    cout<<"                                                     '-|:.     |-'    "<<endl;
    cout<<"                                                       \\::.    /      "<<endl;
    cout<<"                                                        '::. .'       "<<endl;
    cout<<"                                                          ) (         "<<endl;
    cout<<"                                                        _.' '._       "<<endl;
    cout<<"                                                       `\"\"\"\"\"\"\"`      "<<endl;
    rlutil::setBackgroundColor(rlutil::color::RED);
    rlutil::locate(50, 15);
    cout<<" ¡TORNEO FINALIZADO! ";
    rlutil::locate(50, 16);
    cout<<"EL EQUIPO CAMPEON ES:";
    string nombreCampeon=aux.getNombre();
    rlutil::locate(60-(nombreCampeon.length()/2), 17);
    cout<<nombreCampeon;
    rlutil::setBackgroundColor(rlutil::color::BLACK);
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    system("pause");
    system("cls");
}

///VALIDA SELECCION DE TORNEO
bool FuncionesUtiles::validacionSeleccionTorneo(int idTorneo){
    Torneo torneo;
    int pos=0;
    while(torneo.leerDeDisco(pos++)){
        if(idTorneo==torneo.getID()){
            return true;
        }
    }

    return false;
}

///VALIDA SELECCION DE PARTIDO
bool FuncionesUtiles::validacionSeleccionPartido(int idPartido){
    Partido aux;
    int pos=0;
    while(aux.leerDeDisco(pos++)){
        if(idPartido==aux.getIdPartido()&&aux.getIdTorneo()==getTorneoActivo()){
            if(aux.getJugado()){
                return false;
            }
            else{
                return true;
            }
        }
    }
    return false;
}

///SE MUESTRA POR PANTALLA LA TABLA DE POSICIONES
void FuncionesUtiles::tablaPosiciones(){
    Torneo aux;
    aux.leerDeDisco(getTorneoActivo()-1);
    int cantidad=aux.getCantidadEquipos();
    Equipo* equipos=new Equipo[cantidad];
    if(equipos==nullptr){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        exit(1);
    }
    aux.setArrayEquiposPorPuntos(equipos);
    cout<<"TABLA DE POSICIONES";
    rlutil::locate(1,3);
    cout<<"EQUIPO";
    rlutil::locate(35,3);
    cout<<"PUNTOS";
    rlutil::locate(50,3);
    cout<<"P.JUGADOS";
    rlutil::locate(65,3);
    cout<<"P.GANADOS";
    rlutil::locate(80,3);
    cout<<"P.PERDIDOS";
    rlutil::locate(95,3);
    cout<<"P.EMPATADOS";
    rlutil::locate(110,3);
    cout<<"GOLES";
    for(int i=0;i<cantidad;i++){
        rlutil::locate(1,4+i);
        cout<<equipos[i].getNombre();
        rlutil::locate(35+4,4+i);
        cout<<equipos[i].getPuntosEquipo();
        rlutil::locate(50+4,4+i);
        cout<<equipos[i].getPartidosJugados();
        rlutil::locate(65+4,4+i);
        cout<<equipos[i].getPartidosGanados();
        rlutil::locate(80+4,4+i);
        cout<<equipos[i].getPartidosPerdidos();
        rlutil::locate(95+4,4+i);
        cout<<equipos[i].getPartidosEmpatados();
        rlutil::locate(110+4,4+i);
        cout<<equipos[i].getGolesEquipoGenerales();
    }
    cout<<endl<<endl<<endl<<endl;

}

