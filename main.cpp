#include <iostream>
#include <vector>
#include "nodos.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include "Funciones.cpp"

using namespace std;

using json = nlohmann::json;

int main(){
    Graph<Aeropuerto*> a;
    a = buildGraph("C:/Users/saidchoquehuanca/Documents/GitHub/graphs-los-lacayos-de-ernesto-v/notDirected.json");
    //"C:/Users/Jaime/Documents/GitHub/graphs-los-lacayos-de-ernesto-v/airports.json"
    //Node<Aeropuerto*> *temp = nullptr;
    //ifstream ifs("/Users/saidchoquehuanca/ClionProjects/untitled7/nuevoair.json");
    //json nuevo =json::parse(ifs);
    //temp = new Aeropuerto( Node* nuevo);
    if(a.isConex())
        cout<<"conexo";
    (a.kruskal());
}
