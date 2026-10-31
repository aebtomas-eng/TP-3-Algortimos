#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    // COMPLETAR
    size_t suma = 0;
    for (char c : clave) {
        suma += c;
    }
    return suma;
}
size_t funcion_hash_horrible(const std::string& clave) {
    // La mas vaga
    return 0;
}
size_t funcion_hash_con_memoria(const std::string& clave) {
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

size_t funcion_hash(int clave) {
    // COMPLETAR
    
    return clave;
}
