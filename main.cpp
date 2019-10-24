#include <iostream>
#include <vector>
#include "nodos.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace std;

using json = nlohmann::json;

int main(){
    ifstream ifs("/Users/m.noel/Desktop/Proyecto/graphs-los-lacayos-de-ernesto-v/airports.json");
    json json1 =json::parse(ifs);
    const json::value_type& airports= json1;
    const json::value_type& destinations= json1[0]["destinations"];


}
