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
    bool isConexo;
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
    void insertNode(Node<T>* nodo){
        int id = nodo->getId();
        nodos[id] = nodo;
    }
    void removeNode(int id){
        auto deleteNode = (*nodos)[id];
        vector<Edge<T>*> vectemp;
        for(auto it = nodos->cbegin(); it != nodos->cend(); it++){
                auto temp = it->second;
                auto lista = temp->getAristas();
                for(auto it2= lista->cbegin();it2 != lista->cend(); it2++){
                    auto temp2 = *it2;
                    if(temp2->get_To() == deleteNode || temp2->get_From() == deleteNode){
                        vectemp.push_back(temp2);
                    }
                }
                for(int i = 0; i < vectemp.size();i++){
                    lista->remove(vectemp[i]);
                    delete vectemp[i];
                }
                vectemp.clear();
        }
        nodos->erase(id);
        delete deleteNode;
    }
    void Size(){
        cout << nodos->size();
    }
    void printAristas(){
        for(auto it = nodos->cbegin(); it!= nodos->cend();it++){
            auto temp = it->second;
            temp->print_aristas();
            cout << endl;
        }
    }
    Node<T>* buscarVertice(int key){
        auto temp =(*nodos)[key];
            if(temp){
                return (temp);
            }
            else{
                return nullptr;
            }
    }
    Edge<T>* buscarArista(Node<T>* from, Node<T>* to){
        int id= from->getId();
        auto temp1= *nodos;
        auto temp = (temp1)[id];
        if(temp){
            auto lista = temp->getAristas();
            for(auto it = lista->cbegin(); it!= lista->cend();it++){
                auto temp2 = *it;
                auto temp3 =temp2->get_From();
                if(temp2->get_From() == from){
                    return temp2;
                }
            }
        }
        else{
            return nullptr;
        }
        return nullptr;
    }
    bool esconexo(){

    }
    bool fuerteconexo(){

    }

    bool bipartito(){

    }

    ~Graph(){
        for(auto it = nodos->cbegin(); it!=nodos->cend(); it++){

        }
    }
};

#endif
