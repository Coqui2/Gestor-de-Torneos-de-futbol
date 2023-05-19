#include "Eliminatoria.h"
#include "partido.h"
#include "torneo.h"
#include "FuncionesUtiles.h"



Eliminatoria::Eliminatoria(int idTorneo,int cantidad, int* arrayEquipos){
    FuncionesUtiles fu;
    _idTorneo=idTorneo;
    _partidosJugados=0;
    _partidosRonda=cantidad;
    _cantidad=cantidad;
    _ronda=0;
    for(int i=0; i<cantidad;i++){
        _arrayEquipos[i]=arrayEquipos[i];
    }
    _totalRondas=fu.calcularTotalRondas(cantidad);
}

int Eliminatoria::getTotalRondas(){return _totalRondas;}

int Eliminatoria::getRonda(){return _ronda;}

int Eliminatoria::getPartidosRonda(){return _partidosRonda;}

int Eliminatoria::getPartidosJugados(){return _partidosJugados;}

void Eliminatoria::armarRonda(){
    _ronda++;
    int halfSize=_cantidad/2;
    for(int i=0; i<halfSize;i++){
        Partido partido(_idTorneo,_arrayEquipos[i],_arrayEquipos[_cantidad-1-i],2,_ronda);
        partido.grabarEnDisco();
    }
    _partidosJugados=0;
    _partidosRonda=_partidosRonda/2;
}




void Eliminatoria::borrarPerdedor(int idPerdedor){
    bool salePerdedor=0;
    for(int i=0;i<_cantidad;i++){
        if(salePerdedor){
            _arrayEquipos[i-1]=_arrayEquipos[i];
        }
        if(_arrayEquipos[i]==idPerdedor){
            salePerdedor=1;
        }
    }
    _cantidad--;
}

bool Eliminatoria::finalRonda(){
    if(_partidosJugados==_partidosRonda){
        return true;
    }
    return false;
}

bool Eliminatoria::finalEliminatoria(){
    if(finalRonda()&&_ronda==_totalRondas){
        return true;
    }
    return false;
}

void Eliminatoria::addPartidoJugado(){
    _partidosJugados++;
}

int Eliminatoria::getCampeon(){
    return _arrayEquipos[0];
}
