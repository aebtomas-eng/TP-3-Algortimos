#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    // COMPLETAR
    int suma = 0;
    for (char c : clave) {
        suma += c;
    }
    return suma % tabla.capacidad();
}

size_t funcion_hash(int clave) {
    // COMPLETAR
    
    return clave % tabla.capacidad();
}
