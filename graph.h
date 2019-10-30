#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#include "Edge.h"
#include <map>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "disjointset.h"

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
    void printEdge(double peso){
        auto temp = buscarArista();
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
                    isDigrafo = true;
                    return true;
                }
            }
        }
        isDigrafo = false;
        return false;
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
                isConexo = false;
                return false;
            }
        }
        isConexo =true;
        return true;
    }
    void DFS(int v, map<int ,bool> visited) {
        visited[v] = true;
        auto vertice = (*nodos)[v];
        auto ListaTemp = vertice->getAristas();
        for (auto it = ListaTemp->begin(); it != ListaTemp->end(); it++) {
            int visit = ((*it)->get_To()->getId() == v) ? (*it)->get_From()->getId() : (*it)->get_To()->getId();
                if(!visited[visit])
                    DFS(visit, visited);
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

    map<int,Node<T>*>& getNodos() {
        return *nodos;
    }

    bool fuerteconexo(){
        if(isConex()){
            if(!esDigrafo()){
                return true;
            }
            map<int ,bool> visited;
            Graph trans = this->getTranspose();
            for(auto v = trans.getNodos().begin(); v != trans.getNodos().end(); v++)
                visited.insert({v->first, false});

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
                if(!Biparticion(temp,color)){
                    isBipartito = false;
                    return false;}
            }
        }
        isBipartito = true;
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
        }
    }

    void mapkrus(map<int, Node<T>*>* mapa, Node<T>* node){
        if(!mapa->operator[](node->getId())) {
            mapa->erase(node->getId());
            mapa->insert(pair<int, Node<T>*>(node->getId(),node));
        }
        else
            return;
    }
    bool id_null(map<int, Node<T>*>* mapa, Node<T>* node){
        if(mapa->operator[](node->getId()))
            return true;
        else
            return false;
    }

    Graph <T> kruskal(){
        if(!isDigrafo){
            //multimap<list<Edge<T>*>*,pair<T,T>> edges_sort ;
            list<Edge<T>*>* edges_sort = new list<Edge<T>*>;
            auto *graphkruskal = new Graph;
            map<int , Node<T>*>* mapeo_for_krus = graphkruskal->get_map();
            for(auto it = nodos->begin(); it != nodos->end() ; it++){
                auto temp1 = it->second;
                for(auto temp_edges = it->second->getAristas()->begin(); temp_edges !=it->second->getAristas()->end(); temp_edges++ ){
                    if (!edges_sort->size()){
                        edges_sort->push_back(*temp_edges);
                    }else{
                        int ctrl=0;
                        for(auto it_temp = edges_sort->begin();it_temp != edges_sort->end() ; it_temp++) {
                            if((*it_temp)->getWeight() < (*temp_edges)->getWeight() && edges_sort->size()<ctrl){
                                edges_sort->insert(it_temp,(*temp_edges));
                                break;
                            }
                            ctrl++;
                        }

                    }
                }
            }
            do{
                auto node_to = new Node<T>(edges_sort->back()->get_To());
                auto node_from = new Node<T>(edges_sort->back()->get_From());
                node_to->setId(node_to->getId());
                node_from->setId(node_to->getId());
                node_to->getAristas()->clear();
                node_from->getAristas()->clear();
                edges_sort->pop_back();
                if(!id_null(mapeo_for_krus,node_from) || !id_null(mapeo_for_krus,node_to)){
                    mapkrus(mapeo_for_krus,node_from);
                    mapkrus(mapeo_for_krus,node_to);
                    graphkruskal->insertEdge(node_from,node_from,edges_sort->size());
                    graphkruskal->insertEdge(node_to,node_to,edges_sort->size());
                }
            }
            while(edges_sort->size()!=0);
            /*for(auto it = nodos->cbegin(); it != nodos->cend() ; ++it){
                Node<T>* it_nod = it->second;
                auto new_nodo = new Node<T>((it)->second);
                auto edges = (*it).second->getAristas();
                disjoinset.makeset(new_nodo);
                for(auto it_edges = edges->begin() ; it_edges != edges->end(); it_edges++){
                    edges_sort.insert({(*it_edges)->getWeight, make_pair((*it_edges)->get_From()->getData(), (*it_edges)->get_To()->getData())});
                }
            }*/

            /*for(auto it_sort = edges_sort->cbegin() ; it_sort!= edges_sort->cend() ; it_sort++){
                if(disjoinset.Find_Node((it_sort->second)->get_From()->getData()) != disjoinset.Find_Node(it_sort->second->get_From()->getData())){
                    graphkruskal->insertEdge(it_sort->second.first , it_sort->second.second , it_sort->first);
                    disjoinset.Union(it_sort->second.first , it_sort->second.second );
                }
            }*/
            return *graphkruskal;
        }else{
            cout<<"No s epuede construir";
        }
    }

    void getProperties(){
        isConex();
        bipartito();
        calculateDensity();
        esDigrafo();
        if(isDigrafo)
            cout << "Es un Grafo dirigido" << endl;
        else
            cout << "Es un grafo no dirigido" << endl;
        if(isBipartito)
            cout << "Es Bipartito " << endl;
        else
            cout << "No es Bipartito" << endl;
        if( 1 > densidad >= 0.6)
            cout << "Es un Grafo denso" << endl;
        else if( 0 < densidad < 0.6)
            cout << "Es un grafo disperso" << endl;
        if(isConexo)
            cout << "Es un Grafo conexo" << endl;
        else
            cout << "Es un grafo no conexo" << endl;
        if(fuerteconexo())
            cout << "Es fuerteconexo"<< endl ;
        else
            cout << "No es fuertemente conexo";

    }
    
    double calculateDensity(){
        auto temp = Size();
        if(temp <= 1){
            densidad = 0;
        }
        else{
            densidad = Aristas/(temp*(temp-1));
        }
        return densidad;
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
