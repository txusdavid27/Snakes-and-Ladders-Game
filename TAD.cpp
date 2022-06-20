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
///TAD:

template<typename T>
void destruirLista(Lista<T> *lista)
{
    Nodo<T> *aux = lista->cab;
    while( !vacia(lista) )
    {
        eliminar(lista, 0);
    }
    delete lista;
}


template<typename T>
void imprimir(Lista<T> * lista)
{
    if(vacia(lista))
    {
        cout<<"La Lista no tiene Informacion"<<endl;
    }
    else
    {
        cout<<"La informacion de la Lista es:"<<endl;
        Nodo<T> * aux;
        aux = lista->cab;
        int pos = 1;
        while(aux != NULL)
        {
            cout<<"Info "<<pos<<": "<<aux->info<<endl;
            aux = aux->sig;
            pos++;
        }
    }
}

template<typename T>
void insertar(Lista<T> * lista, T infoNueva)
{
    Nodo<T> * nuevo;
    nuevo = new Nodo<T>();
    nuevo->info = infoNueva;
    nuevo->sig = NULL;
    if(lista->tam == 0)
    {
        lista->cab = nuevo;
        lista->tam++;
    }
    else
    {
        Nodo<T> * aux;
        aux = lista->cab;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
        lista->tam++;
    }
}

template<typename T>
bool vacia(Lista<T> * lista)
{
    if(lista->tam == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
int tamano(Lista<T> * lista)
{
    return lista->tam;
}


template<typename T>
T obtenerDato(Lista<T> * lista, int pos)
{
    Nodo<T> * aux;
    aux = lista->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(pos == p)
        {
            return aux->info;
        }
        aux = aux->sig;
        p++;
    }
    Tipo retorno;
    retorno.permiso=false;
    retorno.posi=0;
    return retorno;
}

template<typename T>
Lista<T> * crearLista()
{
    Lista<T> *lista;
    lista = new Lista<T>;
    lista->tam = 0;
    lista->cab = NULL;
    return lista;
}

template<typename T>
bool eliminar(Lista<T> * lista, int pos)
{
    if(lista->tam > pos)
    {
        if(pos == 0)
        {
            Nodo<T> * temp;
            temp = lista->cab;
            lista->cab = temp->sig;
            temp->sig = NULL;
            delete temp;
            lista->tam--;
            return true;
        }
        else
        {
            Nodo<T> * aux;
            aux = lista->cab;
            for(int i=0; i<pos-1; i++)
            {
                aux = aux->sig;
            }
            Nodo<T> * temp;
            temp = aux->sig;
            aux->sig = temp->sig;
            temp->sig = NULL;
            delete temp;
            lista->tam--;
            return true;
        }
    }
    else
    {
        return false;
    }
}
