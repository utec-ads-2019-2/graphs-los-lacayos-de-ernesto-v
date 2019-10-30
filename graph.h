#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#include "Edge.h"
#include <map>
#include <fstream>
#include <iostream>
#include <stack>


template <typename E>
class Node;

template <typename T>
class Graph {
    map<int,Node<T>*>*nodos;
    bool isDigrafo;
    bool isConexo;
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

        }
    }
    map<int,Node<T>*> * get_map(){
        return nodos;
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
        return true;
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

    bool esconexo(){
        map<int, pair<bool ,bool > > conexodet;
        auto aristas_a = new list<Edge<T>*>;
        for (auto it = nodos->begin(); it != nodos->end() ; ++it) {
            conexodet.insert(pair<int,pair<bool,bool>>(it->first,pair<bool ,bool >(false,false)));
        }
        for(auto it = nodos->begin(); it != nodos->end() ; ++it) {
            Node<T> * ptr = it->second;
            conexodet.at(it->first).first = true;
            if(ptr->getAristas()->empty() or ptr->getAristas()->front()->get_To() == nullptr){
                return false;
            }else {
                *aristas_a = *(ptr->getAristas());
                auto temp= *aristas_a;
                for (auto it2 = temp.cbegin(); it2 != temp.cend();it2++) {
                    int id = temp.front()->get_To()->getId();   //->front()->get_To()->getId();
                    temp.pop_front();
                    conexodet.at(id).second=true;
                }
            }
        }
        for(auto it = conexodet.begin(); it != conexodet.end() ; it++){
            if(!it->second.first or !it->second.second ){
                return false;
            }
        }
        return true;
    }

    void insertNode(Node<T>* nodo){
        int id = nodo->getId();
        nodos[id] = nodo;
    }

    bool insertEdge(Node<T>* from, Node<T>* to,double peso){
        if(!buscarArista(from,to)){
            auto temp = buscarVertice(from->getId());
            auto vec = temp->getAristas();
            auto ed = new Edge<T>(from,to);
            ed->setWeight(peso);
            vec->push_back(ed);
            Aristas++;
            return true;
        }
        else{
            return false;
        }
    }

    void DFS(int v, map<int ,bool> & visited) {
        visited[v] = true;
        auto vertice = buscarVertice(v);
        list<Edge<T>*>* ListaTemp = vertice->getAristas();
        for (auto it = ListaTemp->cbegin(); it != ListaTemp->cend(); it++) {
            int visit = ((*it)->get_To()->getId() == v) ? (*it)->get_From()->getId() : (*it)->get_To()->getId();
            if (!visited[visit]) {
                DFS(visit, visited);
            }
        }
    }

    Graph<T> getTranspose() {
        Graph<T> temp;
        for (auto it = nodos->begin(); it != nodos->end() ; ++it) {
            temp.insertNode(it->second);
        }
        for (auto it = nodos->begin(); it != nodos->end() ; ++it){
            for (auto ite = it->second->getAristas()->begin(); ite != it->second->getAristas()->end(); ite++)
                temp.insertEdge((*ite)->get_To(), (*ite)->get_From(), (*ite)->getWeight());

        }
        return temp;
    }

    map<int,Node<T>*>* getNodos() {
        return nodos;
    }

    bool fuerteconexo(){
        if(esconexo()){
            if(esDigrafo()) return true;

            map<int ,bool> visited;
            Graph trans = this->getTranspose();
            for(auto v = trans.getNodos()->begin(); v!= trans.getNodos()->end(); v++){
                    visited[v->first] = false;
            }
            trans.DFS(visited.begin()->first,visited);
            for (auto v : visited) {
                if (!visited.at(v.first)){
                    return false;
                }
            }
            return true;
        }
        return false;
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

