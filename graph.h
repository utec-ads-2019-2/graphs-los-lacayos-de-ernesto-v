#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#include "Edge.h"
#include <map>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
template <typename E>
class Node;

template <typename T>
class Graph {
    map<int,Node<T>*>*nodos;
    bool isDigrafo;
    bool isConexo;
    bool isBipartito;
    bool fConexto;
    double densidad;
    int Aristas;
public:
    Graph(){
        nodos = new map<int,Node<T>*>;
        Aristas=0;
    }

        map<int,Node<T>*> * get_map(){
        return nodos;
    }

    bool esDigrafo(){
        for (auto it = nodos->cbegin(); it != nodos->cend(); it++) {
            auto edges = it->second->getAristas();
            for (auto it2 = edges->cbegin(); it2 != edges->cend() ; it2++) {
                auto id = (*it2)->get_To();
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
        if(!esDigrafo()){
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
        else
            return false;
    }
    int get_Aristas(){
        if(esDigrafo())
            return Aristas;
        else{
            return Aristas / 2;
        }
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

    map<int,Node<T>*>& getNodos() {
        return *nodos;
    }

    bool fuerteconexo(){
        if(esDigrafo()){
            map<int ,bool> visited;
            auto temp = new Graph;
            for (auto it = nodos->begin(); it != nodos->end() ; ++it) {
                temp->insertNode(it->second);
            }
            for (auto it = nodos->begin(); it != nodos->end() ; ++it){
                for (auto ite = it->second->getAristas()->begin(); ite != it->second->getAristas()->end(); ite++)
                    temp->insertEdge((*ite)->get_To(), (*ite)->get_From(), (*ite)->getWeight());

            }
            for(auto v = temp->getNodos().begin(); v != temp->getNodos().end(); v++)
                visited.insert({v->first, false});
            temp->DFS(visited.begin()->first,visited);
            for (auto v : visited) {
                if (!visited.at(v.first)){
                    return false;
                }
            }
            return true;
        }
        return isConexo;
    }


    Graph <T> Prim (int key){
        auto nodo = buscarVertice(key);
        if(nodo){
            if(!esDigrafo()) {
                cout << "El orden de las aristas es: ";
            vector<Node<T>*> a;
            auto newgraph = new Graph<T>;
            for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
                auto newnode = new Node<T>(it->second);
                newgraph->insertNode(newnode);
            }
            for(int i = 0; i < nodos->size(); i++){
                   a.push_back(nodo);
                   auto ed = findMin(a);
                   if(ed){
                       ed->set_taken();
                       auto temp = buscarArista(ed->get_To(),ed->get_From());
                       temp->set_taken();
                       auto nodo_to = newgraph->buscarVertice(ed->get_To()->getId());
                       auto nodo_from = newgraph->buscarVertice(ed->get_From()->getId());
                       cout << "{ " << nodo_from->getId() << " , " << nodo_to->getId() << " } ";
                       newgraph->insertEdge(nodo_from,nodo_to,ed->getWeight());
                       newgraph->insertEdge(nodo_to,nodo_from,ed->getWeight());
                       if(in(a,ed->get_To()))
                           nodo = ed->get_From();
                       else
                           nodo = ed->get_To();
                   }
                   else{
                       break;
                   }
            }
            cout << endl;
            return *newgraph;
        }
        else{
                cout << "El grafo es direccionado; se necesita un Grafo no direccionado";
            throw new out_of_range("El grafo es direccionado; se necesita un Grafo no direccionado");

            }
        }
        else{
            cout << "El nodo ingresado no existe";
            throw new out_of_range("El nodo ingresado no existe");
        }
    }
    void mapkrus(map<int, Node<T>*>*mapa, Node<T>* node){
        if(id_null(mapa,node) == true) {
            mapa->erase(node->getId());
            mapa->insert(pair<int, Node<T>*>(node->getId(),node));
        }
    }
    bool id_null(map<int, Node<T>*>* mapa, Node<T>* node){
        if(mapa->operator[](node->getId()) == nullptr)
            return true;
        else
            return false;
    }

    Graph <T> kruskal(){
        if(!esDigrafo()){
            auto edges_sort = new list<Edge<T>*>;
            auto *graphkruskal = new Graph;
            auto mapeo_for_krus = graphkruskal->get_map();
            for(auto it = nodos->begin(); it != nodos->end() ; it++){
                Node<T>* ite = it->second;
                for(auto temp_edges = ite->getAristas()->begin(); temp_edges !=ite->getAristas()->end(); temp_edges++ ){
                    if (edges_sort->size()==0){
                        edges_sort->push_back(*temp_edges);
                    }else{
                        int ctrl=0;
                        auto it_temp = edges_sort->begin();
                        while((edges_sort->size()> ctrl) && ((*it_temp)->getWeight()>(*temp_edges)->getWeight()) ){
                            ctrl++;
                            it_temp++;
                        }
                        edges_sort->insert((it_temp),(*temp_edges));
                    }
                }
            }
            do {
                auto node_to = new Node<T>(edges_sort->back()->get_To());
                auto node_from = new Node<T>(edges_sort->back()->get_From());
                node_to->setId(node_to->getId());
                node_from->setId(node_from->getId());
                auto newed = buscarArista(edges_sort->back()->get_From(), edges_sort->back()->get_To());
                edges_sort->pop_back();
                node_to->getAristas()->clear();
                node_from->getAristas()->clear();
                if(id_null(mapeo_for_krus,node_from)==true or id_null(mapeo_for_krus,node_to)==true){
                    mapkrus(mapeo_for_krus,node_from);
                    mapkrus(mapeo_for_krus,node_to);
                    cout << "{ " << node_from->getId() << " , " << node_to->getId() << " } ";
                    graphkruskal->insertEdge(node_from,node_to,newed->getWeight());
                    graphkruskal->insertEdge(node_to,node_from,newed->getWeight());
                }
            }while(edges_sort->size() > 0);
            return *graphkruskal;
        }
        else{
            cout<<"No se puede construir";
            throw new out_of_range("No se  puede construir");
        }
    }
    void getProperties(){
        isConex();
        bipartito();
        calculateDensity();
        esDigrafo();
        //fConexto = fuerteconexo();

        if(isDigrafo){
            cout << "Es un Grafo dirigido" << endl;
        }
        else {
            cout << "Es un grafo no dirigido" << endl;
        }
        if(fConexto)
            cout << "Es fuerteconexo"<< endl ;
        else
            cout << "No es fuertemente conexo" << endl;
        if(isConexo)
            cout << "Es un Grafo conexo" << endl;
        else
            cout << "Es un grafo no conexo" << endl;
        if(isBipartito)
            cout << "Es Bipartito " << endl;
        else
            cout << "No es Bipartito" << endl;
        if( 1 >= densidad && densidad >= 0.6){
            cout << "Es un Grafo denso" << endl;}
        else if( 0 <= densidad && densidad < 0.6)
            cout << "Es un grafo disperso" << endl;
    }

    vector <Node<T>*>*  BFS (int start){
            auto vec = new vector<Node<T>*>;
            setNodesBlank();
            auto s = (*nodos)[start];
            queue<Node<T>*> a;
            a.push(s);
            vec->push_back(s);
            s->setColor('T');
            while(!a.empty()) {
                Node<T>* v = a.front();
                a.pop();
                auto ed = v->getAristas();
                for(auto it = ed->cbegin() ; it != ed->cend(); it++){
                    auto to = (*it)->get_To();
                    if(to->getColor()== 'B'){
                        a.push(to);
                        vec->push_back(to);
                        to->setColor('T');
                    }
                }
            }
        return vec;
    }

    Graph<T>* Dijsktra(int key){
        setNodesBlank();
        auto newGraph = new Graph<T>;
        map<Node<T>*,Node<T>*> llegadas;
        vector<pair<Node<T>*,double>> vec;
        for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
            auto newNode = new Node<T>(it->second);
            llegadas[newNode] = nullptr;
            newGraph->insertNode(newNode);
        }
        for(auto it = nodos->cbegin(); it != nodos->cend(); it++){
            pair<Node<T>*,double> p;
            p.first = it->second;
            if(it->first != key)
                p.second = INFINITY;
            else
                p.second = 0;
            vec.push_back(p);
        }
        auto temp = buscarVertice(key);
        double cont = 0;
        for(int i = 0; i < nodos->size() ; i++){
            temp->setColor('m');
            for(auto j = 0; j < vec.size(); j++){
                auto ida = vec[j].first;
                if(ida->getColor() == 'B'){
                    auto arista = buscarArista(temp, ida);
                    if (arista) {
                        double val = cont + arista->getWeight();
                        if ((vec[j]).second > val) {
                            auto x = newGraph->buscarVertice(temp->getId());
                            auto y = newGraph->buscarVertice((vec[j]).first->getId());
                             newGraph->insertEdge(x,y,val-cont);
                             if(llegadas[y]){
                                 newGraph->removeEdge(llegadas[y],y);
                             }
                             llegadas[y]= x;
                            (vec[j]).second = val;
                        }
                    }
                }
            }
            pair<Node<T>*,double> temporal;
            temporal.second = INFINITY;
            for(auto it = vec.cbegin(); it != vec.cend(); it++) {
                auto next = (*it).first;
                if (next->getColor() == 'B') {
                    if ((*it).second < temporal.second) {
                        temporal.second = (*it).second;
                        temporal.first = (*it).first;
                    }
                }
            }
            temp = temporal.first;
            cont = temporal.second;

        }
        cout << "El nodo con key: " << key << " LLEGA A: " << endl;
        for(auto it = vec.cbegin(); it != vec.cend(); it++){
            cout << (*it).first->getId() << " CON PESO " << (*it).second << endl;
        }
        return newGraph;
    }

    Graph <T> * BellmanFord(int key){
        setNodesBlank();
        auto newGraph = new Graph<T>;
        vector<Node<T>*> res;
        map<Node<T>*,double> val;
        map<Node<T>*,Node<T>*> llegadas;
        for(auto it = nodos->cbegin() ; it != nodos->cend(); it++){
            res.push_back(it->second);
            val[it->second] = INFINITY;
            llegadas[it->second] = nullptr;
        }

        auto temp = buscarVertice(key);
        val[temp] = 0;
        temp->setColor('m');
        bool cambio=true;
        for(auto it = nodos->cbegin(); it!= nodos->cend() ; it++){
            newGraph->insertNode(new Node<T>(buscarVertice(it->first)));
        }
        while(cambio) {
            cambio = false;
            for (auto it = res.cbegin(); it != res.cend(); it++) {
                auto temp2 = *it;
                if (temp2->getColor() == 'm') {
                    auto aris = temp2->getAristas();
                    for (auto it2 = aris->cbegin(); it2 != aris->cend(); it2++) {
                        auto nodeFROM = (*it2)->get_From();
                        auto nodeTO = (*it2)->get_To();
                        auto a = val[nodeTO];
                        //comparando si es más corto
                        if (val[nodeFROM] + (*it2)->getWeight() < val[nodeTO]) {
                            llegadas[nodeTO] = nodeFROM;
                            val[nodeTO] = val[nodeFROM] + (*it2)->getWeight();
                            nodeTO->setColor('m');
                            cambio = true;
                        }
                    }
                }
            }
        }

        cout << "El nodo con key "  << key << " llega a : " <<endl;
        for(auto it = nodos->cbegin(); it!=nodos->cend() ; it++ ){
            cout << it->second->getId() << " con peso : " << val[it->second] << endl;
        }
        for(auto it = llegadas.cbegin() ; it != llegadas.cend() ; it++) {
            Node<T>* NodeTo = it->first;
            Node<T>* NodeFrom = it->second;
            if(NodeFrom) {
                auto oriArista = buscarArista(NodeFrom, NodeTo);
                newGraph->insertEdge(buscarVertice(NodeFrom->getId()), buscarVertice(NodeTo->getId()),
                                     oriArista->getWeight());
            }
        }
        return newGraph;
    }
    double calculateDensity(){
        auto temp = Size();
            if(temp <= 1){
                densidad = 0;
            }
            else{
                densidad = Aristas/float((temp*(temp-1)));
            }
        return densidad;
    }

    ~Graph(){
        for(auto it = nodos->cbegin(); it!= nodos->cend(); it++){
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
        delete nodos;
    }
};

#endif
