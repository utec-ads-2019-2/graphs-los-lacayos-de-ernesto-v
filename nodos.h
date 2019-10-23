#ifndef UNTITLED7_NODOS_H
#define UNTITLED7_NODOS_H

#include <list>
#include "string.h"
#include "Edge.h"
template <typename A>
class Edge;

template <typename E>
class Node {
private:
    E Data;
    list<Edge<E>*>aristas;
public:
    Node(E valor){
        Data = valor;
    }
    void printNode(){

    }
};
#endif