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
    map<int,Node<T>* > *nodos;
    bool isConexo=false;
    bool isBipartito;
    double densidad;
    int Aristas;
public:
    Graph(){
        nodos = new map<int,Node<T>*>;
        Aristas=0;
    }

    void printGraph(){
        for(auto it = nodos->cbegin() ; it != nodos->cend() ; it++){
            it->second->getAristas()->empty();
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
                        Aristas--;
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
    bool removeEdge(Node<T>* from, Node<T>* to){
        auto temp = buscarArista(from,to);
        if(temp){
            auto temp2 = from->getAristas();
            temp2->remove(temp);
            delete temp;
            Aristas--;
            return true;
        }
        else{
            return false;
        }
    }
    int Size(){
        cout << nodos->size();
    }

    void AumtentarArista(){
        Aristas++;
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
                if(temp2->get_To() == to){
                    return temp2;
                }
            }
        }
        else{
            return nullptr;
        }
        return nullptr;
    }
    
    bool esDigrafo(){
        for (auto it = nodos->begin(); it != nodos->end(); it++) {
            list<Edge<T>*> edges = *(it->second->getAristas());
            for (int i = 0; i < edges.size(); i++) {
                auto id = edges.front()->get_To();
                edges.pop_front();
                if(buscarArista(it->second, id)==nullptr or buscarArista(id,it->second) == nullptr){
                    return false;
                }
            }
        }
        return true ;
    }
    
    bool esconexo(){
        map<int, pair<bool ,bool > > conexodet;
        auto aristas_a = new list<Edge<T>*>;
        for (auto it = nodos->begin(); it != nodos->end() ; ++it) {
            conexodet.insert(pair<int,pair<bool,bool>>(it->first,pair<bool ,bool >(false,false)));
        }
        for (auto it = nodos->begin(); it != nodos->end() ; ++it) {
            Node<T> * ptr = it->second;
            conexodet.at(it->first).first = true;
            if(ptr->getAristas()->empty() or ptr->getAristas()->front()->get_To() == nullptr){
                return false;
            }else {
                *aristas_a = *(ptr->getAristas());
                for (int i = 0; i< aristas_a->size();i++) {
                    int id = aristas_a->front()->get_To()->getId();
                    aristas_a->pop_front();
                    conexodet.at(id).second=true;
                }
            }
        }
        for (auto it = conexodet.begin(); it != conexodet.end() ; it++){
            if(!it->second.first or !it->second.second ){
                return false;
            }
        }
        return true;
    }

    bool fuerteconexo(){

    }
    int get_Aristas(){
        return Aristas;
    }
    bool bipartito(){

    }
    void calculateDensity(){
        auto temp = Size();
        if(temp <= 1){
            densidad = 0;
        }
        else{
            densidad = Aristas/(temp*(temp-1));
        }
    }

    ~Graph(){
        /*for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
            auto temp = it->second;
            auto temp2 = temp->getAristas();
            for(auto i = temp2->cbegin(); i != temp2->cend(); i++){
                delete *i;
            }
        }
        for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
            auto temp = it->second;
            delete temp;
        }
        delete nodos;*/
    }
};

#endif

