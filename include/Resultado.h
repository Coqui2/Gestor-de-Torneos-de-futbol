#ifndef RESULTADO_H
#define RESULTADO_H



class Resultado
{

     private:
         int _idPartido;
         int _idEquipo[2]; ///id en la primera posicion es local, y el almacenado en la segunda posicion es el visitante
         int _cantGoles[2];
         int _puntosObtenidos[2];
         int _cantAmarillas[2];
         int _cantRojas[2];


     public:

         int getIdPartido();
         int getIdEquipo();
         int getCantGoles();
         int getGolesLocal();
         int getGolesVisitante();
         int getPuntosObtenidos();
         int getCantAmarillas();
         int getCantRojas();


         void setIdPartido(int idPartido);
         void setIdEquipo(int local, int visitante);
         void setCantGoles(int local, int visitante);
         void setPuntosObtenidos();
         void setCantAmarillas(int local, int visitante);
         void setCantRojas(int local, int visitante);
         void asignarGoles(int idEquipo,int numeroCamiseta,int cantGoles);
         void asignarAmarillas(int idJugador);
         void asignarRojas(int idJugador);
         void asignarAsistencias(int idEquipo,int numeroCamiseta,int cantAsistencias);
         int enviaResultado();
         void crearResultado();
//         void cargarResultado(int idPartido);


};

#endif // RESULTADO_H
