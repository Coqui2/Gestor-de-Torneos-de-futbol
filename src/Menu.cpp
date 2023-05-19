#include "Menu.h"

void Menu::askOption(){
    setlocale(LC_ALL,"spanish");
    int opt;
    while(true){
        system("cls");
        cout<<"Elija una opción: "<<endl;
        getOpciones();
        cin>>opt;
        if(opt==0&&_tieneExit){
                _exitOpt.ejecFuncion();
                break;
        }
        else{
            if(opt>0&&opt<=_cantidad){
                ejec(opt);
                system("pause");
                break;
            }
        }
        cout<<"Opción inválida, intente nuevamente"<<endl;
        Sleep(1200);
    }

}

void Menu::addExit(string opc, void funcion()){
    Opcion nuevaOpt(opc,funcion);
    _exitOpt=nuevaOpt;
    _tieneExit=1;
}

void Menu::getOpciones(){
    if(_tieneHeader){

        cout<<_header<<endl;

    }
    for(int i=0;i<_cantidad;i++){

        cout<<i+1<<". "<<_opciones[i].getTexto()<<endl;
    }
    if(_tieneExit){
        cout<<endl;
        cout<<"0. "<<_exitOpt.getTexto();
    }
}

void Menu::ejec(int i){
    _opciones[i-1].ejecFuncion();
}

void Menu::addOptFunct(string opc, void funcion()){
    Opcion nuevaOpcion(opc, funcion);
    Opcion *pBufferOpc;

    pBufferOpc = new Opcion [_cantidad+1];
    if(pBufferOpc==nullptr){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        exit(1);
    }
    for(int i=0;i<_cantidad;i++){
        pBufferOpc[i]= _opciones[i];
    }

    pBufferOpc[_cantidad]=nuevaOpcion;

    if(_opciones != nullptr){
        delete [] _opciones;
    }

    _opciones=pBufferOpc;
    _cantidad++;
}

void showItem(const char* text, int posx, int posy, bool selected) {
    if (selected){
        rlutil::setBackgroundColor(rlutil::color::RED);
        rlutil::locate(posx - 3, posy);
        char open=175;
        char close=174;
        std::cout << " " << open << " " << text << " " << close << " " << std::endl;
    }
    else{
        rlutil::setBackgroundColor(rlutil::color::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << text << "         " << std::endl;
    }
    rlutil::setBackgroundColor(rlutil::color::BLACK);

}
void showItemHeader(const char* text, int posx, int posy, bool selected) {
    if (selected){
        rlutil::setBackgroundColor(rlutil::color::BLUE);
        rlutil::locate(posx - 3, posy-1);
        char open=175;
        char close=174;
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;
    }
    else{
        rlutil::setBackgroundColor(rlutil::color::LIGHTBLUE);
        rlutil::locate(posx - 3, posy-1);
        std::cout << "    " << text << "  " << std::endl;
    }
    rlutil::setBackgroundColor(rlutil::color::BLACK);

}

void Menu::mostrarmenu(){
    int offset=1;
    int x=50, y=10;

    while(true){
        rlutil::hidecursor();
        printBackground();
        if(_tieneHeader){

            showItemHeader(_header.c_str(), x, y, offset == 0);
        }
        for(int i=0; i<_cantidad;i++){
            showItem(_opciones[i].getTexto().c_str(), x, y+(i+1)*2, offset == i+1);
        }
        if(_tieneExit){
            showItem(_exitOpt.getTexto().c_str(), x, y+(_cantidad+1)*2, offset == _cantidad+1);
        }

        int key = rlutil::getkey();
        switch (key)
        {
        case 14:
            rlutil::locate(x-2, y + offset);
            std::cout << " " << std::endl;
            offset--;
            if (offset < 1){
                if(_tieneExit){
                    offset=_cantidad+1;
                }
                else{
                    offset = _cantidad;
                }
            }
            break;
        case 15:
            rlutil::locate(x-2, y + offset);
            std::cout << " " << std::endl;
            offset++;
            if(_tieneExit){
                if (offset > _cantidad+1){
                    offset =1;
                }
            }
            else if(offset > _cantidad){
                offset=1;
            }
            break;
        case 1:
            if(offset>_cantidad){
                system("cls");
                _exitOpt.ejecFuncion();
            }
            else{
                system("cls");
                ejec(offset);
            }
        }
    }
}


void Menu::printBall(){
///     _,...,_
///   .'@/   \@'.
///  //  \___/  \\
/// |@\__/a@a\__/a|
/// |a/  \@@@/  \@|
///  \\__/   \__//
///   `.a\___/a.'   jgs
///     `'""""`
}


void Menu::printBackground(){

int x=6;
rlutil::locate(x,16);
cout<<"                                                                            o                                          "<<endl;
rlutil::locate(x,17);
cout<<"                                                                           \"|\\                                         "<<endl;
rlutil::locate(x,18);
cout<<"                                                          _________________/)_____________________________________     "<<endl;
rlutil::locate(x,19);
cout<<"                                                         /                     ()    /                           /     "<<endl;
rlutil::locate(x,20);
cout<<"                                                        /________   o               /                  _________/      "<<endl;
rlutil::locate(x,21);
cout<<"                                                     /|/o ___   / /|\"              /                  /  o___/|\\       "<<endl;
rlutil::locate(x,22);
cout<<"                                                    /_|/\"'  /  /-, )\\        _.--\"/\"-,   ' o\"    _.--/  ~|\\ / |_\\     "<<endl;
rlutil::locate(x,23);
cout<<"                                                   / //)   /  /   :         /    /    :  \"/-    /   /  / (\\/ /  /      "<<endl;
rlutil::locate(x,24);
cout<<"                                                  /|/     /  /   /         (    /    /   /)    (   /  /    |\\  /       "<<endl;
rlutil::locate(x,25);
cout<<"                                                 /_|     /  /.-'      o    `._ /_.-'           `. /  /     |_\\/        "<<endl;
rlutil::locate(x,26);
cout<<"                                                  /-----'  /         /|\"     /                   /  `-----/            "<<endl;
rlutil::locate(x,27);
cout<<"                                                 /--------'          /)     /                   `--------/             "<<endl;
rlutil::locate(x,28);
cout<<"                                                /                          /                            /              "<<endl;
rlutil::locate(x,29);
cout<<"                                               /__________________________/____________________________/               "<<endl;
}
