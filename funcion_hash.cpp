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
*/