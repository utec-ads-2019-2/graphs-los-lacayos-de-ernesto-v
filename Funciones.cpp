#include "graph.h"

#include <cmath>

using pareja = pair <int,Node<Aeropuerto*>*>;


Edge<Aeropuerto*> * getEdge(Node<Aeropuerto*>* _from, Node<Aeropuerto*>* _to){
    auto ed = new Edge<Aeropuerto*>(_from,_to);
    auto lat1 = _from->getData()->getLatitude();
    auto long1 =  _from->getData()->getLongitude();
    auto lat2 = _to->getData()->getLatitude();
    auto long2 =  _to->getData()->getLongitude();
    auto peso = sqrt(pow(lat1-lat2,2)+pow(long1-long2,2));
    ed->setWeight(peso);
    return ed;
}
bool inMap(map<int,Node<Aeropuerto*>*>mapa, int id){
    return mapa[id];
}

Graph<Aeropuerto*> buildGraph(string a){
    auto* graf = new Graph<Aeropuerto*>;
    auto mapa = graf->get_map();
    ifstream ifs(a);
    if (ifs.fail()){cout<<"error"<<endl; exit(-1);}
    json json1 =json::parse(ifs);
    json file = std::move(json1);
    vector<Aeropuerto*> aeropuetos;
    for(int i = 0; i <  file.size(); i++){
        json json2 = file[i];
        auto* temp = new Aeropuerto(json2);
        auto* nodo = new Node<Aeropuerto*>(temp);
        mapa->insert(pareja(temp->get_Id(),nodo));
    }
    for(auto it=mapa->cbegin(); it!=mapa->cend(); it++){
        auto temp = it->second;
        auto vec = temp->getData()->get_destinos();
        for(int i = 0; i < vec->size(); i++){
            if(inMap(*mapa,(*vec)[i])){
               auto newEdge = getEdge(temp,(*mapa)[(*vec)[i]]);
               temp->insertEdge(newEdge);
            }
        }
    }
    return *graf;
}
