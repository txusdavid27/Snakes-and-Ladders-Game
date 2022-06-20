#include<iostream>
#include <windows.h>
#include<iomanip>
#include<time.h>
#include<cstdlib>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<cstring>
#include<fstream>
#include<string>
#include"funciones.cpp"
#include"TAD.cpp"

/**
 *@def [int] tab : el tamaño del tablero.
 *@brief Es constante ; no se modifica.
*/
#define tab 56

using namespace std;


/**
 *FUNCIÓN PRINCIPAL
*/

int main(int argc, char * argv[])
{
    saludo();//LLamado a Presentación
    system("cls");//Borra Pantalla
    titulo(0);//Encabezado del juego con el numero de la partida (0)
    bool seguir=true;//Centinela para salir del ciclo do.
    Lista<Tipo> *jugadores;//declarar Lista jugadores Tipo
    Lista<Tipo> *tablero;//declarar Lista tablero(del mismo tipo)
    do
    {
        cout<<"EMPEZAR JUEGO NUEVO? "<<endl;
        switch(menu(1))//Muestra menu principal para empezar el juego y genera valor de opción.
        {
        case 0:
            seguir=false;
            break;
        case 1:
            jugadores=crearLista<Tipo>();
            tablero=crearLista<Tipo>();
            int cant;
            //Pedir cantidad de jugadores.
            cant=pedirCant();
            system("cls");
            if(cant<=0)
            {
                //No hay jugadores, se acaba.
                seguir=false;
                //elimina memorias.
                destruirLista (tablero);
                destruirLista (jugadores);
            }
            else if( juego( tablero, cant, jugadores) == 0)//Comienza el juego.
            {
                cout<<endl<<"FIN DEL JUEGO......."<<endl;
                /*Acaba el juego,
                elimina memorias.*/
                destruirLista (tablero);
                destruirLista(jugadores);
            }
            break;
        default:
            seguir=false;
            //elimina Listas
            destruirLista (tablero);
            destruirLista(jugadores);
            break;
        }
    }
    while(seguir);
    system("PAUSE");
    //FIN DEL PROGRAMA.
    return EXIT_SUCCESS;
}

void saludo()
{
    cout<<"****ESCALERAS Y SERPIENTES***"<<endl<<endl;
    cout<<"|POR: JESUS DAVID TRASLAVINA FUENTES       |"<<endl;
    cout<<"|SEGUNDA ENTREGA DEL PROYECTO DE CURSO P.C |"<<endl;
    cout<<"|Press enter_______________________________|"<<endl;
    cin.ignore();
}

/**
    *@fn titulo
    *@brief Muestra en consola el titulo del juego con la partida actual.
    *@param [int] turno: valor entero que representa el juego ocurrente.
*/
void titulo(int turno)
{
    cout<<"**************ESCALERAS Y SERPIENTES******, PARTIDA="<<turno<<"***"<<endl;
}

/**
    *@fn pedirCant
    *@brief Pide por consola la cantidad de jugadores que participan.
    *@return [int] cant: representa la cantidad de jugadores.
*/
int pedirCant()
{
    int cant;
    cout<<"Por favor digite el numero de jugadores(MAX=5): "<<endl;
    cin>>cant;
    cout<<"LEA CON ATENCION:"<<endl;
    cout<<"En este juego (S# & S# = una SERPIENTE) y (E# & E# = una ESCALERA) "<<endl;
    Sleep(5000);
    esperar();
    return cant;
}

/**
    *@fn menu
    *@brief Representa una función que pide un valor para empezar el juego o salir.
    *@param [int] sit: Representa la situación 1 o 0, para mostrar un menú particular.
    *@return [int] op: Representa la opción elegida por el jugador.
*/
int menu(int sit )
{
    if(sit==1)
    {
        int op;
        cout<<"MENU DE INTERACCION____"<<endl;
        cout<<"1.Jugar"<<endl;
        cout<<"0.Salir"<<endl;
        cin>>op;
        return op;
    }
    else
    {
        int op;
        cout<<"/////////////////////////////"<<endl;
        cout<<"MENU DE INTERACCION (Pausa)__"<<endl;
        cout<<"1.Continuar"<<endl;
        cout<<"0.Salir"<<endl;
        cin>>op;
        return op;
    }
}
/**
    *@fn esperar
    *@brief Representa la función que detiene la compilación del codigo para que el ser humano capte los cambios del Juego.
*/
void esperar()
{
    for(int i=3; i>=1; i--)
    {
        Sleep(100);
        cout<<"......."<<i;
    }
    Sleep(100);
}











































