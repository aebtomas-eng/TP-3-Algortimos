#include <iostream>
#include <string>

#include "tabla_hash.h"
using namespace std;

// Programa para explorar funciones de hash: carga en una TablaHash todos los
// jugadores (distintos) de la entrada estandar y muestra cuantas colisiones
// hubo. La funcion que se prueba es la funcion_hash de funcion_hash.cpp.
//
// Uso: ./explorar_hash < datos/goles.txt

// Prueben tambien con otras capacidades iniciales.
const size_t CAPACIDAD_INICIAL = 8;

int main() {
    // COMPLETAR: crear una TablaHash<std::string, int> con CAPACIDAD_INICIAL.

    std::string jugador;
    TablaHash<string, int> tabla(CAPACIDAD_INICIAL);
    while (std::getline(std::cin, jugador)) {
        if (jugador != "") {
            // En este punto, jugador tiene el nombre de quien hizo el gol.
            // COMPLETAR: si el jugador todavia no esta en la tabla, insertarlo
            // (el valor no importa).
            if (tabla.buscar(jugador) == nullptr) tabla.insertar(jugador,0);
        }
    }

    // COMPLETAR: imprimir la cantidad de claves, la capacidad final y la
    // cantidad de colisiones de la tabla.
    cout << "Claves:" << tabla.cantidad()<< endl;
    cout << "Capacidad final:" << tabla.capacidad()<< endl;
    cout << "Colisiones:" << tabla.colisiones()<< endl;


    return 0;
}
/*
Con 117 claves y 64 buckets hubieron:
|---------------------------------------|
|                            |Colisiones|
|Funcion_hash_basica.        | 64       |
|Funcion_hash_con_memoria    | 64       |
|Funcion_hash_horrible       | 116      |
|---------------------------------------|

-> Elegimos la funcion funcion_hash_con_memoria. En nuestros datos empato con la basica, pero la con memoria tiene en cuenta el orden de las letras. Gracias a esta propiedad, reducimos la posibilidad de colisiones. Se ve, por supesto, que la peor funcion es la funcion: Funcion_hash_horrible.
En las funciones de hash malas vemos que las claves qe colisionan tienen esto en comun
 - En la horrible todas tienen el mismo hash asi que siempre caen el el bucket 0 sin importar el nombre
 - En la basica, colisionan las claves cuyas sumas de caracteres (en ASCII) da el mismo resto mod cap. En particular, los anagrmas tienen el mismo hash.
En nuestro trabajo, todo esta realizado con potencias par y no vemos que esto afecte que tan bueno/malo sea el hash. 
*/

