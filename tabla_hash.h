#ifndef TABLA_HASH_H
#define TABLA_HASH_H
#include <vector>
using namespace std;

#include <cstddef>

#include "funcion_hash.h"

// TAD TablaHash<K, V>: tabla de hash con direccionamiento cerrado.
//
// Guarda pares <clave, valor> repartidos en buckets: el par de una clave esta
// en el bucket numero funcion_hash(clave) % capacidad().
//
// Requisitos sobre los tipos:
//   - K: se puede copiar, comparar con == y existe funcion_hash(K).
//   - V: se puede copiar.
//
// Invariante de representacion:
//   COMPLETAR: escriban aca el invariante de la representacion que elijan.
//    .La lista de buckets es un vector de nodos
//    .Cada Nodo guarda tres elementos: (clave,valor,next)
//      Clave es de tipo K, Valor es tipo V y next es un puntero a el siguiente nodo o nullptr
//    .Buckets.size() = capacidad
//    .Capacidad >=1
//    .cant <= FACTOR_DE_CARGA_MAXIMO * cap
//    .Cada nodo esta el bucket[funcion_hash(nodo->clave)%cap]
//    .Si un nodo es el ultimo de su bucket, entonces su next sera nullptr (no hay ciclos)
//    .Todo nodo insertado es un elemento del vector o un hijo de otro nodo
//    .Cada nodo tiene a lo sumo un hijo
//    .No hay claves repetidas
//    
//  
// Complejidades: n es la cantidad de claves guardadas y c la capacidad.
// "Promedio" supone que la funcion de hash reparte las claves de manera
// uniforme y que calcularla (y comparar dos claves) cuesta O(1).

template <typename K, typename V>
class TablaHash {
  private:
  // COMPLETAR: la representacion la eligen ustedes (que guardan, y que hay
  // en cada bucket). Pueden agregar tambien funciones auxiliares privadas.
  // Lo que el Iterador necesite de aca tiene que estar declarado antes que el.
  struct Node {
      Node(const K& c, const V& v) : clave(c), valor(v), next(nullptr) {}
      K clave;
      V valor;
      Node* next;
    };
    void redimensionar_la_wea();
    size_t cap=0;
    size_t cant=0;
    vector<Node*> buckets;

  public:
    static const size_t FACTOR_DE_CARGA_MAXIMO = 2;

    // Pre:  capacidad_inicial >= 1.
    // Post: crea una tabla vacia, con capacidad_inicial buckets.
    // Costo: O(capacidad_inicial).
    TablaHash(size_t capacidad_inicial);

    // Post: libera toda la memoria pedida por la tabla.
    // Costo: O(n + c) en peor caso.
    ~TablaHash();

    // Copiar una tabla copiaria los punteros y no su contenido: lo prohibimos.
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;

    // Pre:  la clave NO esta en la tabla.
    // Post: la tabla tiene ademas el par <clave, valor>, y
    //       cantidad() <= FACTOR_DE_CARGA_MAXIMO * capacidad().
    // Costo: O(1) amortizado (en peor caso O(n), cuando toca redimensionar).
    void insertar(const K& clave, const V& valor);


    // Pre:  la clave esta en la tabla.
    // Post: la tabla ya no tiene la clave (ni su valor).
    // Costo: O(1) en promedio, O(n) en peor caso.
    void eliminar(const K& clave);

    // Pre:  -
    // Post: si la clave esta, devuelve un puntero a su valor (que se puede
    //       usar para leerlo o modificarlo); si no, devuelve nullptr.
    //       El puntero deja de ser valido al insertar o eliminar.
    // Costo: O(1) en promedio, O(n) en peor caso.
    V* buscar(const K& clave);

    // Post: devuelve la cantidad de claves guardadas. Costo: O(1).
    size_t cantidad();

    // Post: devuelve la cantidad de buckets. Costo: O(1).
    size_t capacidad();

    // Post: devuelve la cantidad de claves que comparten bucket con alguna
    //       clave que llego antes, es decir:
    //       cantidad() - (cantidad de buckets que no estan vacios).
    // Costo: O(c) en peor caso.
    size_t colisiones();

    // Iterador de la tabla: recorre todos los pares <clave, valor>, cada uno
    // exactamente una vez, en algun orden (ver TAD Iterador en el enunciado).
    // Deja de ser valido si se inserta o se elimina en la tabla.
    //
    // Invariante de representacion:
    //   COMPLETAR: escriban aca el invariante de la representacion que elijan.
    //   .Cada iterador tiene 3 atributos:
    //      un indice que es size t, un puntero al nodo actual, un puntero a la tablahash
    //   .El puntero siempre apunta a la tabla que llamo crear_iterador
    //   .Si indice == capacidad, el recorrido termino pq el vector va desde 0 hasta cap-1
    //      entonces hay_mas() = false
    //   .Si indice < capacidad, entonces actual apunta a un nodo(!nullptr) del bucket[indice]
    
    class Iterador {
      private:
        // COMPLETAR: la representacion la eligen ustedes. Desde aca se puede
        // usar la parte privada de la tabla.
        // Para que crear_iterador() pueda armar el iterador.
        size_t indice = 0;
        Node* actual = nullptr;
        TablaHash* tabla_it;        
        friend class TablaHash;
        
        public:
        // Pre:  -
        // Post: indica si quedan pares por recorrer.
        // Costo: O(1).
        bool hay_mas() {
            // COMPLETAR
            if (indice>= tabla_it->capacidad()) return false;
            return true;
        }

        // Pre:  hay_mas().
        // Post: devuelve la clave del par actual, sin modificar el iterador.
        // Costo: O(1).
        K clave() {
            // COMPLETAR (reemplazar la linea de abajo)
            return actual->clave;
        }

        // Pre:  hay_mas().
        // Post: devuelve el valor del par actual, sin modificar el iterador.
        // Costo: O(1).
        V valor() {
            // COMPLETAR (reemplazar la linea de abajo)
            return actual->valor;
        }

        // Pre:  hay_mas().
        // Post: el iterador pasa al par siguiente (o al final, si no hay mas).
        // Costo: O(c) en peor caso. Recorrer la tabla entera (crear el
        //        iterador y avanzar hasta el final) cuesta O(n + c).
        void avanzar() {
            if (actual->next==nullptr)
            {
                indice++;
                while (indice < tabla_it->capacidad() && tabla_it->buckets[indice] == nullptr)
                {
                    indice++;
                }
                if (indice< tabla_it->capacidad())
                {
                    actual = tabla_it->buckets[indice];
                }
                return;
            }
            actual=actual->next;   
        }
    };

    // Pre:  -
    // Post: devuelve un iterador al primer par de la tabla (si la tabla esta
    //       vacia, el iterador ya esta al final).
    // Costo: O(c) en peor caso.
    Iterador crear_iterador();

};

// ---------------------------------------------------------------------------
// Implementacion. Al ser una clase template, va en el mismo .h.
// ---------------------------------------------------------------------------

template <typename K, typename V>
TablaHash<K, V>::TablaHash(size_t capacidad_inicial) {
    // COMPLETAR
    buckets.resize(capacidad_inicial);
    cap=capacidad_inicial;
}

template <typename K, typename V>
TablaHash<K, V>::~TablaHash() {
    // COMPLETAR
    Iterador it = crear_iterador();
    while (it.hay_mas()){
        Node* LaVenganzaContraLaxDelNoditoAuxiliarLindoAhoraCriminal = it.actual;
        it.avanzar();
        delete LaVenganzaContraLaxDelNoditoAuxiliarLindoAhoraCriminal;
    }
}

template <typename K, typename V>
void TablaHash<K, V>::redimensionar_la_wea() {
    size_t nueva_cap = cap*2;
    vector<Node*> baldes;
    baldes.resize(nueva_cap);
    Iterador it = crear_iterador();
    while (it.hay_mas())
    {
        size_t indice = funcion_hash(it.actual->clave) % nueva_cap;
        Node* posicion = baldes[indice];
        if (posicion == nullptr)
        {
            baldes[indice] = it.actual;
        }
        else
        {
            while (posicion->next!=nullptr)
            {
                posicion = posicion->next;
            }
            posicion->next=it.actual;
        }
        Node* viejo = it.actual;
        it.avanzar();
        viejo->next = nullptr;
    }
buckets = baldes;
cap=nueva_cap;
}

template <typename K, typename V>
void TablaHash<K, V>::insertar(const K& clave, const V& valor) {
    // COMPLETAR
    size_t indice = funcion_hash(clave) % cap;
    Node* actual = buckets[indice];
    Node* nuevo = new Node(clave, valor);
    if (actual != nullptr)
    {
    while (actual->next!=nullptr)
    {
        actual = actual->next;
    }
    actual->next = nuevo;
    }
    else
    {
        buckets[indice]=nuevo;
    }
    cant++;
    if (cant > FACTOR_DE_CARGA_MAXIMO*cap)
    {
        redimensionar_la_wea();
    }
}

template <typename K, typename V>
void TablaHash<K, V>::eliminar(const K& clave) {
    // COMPLETAR
    size_t indice = funcion_hash(clave) % cap;
    Node* actual = buckets[indice];
    if (actual->clave == clave)
    {
        buckets[indice] = actual->next;
        delete actual;
        cant--;
        return;
    }
    while (actual->next != nullptr)
    {
        Node* viejo = actual;
        actual = actual->next;
        if (actual->clave == clave)
        {
            viejo->next = actual->next;
            delete actual;
            cant--;
            return;
        }
    }
}

template <typename K, typename V>
V* TablaHash<K, V>::buscar(const K& clave) {
    // COMPLETAR
    size_t indice = funcion_hash(clave) % cap;
    Node* actual = buckets[indice];
    if (actual == nullptr)
    {
        return nullptr;
    }
    while (actual->next != nullptr)
    {
        if (actual->clave == clave)
        {
            return &actual->valor;
        }
        else
        {
            actual = actual->next;
        }
    }
    if (actual->clave == clave)
    {
        return &actual->valor;
    }
    
    return nullptr;
}

template <typename K, typename V>
size_t TablaHash<K, V>::cantidad() {
    // COMPLETAR
    return this->cant;
}

template <typename K, typename V>
size_t TablaHash<K, V>::capacidad() {
    // COMPLETAR
    return this->cap;
}

template <typename K, typename V>
size_t TablaHash<K, V>::colisiones() {
    // COMPLETAR
    size_t no_vacios = 0;
    for (size_t i = 0; i < cap; i++)
    {
       if (buckets[i] != nullptr)
       {
        no_vacios++;
       }
    }
    return cant - no_vacios;
}

// El "typename" le avisa al compilador que TablaHash<K, V>::Iterador es un tipo.
template <typename K, typename V>
typename TablaHash<K, V>::Iterador TablaHash<K, V>::crear_iterador()
    {
        Iterador it;
        it.tabla_it = this;
        if (this->cantidad() == 0)
        {
            it.indice = this->capacidad();
            return it;
        }
        Node* primero = this->buckets[0];
        while (primero == nullptr)
        {
            it.indice++;
            primero = this->buckets[it.indice];
        }
        it.actual = primero;
        return it;
    }

#endif
