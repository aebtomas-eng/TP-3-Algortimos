#include "goleadores.h"
#include <vector>
using namespace std;
#include <iostream>

Goleadores::Goleadores() {
    // COMPLETAR (si hace falta)
}

void Goleadores::anotar_gol(const std::string& jugador) {
    // COMPLETAR
    int goles = 0;
    if(goles_por_jugador.pertenece(jugador)){
        goles = goles_por_jugador.obtener(jugador) +1;
    }
    else goles = 1; 
    goles_por_jugador.insertar(jugador, goles);
    if (goles_por_jugador.cantidad() ==1) maximo = jugador;
    else{
        int goles_maximos = goles_por_jugador.obtener(maximo);
        if (goles>goles_maximos) maximo = jugador;
    } 
}

int Goleadores::goles(const std::string& jugador) {
    // COMPLETAR
    if(!goles_por_jugador.pertenece(jugador)) return 0;
    return goles_por_jugador.obtener(jugador);
}

size_t Goleadores::cantidad_de_jugadores() {
    // COMPLETAR
    return goles_por_jugador.cantidad();
}

std::string Goleadores::maximo_goleador() {
    // COMPLETAR
    return maximo;
}

//Implementacion: decimos que lista[0..n-1] es un heap
bool por_goles = false;
// Pre: -
//Post: devuelve un vector con las claves del diccionario 
vector<string> armar_vector(Diccionario<string, int>& dic) {
    vector<string> lista; 
    Diccionario<string,int>:: Iterador it = dic.crear_iterador();
    while(it.hay_mas()){
        lista.push_back(it.clave());
        it.avanzar();
    }
    return lista;
}
//Pre: i>=0
//Post: devuelve la posicion del hijo izquierdo
int izq(int i){
    return 2*i+1;
}
//Pre: i>=0
//Post: devuelve la posicion del hijo derecho
int der(int i){
    return 2*i+2;
}

//Pre:-
//Post: devuelve true si a<b
bool comparar(string& a, string& b, Goleadores& g){
    if (por_goles && g.goles(a) !=g.goles(b)){
        return g.goles(a) > g.goles(b);
    }
    size_t i =0;
    while(i<a.size() && i<b.size()){
        char letra_a = a[i];
        char letra_b = b[i];
        if (letra_a != letra_b) return letra_a < letra_b;
        i++;
    }
    return a.size() < b.size();
}
//Pre: 0<=n, 0< i<n
//Post:  i cumple la propiedad de heap
void bajar(vector<string>& lista, int n, int i, Goleadores& g){
    while (izq(i) < n) {
    int m = izq(i);
    if (der(i)<n && comparar(lista[m], lista[der(i)],g)) m = der(i);
    if (!comparar(lista[i], lista[m],g)) return;
    swap(lista[i], lista[m]);
    i=m;
    }
}
//Pre: -
// Post lista cumple la propiedad del heap
void heapify(vector<string>& lista, int n, Goleadores& g){
    for (int i =n/2-1; i>=0;i--){
        bajar(lista,n,i,g);
    }
}
//Pre: 0<=n
// Post:ordena una lista
void heapsort(vector<string>& lista, int n, Goleadores& g){
    heapify(lista,n,g);
    for (int fin = n-1; fin>=1; fin--){
        swap(lista[0], lista[fin]);
        bajar(lista, fin,0,g);
    }
}

void Goleadores::imprimir_por_nombre() {
    // OPTATIVO
    vector<string> lista = armar_vector(goles_por_jugador);
    int n = lista.size();
    heapsort(lista, n, *this);
    for(int i=0; i< n; i++){
        cout<< lista[i] << ": "<< goles(lista[i]) <<endl;
    }
}

void Goleadores::imprimir_por_goles() {
    // OPTATIVO
    por_goles = true;
    imprimir_por_nombre();
    por_goles =false;
}
