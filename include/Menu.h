#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "locale.h"
#include <iostream>
#include <string>
using namespace std;
#include "rlutil.h"

class Opcion{
private:
    string _texto;
    void (*_funcion)();

public:
    Opcion(){};
    Opcion(string texto,void funcion()){
        _texto=texto;
        _funcion=funcion;
    }
    string getTexto(){return _texto;}
    void setFunction(void funcion()){_funcion=funcion;}
    void ejecFuncion(){(*_funcion)();}
};

class Menu{
private:
    int _cantidad;
    Opcion *_opciones;
    bool _tieneExit=0;
    Opcion _exitOpt;
    bool _tieneHeader=0;
    string _header;

public:
    Menu(){
        _cantidad=0;
        _opciones=nullptr;
    }
    void addHeader(string header){_header=header;_tieneHeader=1;}
    void ejec(int i);
    void addOptFunct(string opc, void funcion());
    void addExit(string opc, void funcion());
    int getCantidad(){return _cantidad;}
    void getOpciones();
    void askOption();
    void mostrarmenu();
    void printBackground();
    void printBall();
};



#endif // MENU_H_INCLUDED
