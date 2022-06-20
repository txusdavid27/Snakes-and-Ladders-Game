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
#include"funciones.h"

/**
 *@def [int] tab : el tamaño del tablero.
 *@brief Es constante ; no se modifica.
*/
#define tab 56

using namespace std;




/**
    *@fn juego
    *@brief Representa la función que hace un juego completo, es un controlador.
    *@param [Lista<T> *] pista: Lista del tablero de tipo T
    *@param [int] cant: Representa la cantidad de jugadores(para el ciclo).
    *@param [Lista<T> *] jugadores: Lista de jugadores tipo T.
    *@return [int]: Representa el fin o salida de la función(fin del juego).
*/

template<typename T>
int juego(Lista<T> *pista,int cant, Lista<T> *jugadores)
{
    llenarPista(pista,cant,jugadores);//LLamado a la función llenarPista.
    bool ganador=false;//Centinela para acabar el juego.
    int partida=1;//Contador de partidas.
    do
    {
        switch(menu(2))//Llamado a Menu con situación 2.
        {
        case 0:
            return 0;//Salir del juego.
            break;
        case 1:
            cin.get();
            system("cls");
            esperar();
            system("cls");
            titulo(partida);//Mostrar encabezado.
            indicar_posiactual(cant, jugadores);//Mostrar Posiciones
            cout<<endl<<"Espere..";
            Sleep(1500);
            system("cls");
            titulo(partida);//Mostrar encabezado.
            imprimir_pista(pista,cant,jugadores);
            srand(time(NULL));//Semilla de tiempo para número aleatorio
            for(int i=0; i<cant; i++)//Juego por jugador.
            {
                int c=0;///Cuenta las veces que saca 6.
                while(c<3)//Ciclo por si saca 6.
                {
                    cout<<"JUEGA: J"<<i+1<<endl;
                    cout<<"Tirar Dados ...Presione enter"<<endl;
                    cin.get();
                    esperar();
                    int ale;
                    ale=(1+rand()%(6));//Generar valor de un dado.
                    Tipo dato = obtenerDato(jugadores,i);//se pide prácticamente toda una estructura.(eso es lo que le llevamos al TAD).
                    if(((dato.permiso) == false) && ale != 6 )//Si no tiene permiso para avanzar.
                    {
                        ale=0;//No avanzar.(como si hubiera sacado nada).
                        cout<<"NECESITA SACAR  6 !!!"<<endl;
                    }
                    else if(((dato.permiso) == false) && ale == 6)//Si no tiene permiso y saca 6.
                    {
                        jugadores=actualizar_permiso(jugadores,i,true);
                        cout<<"PUEDE VOLVER A JUGAR !!!"<<endl;
                    }
                    if(ale==6)
                    {
                        c++;
                        cout<<"EL DADO SACO: "<<ale<<endl;
                        dato.posi += ale;//Avanza lo que saco el Ale.
                        jugadores=actualizar_posi(jugadores,i,dato.posi);
                        if(c==3)//Si saca 6 tres veces.
                        {
                            jugadores=actualizar_posi(jugadores,i,0);//Jugador vuelve a la pos inicial.
                            jugadores=actualizar_permiso(jugadores,i,false);
                        }
                        if(  ( (dato.posi) >= (tab-7)) && ((dato.posi)+ale!=(tab-1)) )
                        {
                            ale=0;//Jugador se acerca a la meta pero no saca exacto, no avanza.
                            cout<<"NECESITA SACAR EXACTO"<<endl;
                        }
                        indicar_posiactual(cant, jugadores);
                        dato=obtenerDato(jugadores,i);
                        if( dato.posi ==(tab-1))
                        {
                            cout<<"TENEMOS UN GANADOR!! "<<"Jugador# "<<i+1<<endl;
                            imprimir_pista(pista,cant,jugadores);//Muestra la pista.
                            return 0;
                        }
                        cout<<endl<<"Espere..";
                        Sleep(1500);
                        system("cls");
                        imprimir_pista(pista,cant,jugadores);
                    }
                    else
                    {
                        c=3;//Para acabar el ciclo provisional.
                        if(  ( dato.posi >= (tab-7)) && (dato.posi)+ale!=(tab-1) )
                        {
                            ale=0;
                            cout<<"NECESITA SACAR EXACTO"<<endl;
                        }
                        cout<<"EL DADO SACO: "<<ale<<endl;
                        dato.posi += ale;
                        jugadores= actualizar_posi(jugadores,i,dato.posi);
                        indicar_posiactual(cant, jugadores);
                        dato=obtenerDato(jugadores,i);
                        if(dato.posi ==(tab-1))
                        {
                            cout<<"TENEMOS UN GANADOR!! "<<"Jugador# "<<i+1<<endl;
                            imprimir_pista(pista,cant,jugadores);
                            ///Hay un Ganador.
                            return 0;
                        }
                        cout<<endl<<"Espere..";
                        Sleep(1500);
                        system("cls");
                        imprimir_pista(pista,cant,jugadores);
                    }
                }
            }
            break;
        default:
            return 0;
            break;
        }
        partida++;//Aumenta el contador de partidas.
    }
    while(!ganador);
    return 0;//Acaba el juego.
}

/**
    *@fn imprimir_pista
    *@brief Representa la función que hace un juego completo, es un controlador.
    *@param [Lista<T> *] pista: Lista del tablero de tipo T
    *@param [int] cant: Representa la cantidad de jugadores(para el ciclo).
    *@param [Lista<T> *] jugadores: Lista de jugadores tipo T.
*/

template<typename T>
void imprimir_pista(Lista<T>* pista, int cant, Lista<T>*jugadores)
{

    ///IMPRIMIR VALORES EN FORMA DE TABLERO:
    int p=(tab-1),pivot=0;//Variable para cambiar la orientación.
    /**
     *@var [int] p:Disminuye a cada impresión porque el tablero se imprime desde su renglón final hasta el inicial.
    */

    bool tramp=false;
    Tipo dato,datop;
    for(int i=0; i<5; i++)//Impresión de 5 filas.
    {
        if(pivot==0)
        {
            int tenedor=(p-10),t2=(p-10),evalua=(p-10);//(tenedor, t2 y evalua: representan la posición en la que esta con respecto al vector pista con tamaño 56.)
            ///Impresión de numeros de menor a mayor(ej: primera y última fila del tablero)
            ///de 1->11 y de 44-55.(la posición 0- no se imprime, porque quiero sea tablero cuadrado).
            for(int j=0; j<11; j++)//Se imprimen 11 columnas.
            {
                dato=obtenerDato(pista,tenedor);
                if(dato.forma<10)
                {
                    cout<<dato.forma<<"          ";
                }
                else
                {
                    cout<<dato.forma<<"         ";
                }
                tenedor++;
                p--;
            }//Se han impreso los numeros(forma).
            cout<<endl;
            for(int j=0; j<11; j++)
            {
                dato=obtenerDato(pista,t2);
                cout<<dato.trampa<<"         ";
                t2++;
            }//se han impreso las trampas
            cout<<endl;
            ///COMPARADOR PARA IMPRESIÓN
            for(int j=0; j<11; j++)
            {
                datop=obtenerDato(pista,evalua);
                int esp=0;
                for(int pl=0; pl<cant; pl++)//pl es igual a player(jugador).
                {
                    dato=obtenerDato(jugadores,pl);
                    if(datop.forma == dato.posi)//Si la posición del vector(evalua) es igual a la posición de algún jugador.
                    {
                        cout<<" J"<<pl+1<<".";//"       "
                        if(datop.proxiForma != dato.posi)//Si el apuntador de esa posición, no apunta a su valor congruente con la posición en el vector "forma"
                        {
                            //Hay una trampa, sea Serpiente o Escalera.
                            jugadores=actualizar_posi(jugadores, pl, datop.proxiForma );
                            //Valor del jugador; pasa a ser el valor al que apunta dirección "Proxi".
                            tramp=true;
                        }
                        esp=1;//Hay al menos un jugador en esa posición.
                    }
                }
                if(esp==0)//No hay ningún jugador en la posición.
                {
                    cout<<"           ";
                }
                evalua++;
            }//Se han impreso las "FICHAS DE LOS JUGADORES."
            cout<<endl;
            pivot=1;
        }
        else if(pivot==1)
        {
            int tenedor=p, t2=p, evalua=p;
            ///Impresión de numeros de mayor a menor(ej: Segunda y penúltima fila del tablero)
            ///de 23->12 y de 43-32.(la posición 0- no se imprime, porque quiero sea tablero cuadrado).
            for(int j=0; j<11; j++)
            {
                dato=obtenerDato(pista,tenedor);
                if(dato.forma<10)
                {
                    cout<<dato.forma<<"          ";
                }
                else
                {
                    cout<<dato.forma<<"         ";
                }
                tenedor--;
                p--;
            }
            cout<<endl;
            for(int j=0; j<11; j++)
            {
                dato=obtenerDato(pista,t2);
                cout<<dato.trampa<<"         ";
                t2--;
            }
            cout<<endl;
            ///COMPARADOR PARA IMPRESIÓN
            for(int j=0; j<11; j++)
            {
                datop=obtenerDato(pista,evalua);
                int esp=0;
                for(int pl=0; pl<cant; pl++)//pl es igual a player(jugador).
                {
                    dato=obtenerDato(jugadores,pl);
                    if(datop.forma == dato.posi)
                    {
                        cout<<" J"<<pl+1<<".";
                        if(datop.proxiForma != dato.posi)
                        {
                            jugadores=actualizar_posi(jugadores, pl, datop.proxiForma );
                            tramp=true;
                        }
                        esp=1;//Hay al menos un jugador en esa posición.
                    }
                }
                if(esp==0)//No hay ningún jugador en la posición.
                {
                    cout<<"           ";
                }
                evalua--;
            }
            cout<<endl;
            pivot=0;
        }
        cout<<endl;
        for(int x=0; x<120; x++)
        {
            cout<<".";
        }
        cout<<endl;
    }
    indicar_posiactual(cant, jugadores);
    if(tramp==true)//Avisa al jugador si cae en una posición cuyo apuntador NO pertenece a esa posición.
    {
        cout<<"CAISTE EN UNA TRAMPA!!"<<endl;
        cout<<"Presione enter para ver donde cae"<<endl;
        cin.get();
        system("cls");
        cout<<endl;
        imprimir_pista(pista,cant,jugadores);
    }
}

/**
    *@fn indicar_posiactual
    *@brief Representa la función que indica el valor de posición actual de los jugadores con respecto al tablero.
    *@param [int] cant: Representa la cantidad de jugadores(para el ciclo).
    *@param [Lista<T>*] jugadores: Lista de jugadores.
*/

template<typename T>
void indicar_posiactual(int cant,Lista<T>* jugadores)
{
    cout<<endl;
    cout<<"TABLA DE POSICIONES:"<<endl;
    Tipo dato;
    for(int i=0; i<cant; i++)
    {
        dato=obtenerDato(jugadores,i);
        cout<<"Jugador_"<<i+1<<" : "<<dato.posi<<endl;
    }
}

/**
    *@fn actualizar_posi
    *@brief Representa la actualización o modificación de un dato de un Nodo en específico.
    *@param [Lista<T> *] lista: Lista del tablero de tipo T
    *@param [int] jugador: Representa el jugador a buscar.
    *@param [int] pos: Dato que queremos actualizar.
    *@return [Lista<T>] lista: Representa el fin o salida de la función(fin del juego).
*/
template<typename T>
Lista<T>* actualizar_posi(Lista<T>* lista, int jugador, int pos )
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(jugador == p)
        {
            (aux->info).posi=pos;
            return lista;
        }
        aux = aux->sig;
        p++;
    }
    return lista;
}

/**
    *@fn actualizar_permiso
    *@brief Representa la actualización o modificación de un dato de un Nodo en específico.
    *@param [Lista<T> *] lista: Lista del tablero de tipo T
    *@param [int] jugador: Representa el jugador a buscar.
    *@param [int] pos: Dato que queremos actualizar.
    *@return [Lista<T>] lista: Representa el fin o salida de la función(fin del juego).
*/
template<typename T>
Lista<T>* actualizar_permiso(Lista<T>* lista, int jugador, bool peaje)
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(jugador == p)
        {
            (aux->info).permiso=peaje;
            return lista;
        }
        aux = aux->sig;
        p++;
    }
    return lista;

}

/**
    *@fn actualizar_forma
    *@brief Representa la actualización o modificación de un dato de un Nodo en específico.
    *@param [Lista<T> *] lista: Lista del tablero de tipo T
    *@param [int] jugador: Representa el jugador a buscar.
    *@param [int] pos: Dato que queremos actualizar.
    *@return [Lista<T>] lista: Representa el fin o salida de la función(fin del juego).
*/
template<typename T>
Lista<T>* actualizar_forma(Lista<T>* lista, int casilla, int valor)
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(casilla == p)
        {
            (aux->info).forma=valor;
            return lista;
        }
        aux = aux->sig;
        p++;
    }
    return lista;
}

/**
    *@fn actualizar_proxiFormas
    *@brief Representa la actualización o modificación de un dato de un Nodo en específico.
    *@param [Lista<T> *] lista: Lista del tablero de tipo T
    *@param [int] jugador: Representa el jugador a buscar.
    *@param [int] pos: Dato que queremos actualizar.
    *@return [Lista<T>] lista: Representa el fin o salida de la función(fin del juego).
*/
template<typename T>
Lista<T>* actualizar_proxiForma(Lista<T>* lista, int casilla, int proxima)
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(casilla == p)
        {
            (aux->info).proxiForma=proxima;
            return lista;
        }
        aux = aux->sig;
        p++;
    }
    return lista;
}

/**
    *@fn actualizar_trampa
    *@brief Representa la actualización o modificación de un dato de un Nodo en específico.
    *@param [Lista<T> *] lista: Lista del tablero de tipo T
    *@param [int] jugador: Representa el jugador a buscar.
    *@param [int] pos: Dato que queremos actualizar.
    *@return [Lista<T>] lista: Representa el fin o salida de la función(fin del juego).
*/
template<typename T>
Lista<T>* actualizar_trampa (Lista<T>* lista, int casilla, char* trampa)
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(casilla == p)
        {
            (aux->info).trampa=trampa;
            return lista;
        }
        aux = aux->sig;
        p++;
    }
    return lista;
}

/**
    *@fn llenarPista
    *@brief Representa la inicialización de algunos valores del tablero.
    *@param [Lista<T> *] pista: Lista.
    *@param [int] cant: cantidad de jugadores.
    *@param [Lista<T> *] jugadores: Lista.
*/

template<typename T>
void llenarPista(Lista<T> *pista, int cant, Lista<T>*jugadores)
{
    ///LLENAR PISTA CON VALORES validos para el tablero.
    Tipo dato_inicial;
    for(int i=0; i<tab; i++)
    {
        dato_inicial.forma=i;
        dato_inicial.proxiForma=i;
        strcpy(dato_inicial.trampa, "  ");
        insertar(pista,dato_inicial);
    }
    ///IMPRIMIR VALORES EN FORMA DE LISTA:
    for(int i=0; i<tab; i++)
    {
        Sleep(10);
        cout<<"...";
    }

    cout<<endl<<endl;
    ///IMPRIMIR VALORES EN FORMA DE TABLERO// Solo para verificación:
    int p=(tab-1),pivot=0;
    for(int i=0; i<5; i++)
    {
        Sleep(50);
        cout<<"*"<<endl;
    }
    system("cls");
    inicializar(pista, cant, jugadores);
}

/**
    *@fn inicializar
    *@brief Representa la inicialización de los valores del tablero y jugadores.
    *@param [Lista<T> *] pista: Lista.
    *@param [int] cant: cantidad de jugadores.
    *@param [Lista<T> *] jugadores: Lista.
*/
template<typename T>
void inicializar(Lista<T>* pista, int cant, Lista<T>*jugadores)
{
    ///INICIALIZAR CON ESPACIO CADA CAJON DEL TABLERO:
    ///No hay trampas, por tanto se deja el espacio para la impresión.
    /**
     *Las siguientes 40 lineas son para asignar una dirección al contenido de proxi, que sea diferente a la posición en la que se encuentra con respecto al vector
     *Es decir, crear Escaleras o Serpientes de manera arbitraria.
     *@note Sabemos que el char* para imprimir las trampas E# y S# pudo haber sido igual al modo que se hizo con las fichas
            de los jugadores, pero de esta manera la ejecución es más eficiente, aunque no es netamente práctico.
     *@see  @fn : imprimir_pista();
    */
    ///ESCALERAS:
    pista=actualizar_proxiForma(pista,3,23);
    pista=actualizar_trampa(pista,3,"E1");
    pista=actualizar_trampa(pista,23,"E1");
    pista=actualizar_proxiForma(pista,11,18);
    pista=actualizar_trampa(pista,11,"E2");
    pista=actualizar_trampa(pista,18,"E2");
    pista=actualizar_proxiForma(pista,16,37);
    pista=actualizar_trampa(pista,16,"E3");
    pista=actualizar_trampa(pista,37,"E3");
    pista=actualizar_proxiForma(pista,29,45);
    pista=actualizar_trampa(pista,29,"E4");
    pista=actualizar_trampa(pista,45,"E4");
    pista=actualizar_proxiForma(pista,42,46);
    pista=actualizar_trampa(pista,42,"E5");
    pista=actualizar_trampa(pista,46,"E5");

    ///SERPIENTES:
    pista=actualizar_proxiForma(pista,54,12);
    pista=actualizar_trampa(pista,54,"S1");
    pista=actualizar_trampa(pista,12,"S1");
    pista=actualizar_proxiForma(pista,51,39);
    pista=actualizar_trampa(pista,51,"S2");
    pista=actualizar_trampa(pista,39,"S2");
    pista=actualizar_proxiForma(pista,48,32);
    pista=actualizar_trampa(pista,48,"S3");
    pista=actualizar_trampa(pista,32,"S3");
    pista=actualizar_proxiForma(pista,43,31);
    pista=actualizar_trampa(pista,43,"S4");
    pista=actualizar_trampa(pista,31,"S4");
    pista=actualizar_proxiForma(pista,40,33);
    pista=actualizar_trampa(pista,40,"S5");
    pista=actualizar_trampa(pista,33,"S5");
    pista=actualizar_proxiForma(pista,27,1);
    pista=actualizar_trampa(pista,27,"S6");
    pista=actualizar_trampa(pista,1,"S6");
    pista=actualizar_proxiForma(pista,22,5);
    pista=actualizar_trampa(pista,22,"S7");
    pista=actualizar_trampa(pista,5,"S7");
    pista=actualizar_proxiForma(pista,19,8);
    pista=actualizar_trampa(pista,19,"S8");
    pista=actualizar_trampa(pista,8,"S8");

    ///INICIO DE CADA JUGADOR:
    Tipo iniciales;

    iniciales.permiso=true;
    iniciales.posi=0;

    for(int i=0; i<cant; i++)
    {
        insertar(jugadores,iniciales);
    }

}
