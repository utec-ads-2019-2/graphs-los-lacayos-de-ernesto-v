#ifndef UNTITLED7_NODOS_H
#define UNTITLED7_NODOS_H

#include <list>
#include "string.h"
#include "Edge.h"
using namespace std;
template <typename A>
class Edge;

template <typename E>
class Node {
private:
    E Data;
    char color;
    int id;

public:
    std::list<Edge<E>*>* aristas;
    Node(E valor){
        aristas = new list<Edge<E>*>;
        Data = valor;
        color = 'B';
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
    void print_aristas(){
        for(auto it = aristas->cbegin(); it !=  aristas->cend(); it++){
            auto temp2 = *it;
            cout <<  temp2->getWeight() << " ";
        }
    }
    void setId(int a){
        id = a;
    }
    int getId(){
        return id;
    }
    ~Node(){
        delete aristas;
    }
    char getColor(){
        return color;
    }
    void setColor(char a){
        color = a;
    }
};
#endif
