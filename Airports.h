//
// Created by saidchoquehuanca on 9/10/2019.
//

#ifndef UNTITLED7_AIRPORTS_H
#define UNTITLED7_AIRPORTS_H

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <vector>


using namespace std;

using json = nlohmann::json;

//ifstream ifs("/Users/saidchoquehuanca/ClionProjects/untitled7/airports.json");
//json archivo =json::parse(ifs);

//const json::value_type& airports = archivo;
//const json::value_type& destinations = archivo[0]["destinations"];

class Aeropuerto{
protected:
    string Ciudad;
    string Pais;
    string Nombre;
    double Longitud;
    double Latitud;
    int Id;
    vector<int> Destinos;
public:
    Aeropuerto(json::value_type& airports) {
        Ciudad = airports["City"];
        Pais = airports["Country"];
        Nombre = airports["Name"];
        Longitud = airports["Longitude"];
        Latitud = airports["Latitude"];
        Id = airports["Id"];
        json destinations = airports["destinations"];
        for(auto i = destinations.begin() ; i != destinations.end() ; i++){
            int k;
            string destino = *i;
            k = atoi((destino).c_str());
            Destinos.push_back(k);
        }
    }


    virtual ~Aeropuerto() {
    }

};



#endif //UNTITLED7_AIRPORTS_H
