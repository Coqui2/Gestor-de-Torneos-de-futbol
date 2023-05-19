using namespace std;

#include "Menues.h"
#include "FuncionesUtiles.h"
#include "torneo.h"

#include <string>


void prueba(){cout<<"prueba";}

void menuPrincipal(){
    Menu menu;
    system("cls");
    setlocale(LC_ALL,"C");
    FuncionesUtiles func;
    func.setTorneoActivo(-1);
    menu.addHeader("MENU PRINCIPAL");
    menu.addOptFunct("CREAR TORNEO",crearTorneoNuevo);
    menu.addOptFunct("TORNEOS EXISTENTES",menuTipoDeTorneo);
   menu.addOptFunct("ESTADISTICAS GENERALES",menuEstadisticasGenerales);
//    menu.addOptFunct("CONFIGURACIONES",menuConfiguraciones);
    menu.addExit("SALIR",salir);
    menu.mostrarmenu();
}



void salir(){
    exit(500);
}


void menuTipoDeTorneo(){
    system("cls");
    FuncionesUtiles func;
    int cantidadTorneos=func.getCantidadTorneos();
    if(!(cantidadTorneos>0)){
        cout<<"NO HAY TORNEOS CREADOS. VOLVIENDO AL MENU PRINCIPAL";
        Sleep(1200);
        menuPrincipal();
    }
    else{
        Menu menu;
        menu.addHeader("TORNEOS EXISTENTES");
        menu.addOptFunct("TORNEOS EN CURSO",menuSeleccionDeTorneoEnCurso);
        menu.addOptFunct("TORNEOS FINALIZADOS",menuSeleccionDeTorneoFinalizado);
        menu.addExit("VOLER A MENU PRINCIPAL",menuPrincipal);
        menu.mostrarmenu();
    }
}

void menuSeleccionDeTorneoEnCurso(){
    Menu menu;
    menu.addHeader("SELECCIONAR TORNEO POR ID");
    menu.addOptFunct("BUSCAR ID DEL TORNEO",listarTorneosEnCursoYElegir);
    menu.addOptFunct("TENGO ID DEL TORNEO",setTorneoEnCursoPorIngreso);
    menu.addExit("VOLVER",menuTipoDeTorneo);
    menu.mostrarmenu();
}

void menuSeleccionDeTorneoFinalizado(){
    Menu menu;
    menu.addHeader("SELECCIONAR TORNEO POR ID");
    menu.addOptFunct("BUSCAR ID DEL TORNEO",listarTorneosFinalizadosYElegir);
    menu.addOptFunct("TENGO ID DEL TORNEO",setTorneoFinalizadoPorIngreso);
    menu.addExit("VOLVER",menuTipoDeTorneo);
    menu.mostrarmenu();
}



void menuTorneosEnCurso(){
    system("cls");
    Menu menu;
    Torneo torneo;
    FuncionesUtiles func;
    torneo.leerDeDisco(func.getTorneoActivo()-1);
    string nombreTorneo="TORNEO ";
    nombreTorneo.append(torneo.getNombre());
    menu.addHeader(nombreTorneo);
    menu.addOptFunct("MOSTRAR FIXTURE",menuFixture);
    menu.addOptFunct("CARGAR RESULTADO DE PARTIDO",menuCargarResultado);
    menu.addOptFunct("ESTADISTICAS",menuEstadisticasTorneoEnCurso);
    menu.addExit("VOLVER",menuPrincipal);
    menu.mostrarmenu();
}

void menuFixture(){
    system("cls");
    Menu menu;
    menu.addOptFunct("TODOS LOS PARTIDOS",mostrarTodos);
    menu.addOptFunct("PARTIDOS PENDIENTES",mostrarPendientes);
    menu.addExit("VOLVER",menuTorneosEnCurso);
    menu.mostrarmenu();
}



void menuTorneosFinalizados(){
    system("cls");
    Menu menu;
    Torneo torneo;
    FuncionesUtiles func;
    torneo.leerDeDisco(func.getTorneoActivo()-1);
    string nombreTorneo="TORNEO ";
    nombreTorneo.append(torneo.getNombre());
    menu.addHeader(nombreTorneo);
    menu.addOptFunct("ESTADISTICAS",menuEstadisticasTorneoFinalizado);
    menu.addExit("VOLVER",menuPrincipal);
    menu.mostrarmenu();
}

void menuCargarResultado(){
    Menu menu;
    menu.addHeader("CARGA DE RESULTADO");
    menu.addOptFunct("BUSCAR ID PARTIDO",listarPartidosYElegir);
    menu.addOptFunct("TENGO EL ID DEL PARTIDO",setIdPartidoPorIngrso);
    menu.addExit("VOLVER",menuTorneosEnCurso);
    menu.mostrarmenu();
}


void menuEstadisticasGenerales(){
    Menu menu;
    menu.addHeader("ESTADISTICAS GENERALES");
    //menu.addOptFunct("TABLA DE POSICIONES GENERAL: ",placeHolder);
    //menu.addOptFunct("TABLA DE GOLEADORES HISTORICA: ",placeHolder);
    menu.addOptFunct("MAXIMO GOLEADOR POR EQUIPO: ",maximoGoleadorEquipo);
    menu.addOptFunct("LISTADO HISTORICO DE EQUIPOS",listadoHistoricoEquipos);
    menu.addOptFunct("TODOS LOS JUGADORES",listarTodosJugadoresEquipo);
    menu.addOptFunct("JUGADORES POR EQUIPOS",listarJugadoresEquipo);
    menu.addExit("VOLVER",menuPrincipal);
    menu.mostrarmenu();
}

void menuConfiguraciones(){

    Menu menu;
    menu.addHeader("CONFIGURACIONES");
    menu.addOptFunct("CARGAR EQUIPO: ",placeHolder);
    menu.addOptFunct("CARGAR JUGADORES: ",placeHolder);
    menu.addOptFunct("TRASPASOS DE JUGADORES: ",placeHolder);
    menu.addExit("VOLVER",menuTorneosEnCurso);
    menu.mostrarmenu();

}

void crearTorneoNuevo(){
    FuncionesUtiles func;
    func.crearTorneoNuevo();
    menuTorneosEnCurso();
}

void setIdPartidoPorIngrso(){
    system("cls");
    FuncionesUtiles func;
    int idPartido;
    cout<<"INGRESE ID DEL PARTIDO(-1 para volver): ";
    cin>>idPartido;
    if(idPartido==-1){
        menuTorneosEnCurso();
    }
    else{
            if(func.validacionSeleccionPartido(idPartido)){
                func.cargarResultado(idPartido);
                menuTorneosEnCurso();
            }
            else{
                cout<<"EL PARTIDO NO EXISTE O YA HA SIDO JUGADO"<<endl;
                Sleep(1300);
                menuTorneosEnCurso();
            }
        }
}

void listarPartidosYElegir(){
    FuncionesUtiles func;
    system("cls");
    if(func.listarPartidosPendientesDeTorneoActivo()){
        int idPartido;
        cout<<"INGRESE EL ID DE PARTIDO ELEGIDO(-1 para volver): ";
        cin>>idPartido;
        if(idPartido==-1){
            menuTorneosEnCurso();
        }
        else{
            if(func.validacionSeleccionPartido(idPartido)){
                func.cargarResultado(idPartido);
                menuTorneosEnCurso();

            }
            else{
                cout<<"EL PARTIDO NO EXISTE O YA HA SIDO JUGADO"<<endl;
                Sleep(1300);
                menuTorneosEnCurso();
            }
        }
    }
    else{
        system("cls");
        cout<<"NO HAY PARTIDOS SIN JUGAR"<<endl;
        Sleep(1300);
    }
    menuTorneosEnCurso();
}

void setTorneoFinalizadoPorIngreso(){
    system("cls");
    int idTorneo;
    FuncionesUtiles func;
    cout<<"INGRESE ID DEL TORNEO(-1 para volver): ";
    cin>>idTorneo;
    if(idTorneo==-1){
        menuTipoDeTorneo();
    }
    else{
            if(func.validacionSeleccionTorneo(idTorneo)){
                func.setTorneoActivo(idTorneo);
                menuTorneosFinalizados();
            }
            else{
                cout<<"TORNEO INEXISTENTE"<<endl;
                Sleep(1300);
                menuTipoDeTorneo();
            }
        }
}

void setTorneoEnCursoPorIngreso(){
    system("cls");
    int idTorneo;
    FuncionesUtiles func;
    cout<<"INGRESE ID DEL TORNEO(-1 para volver): ";
    cin>>idTorneo;
    if(idTorneo==-1){
        menuTipoDeTorneo();
    }
    else{
            if(func.validacionSeleccionTorneo(idTorneo)){
                func.setTorneoActivo(idTorneo);
                menuTorneosEnCurso();
            }
            else{
                cout<<"TORNEO INEXISTENTE"<<endl;
                Sleep(1300);
                menuTipoDeTorneo();
            }
        }
}

void listarTorneosFinalizadosYElegir(){
    FuncionesUtiles func;
    system("cls");
    if(func.listarTorneosFinalizados()){
        int idTorneo;
        cout<<"INGRESE EL ID DE TORNEO ELEGIDO(-1 para volver): ";
            cin>>idTorneo;
        if(idTorneo==-1){
            menuTipoDeTorneo();
        }
        else{
            if(func.validacionSeleccionTorneo(idTorneo)){
                func.setTorneoActivo(idTorneo);
                menuTorneosFinalizados();
            }
            else{
                cout<<"TORNEO INEXISTENTE"<<endl;
                Sleep(1300);
                menuSeleccionDeTorneoFinalizado();
            }
        }
    }
    else{
        system("cls");
        cout<<"NO HAY TORNEOS FINALIZADOS"<<endl;
        Sleep(1300);
        menuTipoDeTorneo();
    }
}

void listarTorneosEnCursoYElegir(){
    FuncionesUtiles func;
    system("cls");
    if(func.listarTorneosEnCurso()){
        int idTorneo;
        cout<<"INGRESE EL ID DE TORNEO ELEGIDO(-1 para volver): ";
        cin>>idTorneo;
        if(idTorneo==-1){
            menuTipoDeTorneo();
        }
        else{
            if(func.validacionSeleccionTorneo(idTorneo)){
                func.setTorneoActivo(idTorneo);
                menuTorneosEnCurso();
            }
            else{
                cout<<"TORNEO INEXISTENTE"<<endl;
                Sleep(1300);
                menuSeleccionDeTorneoEnCurso();
            }
        }

    }

    else{
        system("cls");
        cout<<"NO HAY TORNEOS EN CURSO"<<endl;
        Sleep(1300);
        menuTipoDeTorneo();

    }
}

void placeHolder(){}

void menuFinTorneo(){
    system("cls");
    Menu menu;
    menu.addOptFunct("VER ESTADISTICAS DE TORNEO",menuEstadisticasTorneoFinalizado);
    menu.addExit("VOLVER A MENU PRINCIPAL",menuPrincipal);
    menu.mostrarmenu();
}

void mostrarTodos(){
    FuncionesUtiles func;
    system("cls");
    func.listarTodosPartidos();
    system("pause");
    menuTorneosEnCurso();
}

void mostrarPendientes(){
    FuncionesUtiles func;
    system("cls");
    func.listarPartidosPendientesDeTorneoActivo();
    system("pause");
    menuTorneosEnCurso();
}


void menuEstadisticasTorneoFinalizado(){
    system("cls");
    Menu menu;
    menu.addHeader("ESTADISTICAS TORNEO");
    menu.addOptFunct("TABLA DE POSICIONES",tablaDePosiciones);
    menu.addExit("VOLVER",menuTorneosFinalizados);
    menu.mostrarmenu();
}

void menuEstadisticasTorneoEnCurso(){
    system("cls");
    Menu menu;
    Equipo equipo;
    menu.addHeader("ESTADISTICAS TORNEO");
    menu.addOptFunct("TABLA DE POSICIONES",tablaDePosiciones);

    menu.addExit("VOLVER",menuTorneosEnCurso);
    menu.mostrarmenu();
}

void tablaDePosiciones(){
    system("cls");
    FuncionesUtiles func;
    func.tablaPosiciones();
    system("pause");
    system("cls");
}

void listarJugadoresEquipo(){
system("cls");
Equipo equipo;
int idEquipo;
cout<<"INGRESE EL ID DE EQUIPO"<<endl;
cin>>idEquipo;
system("cls");
while(idEquipo<1){
system("cls");
    cout<<"EL ID INGRESADO NO ES VALIDO"<<endl;

cout<<"INGRESE EL ID DE EQUIPO"<<endl;
cin>>idEquipo;
}
equipo.listarJugadoresEquipo(idEquipo);
system("pause");
system("cls");


}

void listarTodosJugadoresEquipo(){
system("cls");
Equipo equipo;

equipo.listarJugadoresTodosEquipo();
system("pause");
system("cls");

}
void listadoHistoricoEquipos(){
Equipo aux;
system("cls");
aux.listaHistoricaEquipos();
system("pause");
system("cls");

}

void maximoGoleadorEquipo(){

Equipo aux;
system("cls");
aux.maximoGoleadorEquipo();
cout<<endl<<endl;
system("pause");
system("cls");

}


