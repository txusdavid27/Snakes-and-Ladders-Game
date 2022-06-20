#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/**
    *@struct Nodo
    *@brief Representa el Nodo de las Listas que vamos a crear de tipo T.
    *@var [Nodo<T>*] sig: Es decir un apuntador a otro Nodo.
    *@var [T] info: Es decir la información que almacenan las listas.
*/
template<typename T>
struct Nodo
{
    Nodo<T> * sig;
    T info; //Esta es la informacion de la lista
};

/**
    *@struct Lista
    *@brief Identifica los atributos de una lista: el comienzo de la Lista o primer apuntador y el tamaño de la lista.
    *@var [Nodo<T>*] cab: Es decir , la cabeza de la Lista o apuntador al primer Nodo.
    *@var [int] tam: Es decir el tamaño de la Lista.
*/
template<typename T>
struct Lista
{
    Nodo<T> * cab;
    int tam;
};

/**
    *@struct Tipo
    *@brief Representa los tipos de datos que van a ser utilizados en cada Lista.
    *@var [int] posi: La posición del jugador en el Tablero.
    *@var [bool] permiso: Si saco 3 veces 6 (carcel o no), permiso para seguir.
    *@var [int] proxiForma: Posición indicada para subir o bajar.
    *@var [int] forma: Número de la casilla.
    *@var [char*] trampa: Nombre de la escalera o serpiente.
*/
struct Tipo///Jugador y Tablero.
{
    int posi;
    bool permiso;
    //-------------
    int proxiForma;
    int forma;
    char* trampa=new char[2];
};
///Extras:
void saludo();
void titulo(int);
int pedirCant();
int menu(int);
void esperar();

///Juego:
template<typename T>
int juego(Lista<T>*,int, Lista<T> *);
template<typename T>
void llenarPista(Lista<T>*, int, Lista<T> *);
template<typename T>
void inicializar(Lista<T>*, int, Lista<T> *);
template<typename T>
void imprimir_pista(Lista<T>*, int, Lista<T> *);
//Lista_Jugadores:
template<typename T>
void indicar_posiactual(int, Lista<T> *);
template<typename T>
Lista<T>* actualizar_posi(Lista<T>*, int, int);
template<typename T>
Lista<T>* actualizar_permiso(Lista<T>*, int, bool);
//Lista_Tablero:
template<typename T>
Lista<T>* actualizar_forma(Lista<T>*, int, int);
template<typename T>
Lista<T>* actualizar_proxiForma(Lista<T>*, int, int);
template<typename T>
Lista<T>* actualizar_trampa (Lista<T>*, int, char* );

///TAD:
template<typename T>
Lista<T> *crearLista();
template<typename T>
void imprimir(Lista<T> *);
template<typename T>
void insertar(Lista<T> *, T); //Este metodo cambia segun el tipo de dato de la informacion de la lista
template<typename T>
bool vacia(Lista<T> *);
template<typename T>
int tamano(Lista<T> *);
template<typename T>
T obtenerDato(Lista<T> *, int);
template<typename T>
bool eliminar(Lista<T> *, int);
template<typename T>
void destruirLista(Lista<T> *);


#endif // FUNCIONES_H_INCLUDED
