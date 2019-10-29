
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include "Airports.h"
#include "graph.h"
#include <cmath>

using pareja = pair <int,Node<Aeropuerto*>*>;
Edge<Aeropuerto*>* getEdge(Node<Aeropuerto*>* _from, Node<Aeropuerto*>* _to){
    auto ed = new Edge<Aeropuerto*>(_from,_to);
    auto lat1 = _from->getData()->getLatitude();
    auto long1 =  _from->getData()->getLongitude();
    auto lat2 = _to->getData()->getLatitude();
    auto long2 =  _to->getData()->getLongitude();
    auto peso =  12742*asin(sqrt(pow(sin((lat2-lat1)*(M_PI/180)/2),2) + pow(sin((long2-long1)*(M_PI/180)/2),2) * cos(lat1*M_PI/180) * cos(lat2*M_PI/180)));;
    ed->setWeight(peso);
    return ed;
}

Graph<Aeropuerto*> buildGraph(string a){
    auto* graf = new Graph<Aeropuerto*>;
    auto mapa = graf->get_map();
    ifstream ifs(a);
    if (ifs.fail()){cout<<"error"<<endl; exit(-1);}
    json json1 =json::parse(ifs);
    json file = std::move(json1);
    for(int i = 0; i <  file.size(); i++){
        json json2 = file[i];
        auto* temp = new Aeropuerto(json2);
        auto* nodo = new Node<Aeropuerto*>(temp);
        nodo->setId(temp->get_Id());
        mapa->insert(pareja(temp->get_Id(),nodo));
    }
    auto map = *mapa;
    for(auto it=mapa->cbegin(); it!=mapa->cend(); it++){
        auto temp = it->second;
        auto vec = temp->getData()->get_destinos();
        for(int i = 0; i < vec->size(); i++){
            auto id = (*vec)[i];
            if(map[id]){
               auto newEdge = getEdge(temp,(*mapa)[id]);
               temp->insertEdge(newEdge);
               graf->AumtentarArista();
            }
        }
    }
    return *graf;
}

void print(Graph<Aeropuerto*> pa){
    auto temp = pa.get_map();
    for(auto it= temp->cbegin(); it!= temp->cend(); it++){
        it->second->getData()->print();
    }
}

