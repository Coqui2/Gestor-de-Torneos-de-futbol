#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

class Eliminatoria{
    private:
        int _idTorneo;
        int _cantidad;
        int _arrayEquipos[32];
        int _ronda;
        int _totalRondas;
        int _partidosJugados;
        int _partidosRonda;

    public:

        Eliminatoria(){};
        Eliminatoria(int idTorneo,int cantidad, int* arrayEquipos);
        void armarRonda();
        void borrarPerdedor(int idPerdedor);
        int getPartidosRonda();
        int getPartidosJugados();
        int getRonda();
        int getTotalRondas();
        bool finalRonda();
        bool finalEliminatoria();
        void addPartidoJugado();
        int getCampeon();

};

#endif // ELIMINATORIA_H
