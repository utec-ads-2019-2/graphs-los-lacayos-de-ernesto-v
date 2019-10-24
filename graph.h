#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H

#include "Edge.h"
#include "nodos.h"
#include <map>
#include <fstream>
#include "Airports.h"
#include <iostream>

template <typename E>
class Node;

template <typename T>
class Graph {
    map<int,Node<T>*>*nodos;

public:
    Graph(){
        nodos = new map<int,Node<T>*>;
    }

    void printGraph(){
        for(auto it = nodos->cbegin() ; it != nodos->cend() ; it++){
        }
    }
    map<int,Node<T>*> * get_map(){
        return nodos;
    }
    void insertNode( Aeropuerto *nuevoaeropuerto){

        for(auto it = nodos->cbegin() ; it != nodos->cend();it++){
            Graph::get_map()->get_allocator();
            
        }
    }

    void deleteNode(int id , Node<T>* nodo){
        nodos[id]= nodo;
    }
};


#endif
