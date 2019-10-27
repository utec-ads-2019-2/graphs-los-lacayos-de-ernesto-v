#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#include "Edge.h"
#include <map>
#include <fstream>
#include <iostream>

template <typename E>
class Node;

template <typename T>
class Graph {
    map<int,Node<T>*>*nodos;
    bool isDigrafo;
public:
    Graph(){
        nodos = new map<int,Node<T>*>;
    }

    void printGraph(){
        for(auto it = nodos->cbegin() ; it != nodos->cend() ; it++){
            cout<<nodos<<endl;
        }
    }
    map<int,Node<T>*> * get_map(){
        return nodos;
    }

    void removeNode(int id){
        for(auto it = nodos->cbegin(); it != nodos->cend(); it++){
                auto temp = it->second;
                auto lista = temp->getAristas();
                for(auto it2= lista->cbegin();it2 != lista->cend(); it2++){
                }
        }
    }
    void insertNode(Node<T>* nuevo_nodo){
        nodos->insert(nuevo_nodo);
    }
    bool buscarvertice(Node<T>* elvertice){}

    bool buscararista(Node<T>* laarista){}

    bool esconexo(T grafo){}

    bool fuerteconexo(T grafo){}

    bool bipartito(T grafo){}

};

#endif
