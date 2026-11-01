#include <iostream>
#include <string>
#include "goleadores.h"
using namespace std;

// Cambiar a true si hicieron la parte optativa (los dos listados).
const bool CON_LISTADOS = true;

// Lee de la entrada estandar la lista de goles del grupo (un gol por linea:
// el nombre del jugador que lo hizo) e imprime el resumen.
//
// Uso: ./goleadores < datos/ejemplo.txt
int main() {
    // COMPLETAR: crear la estructura donde se van a cargar los goles.
    Goleadores g; 
    std::string jugador;
    while (std::getline(std::cin, jugador)) {
        if (jugador != "") {
        // En este punto, jugador tiene el nombre de quien hizo el gol.
        // COMPLETAR: anotarle el gol.
           g.anotar_gol(jugador);
        }
    }
    cout << "Jugadores con goles: " << g.cantidad_de_jugadores() <<endl;
    string maximo = g.maximo_goleador();
    cout << "Maximo goleador: " << g.maximo_goleador() <<" (" << g.goles(maximo)<< "goles)"  <<endl;
            

    // COMPLETAR: imprimir, con el formato del enunciado, la cantidad de
    // jugadores con goles y el maximo goleador (con sus goles).

    if (CON_LISTADOS) {
        std::cout << std::endl;
        std::cout << "Goleadores por nombre:" << std::endl;
        g.imprimir_por_nombre();
        // OPTATIVO: imprimir el listado por nombre.
        std::cout << std::endl;
        std::cout << "Goleadores por goles:" << std::endl;
        // OPTATIVO: imprimir el listado por goles.
        g.imprimir_por_goles();
    }

    return 0;
}
