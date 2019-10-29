#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#include "Edge.h"
#include <map>
#include <limits.h>
#include <fstream>
#include <iostream>

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
    void insertNode(Node<T>* nodo){
        int id = nodo->getId();
        (*nodos)[id] = nodo;
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
        return nodos->size();
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
    bool isConex(){
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
    bool fuerteconexo(){

    }
    int get_Aristas(){
        return Aristas;
    }
    void setNodesBlank(){
        for(auto it  = nodos->cbegin(); it!= nodos->cend(); it++){
            auto temp = it->second;
            temp->setColor('B');
        }
    }
    bool bipartito(){
        setNodesBlank();
        for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
            auto temp = it->second;
            if(temp->getColor() == 'B'){
                char color = 'A';
                auto temp2 = temp->getAristas();
                for(auto it = temp2->cbegin(); it!= temp2->cend() ; it++){
                    if((*it)->get_To()->getColor() == 'A'){
                        color = 'R';
                    }
                }
                if(!Biparticion(temp,color))
                    return false;
            }
        }
        return true;
    }

    bool Biparticion(Node<T>*a,char color){
        a->setColor(color);
        vector<Node<T>*>newvec;
        auto temp = a->getAristas();
        for(auto it = temp->cbegin(); it!= temp->cend(); it++){
               auto nodo = (*it)->get_To();
               if(nodo->getColor() == 'B'){
                   newvec.push_back(nodo);
               }
               else if(nodo->getColor() == color){
                   return false;
               }
        }
        if(newvec.size()== 0){
            return true;
        }
        if(color == 'A'){
            for(int i = 0; i < newvec.size(); i++){
               if(!Biparticion(newvec[i],'R'))
                   return false;
            }
        }
        else if(color == 'R'){
            for(int i = 0; i < newvec.size(); i++){
                if(!Biparticion(newvec[i],'A'))
                    return false;
            }
        }
        return true;
    }

    bool inVec(Edge<T>* a,vector<Node<T>*> vec){
        auto temp = a->get_To();
        auto temp2 = a->get_From();
        bool x = false;
        bool y = false;
        for(int i = 0; i<vec.size(); i++){
            Node<T>* nodo = vec[i];
            if(temp == nodo)
                x = true;
            if(temp2 == nodo)
                y = true;
        }
        return x&&y;
    }
    Edge<T>* findMin(vector<Node<T>*> vec){
        int s = vec.size();
        if(s == 0 || s == nodos->size()){
            return nullptr;
        }
        auto min = new Edge<T>;
        auto del = min;
        min->setWeight(INT16_MAX);
        for(auto it = vec.cbegin(); it!= vec.cend(); it++){
            auto temp = *it;
            auto lista = temp->getAristas();
            for(auto it = lista->cbegin(); it!= lista->cend(); it++){
                auto temp2 =(*it);
                if(!temp2->get_taken()&& temp2->getWeight()<min->getWeight()){
                    if(!inVec(temp2,vec)){
                        min = temp2;
                    }
                }
            }
        }
        return min;
    }

    bool in(vector<Node<T>*>a,Node<T>* b){
        for(auto it = a.cbegin(); it!= a.cend();it++){
            if(*it == b)
                return true;
        }
        return false;
    }
    Graph <T> Prim (){
        if(!isDigrafo) {
            vector<Node<T> *> a;
            Graph<T> newgraph;
            for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
                auto newnode = new Node<T>(it->second);
                newgraph.insertNode(newnode);
            }
            auto nodo = nodos->cbegin()->second;
            for(int i = 0; i < nodos->size(); i++){
                   a.push_back(nodo);
                   auto ed = findMin(a);
                   if(ed){
                       //marco las aristas
                       ed->set_taken();
                       auto temp = buscarArista(ed->get_To(),ed->get_From());
                       temp->set_taken();

                       //inserto las aristas en el nuevo grafo
                       auto nodo_to = newgraph.buscarVertice(ed->get_To()->getId());
                       auto nodo_from = newgraph.buscarVertice(ed->get_From()->getId());
                       newgraph.insertEdge(nodo_from,nodo_to,ed->getWeight());
                       newgraph.insertEdge(nodo_to,nodo_from,ed->getWeight());
                       if(in(a,ed->get_To()))
                           nodo = ed->get_From();
                       else
                           nodo = ed->get_To();
                   }
                   else{
                       break;
                   }
            }
            return newgraph;
        }
        else{
            cout << "El grafo es direccionado; se necesita un Grafo no direccionado";
            exit(100);
        }
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
