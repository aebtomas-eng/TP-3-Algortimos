#include "funcion_hash.h"

size_t funcion_hash_basica(const std::string& clave) {
    // COMPLETAR
    size_t suma = 0;
    for (char c : clave) {
        suma += c;
    }
    return suma;
}
//Claves:117
//Capacidad final:64
//Colisiones:64

size_t funcion_hash_horrible(const std::string& clave) {
    // La mas vaga
    return 0;
}
//Claves:117
//Capacidad final:64
//Colisiones:116

//Funcion hash con memoria
size_t funcion_hash(const std::string& clave) {
    // Evita muchos anagramas caigan en el mismo lugar 
    // ej: BE = 2+5x2 = 12, EB = 5+2x5 = 15
    size_t suma = 0;
    size_t anterior = 1; 
    for (char c : clave) { 
        suma += anterior*c;
        anterior = c;
    }
    return suma;
}
//Claves:117
//Capacidad final:64
//Colisiones:64

size_t funcion_hash(int clave) {
    // COMPLETAR
    
    return clave;
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