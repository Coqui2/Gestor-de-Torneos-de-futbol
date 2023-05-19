#ifndef FUNCIONESADICIONALES_H_INCLUDED
#define FUNCIONESADICIONALES_H_INCLUDED

#include <ctime>
#include <algorithm>
#include "partido.h"
#include "equipo.h"


bool checkeaNroRepetido(int* arr, int nro, int tam){
    for(int i=0;i<tam;i++){
        if(arr[i]==nro){
            return true;
        }
    }
    return false;
}


///PARA GRUPOS O ELIMINATORIA SOLO POTENCIAS DE 2
void sorteadorDePartidos(int* arrayIDEquipos,int cantidad, int tipo, int idTorneo){
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

            ///ordena de manera decreciente la primera mitad del array, en la segunda mitad del nuevo
            for(int i=1;i<halfSize;i++){
                arraySinPrimerEquipo[fechas-i]=arrayEquiposCorregido[i];
            }

            ///ordena de manera creciente la primera mitad del array, en la primera mitad del nuevo
            for(int i=halfSize; i<cantidad;i++){
                arraySinPrimerEquipo[i-halfSize]=arrayEquiposCorregido[i];
            }

            for (int fecha = 0; fecha < fechas; fecha++){

                int idSinPrimero = fecha % fechas;
                if(arraySinPrimerEquipo[idSinPrimero]!=-1){
                    Partido partido(idTorneo,arrayEquiposCorregido[0],arraySinPrimerEquipo[idSinPrimero],1,fecha);
                    partido.grabarEnDisco();
                }

                for (int i = 1; i < halfSize; i++){
                    int equipo1 = (fecha + i) % fechas;
                    int equipo2 = (fecha  + fechas - i) % fechas;
                    if(arraySinPrimerEquipo[equipo1]!=-1&&arraySinPrimerEquipo[equipo2]!=-1){
                        Partido partido2(idTorneo,arraySinPrimerEquipo[equipo1],arraySinPrimerEquipo[equipo2],1,fecha);
                        partido2.grabarEnDisco();
                    }
                }
            }
            delete [] arrayEquiposCorregido;
            delete [] arraySinPrimerEquipo;
            break;
            }
        case 2:                 ///grupo
            {

            for(int i=0;i<3;i++){       ///crea y guarda los partidos del equipo del indice 0
                Partido partido(idTorneo,arrayIDEquipos[0],arrayIDEquipos[i+1],1,i+1);
                partido.grabarEnDisco();
            }
            for(int i=1;i<3;i++){       ///crea y guarda los partidos del equipo del indice 1
                Partido partido(idTorneo,arrayIDEquipos[1],arrayIDEquipos[i+1],1,4-i);
                partido.grabarEnDisco();
            }
            Partido partido(idTorneo,arrayIDEquipos[2],arrayIDEquipos[3],1,1);
            partido.grabarEnDisco();
            break;
            }

    }





}

void sorteadorDeGrupos(int* arrayIDEquipos, int cantidadEquipos, int idTorneo){
    random_shuffle(&arrayIDEquipos[0],&arrayIDEquipos[cantidadEquipos]);
    int tamGrupo=4;
    int cantidadGrupos=cantidadEquipos/tamGrupo;
    int arrayIDgrupo[4];
    for(int i=0;i<cantidadGrupos;i++){
        for(int j=0;j<tamGrupo;j++){
            arrayIDgrupo[j]=arrayIDEquipos[(i*tamGrupo)+j];
        }
        sorteadorDePartidos(arrayIDgrupo,tamGrupo, 2,idTorneo);  ///tipo 2=grupos
    }
}

///ABRE Y CIERRA LOS ARCHIVOS PARA ASEGURARSE QUE EXISTEN
bool chequeoDeArchivos(){
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
    pFile=fopen("eliminatorias.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    pFile=fopen("resultados.dat","ab");
    if(pFile==nullptr){
        return 0;
    }
    fclose(pFile);
    return true;
}


int calcularTotalRondas(int cantidadEquipos){
    int aux=32;
    int cont=6;
    for(int i=aux;i>0;i/=2){
        if(cantidadEquipos%i==0){
            cont--;
        }
    }
    int totalRondas=6-cont;
    return totalRondas;
}

void ordenarEquiposDescendente(Equipo* arrayEquipos,int cantidad){
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

void getMejorMitadDeEquipos(int* arrayEquipos,Equipo* auxEquipos,int cantidad){
    for(int i=0;i<cantidad;i++){
        arrayEquipos[i]=auxEquipos[i].getIdEquipo();
    }
}


#endif // FUNCIONESADICIONALES_H_INCLUDED
