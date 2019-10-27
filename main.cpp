#include <iostream>
#include <vector>
#include "nodos.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include "Airports.h"
#include "Edge.h"
#include "Funciones.cpp"
#include "graph.h"

using namespace std;

using json = nlohmann::json;

int main(){
    Graph<Aeropuerto*> a;
    a = buildGraph("C:/Users/saidchoquehuanca/Documents/GitHub/graphs-los-lacayos-de-ernesto-v/airports.json");
    //"C:/Users/Jaime/Documents/GitHub/graphs-los-lacayos-de-ernesto-v/airports.json"
    Node<Aeropuerto*> *temp = nullptr;
    ifstream ifs("/Users/saidchoquehuanca/ClionProjects/untitled7/nuevoair.json");
    json nuevo =json::parse(ifs);
    temp = new Aeropuerto( Node* nuevo);

    a.insertNode(temp);

}
