
#ifndef UNTITLED7_EDGE_H
#define UNTITLED7_EDGE_H
#include "nodos.h"

#include <list>

using namespace std;
template <typename A>
class Node;

template <typename E>
class Edge {
private:
    Node<E>* from;
    Node<E>* to;
    double peso;
    bool taken;
public:
    Edge(){
        from = nullptr;
        to = nullptr;
        peso = 0;
        taken = false;
    }
    Edge(Node<E>* _from, Node<E>* _to) {
        from = _from;
        to = _to;
        taken = false;
    }
    void set_taken(){
        taken = true;
    }
    bool get_taken(){
        return taken;
    }
    void setWeight(double x){
        peso = x;
    }
    Node<E>* get_From(){
        return from;
    }
    Node<E>* get_To(){
        return to;
    }
    double getWeight(){
        return peso;
    }
    ~Edge(){
    }
};
#endif
