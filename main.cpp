#include <iostream>
#include <vector>
#include "nodos.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include "Airports.h"
#include "Edge.h"
#include "graph.h"
using namespace std;

using json = nlohmann::json;

int main(){
    Graph<Aeropuerto> a("C:/Users/Jaime/Documents/GitHub/graphs-los-lacayos-de-ernesto-v/airports.json");

}
