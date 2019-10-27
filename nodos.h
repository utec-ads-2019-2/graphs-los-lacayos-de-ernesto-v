#ifndef UNTITLED7_NODOS_H
#define UNTITLED7_NODOS_H

#include <list>
#include "string.h"

using namespace std;
template <typename A>
class Edge;

template <typename E>
class Node {
private:
    E Data;
    char color;
public:
    std::list<Edge<E>*>* aristas;
    Node(E valor){
        aristas = new list<Edge<E>*>;
        Data = valor;
    }

    void insertEdge(Edge<E>*to){
        aristas->push_back(to);
    }

    E getData(){
        return Data;
    }
    list<Edge<E>*>* getAristas(){
        return aristas;
    };
};
#endif
