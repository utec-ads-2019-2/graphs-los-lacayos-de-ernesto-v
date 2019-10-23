
#ifndef UNTITLED7_AIRPORTS_H
#define UNTITLED7_AIRPORTS_H

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <vector>


using namespace std;

using json = nlohmann::json;


class Aeropuerto{
protected:
    string Ciudad;
    string Pais;
    string Nombre;
    double Longitud;
    double Latitud;
    int Id;
    vector<int> *Destinos;
public:
    Aeropuerto(json airports) {
        Destinos = new vector<int>;
        Ciudad = airports["City"];
        Pais = airports["Country"];
        Nombre = airports["Name"];
        string longi = airports["Longitude"];
        string lati = airports["Latitude"];
        Longitud = atof(longi.c_str());
        Latitud = atof(lati.c_str());
        string id= airports["Id"];
        Id = atoi(id.c_str());
        json destinations = airports["destinations"];
        for(auto i = destinations.begin() ; i != destinations.end() ; i++){
            string destino = *i;
            Destinos->push_back(atoi(destino.c_str()));
        }
    }


    virtual ~Aeropuerto() {
    }
    void print() {
        cout << Ciudad << endl;
        cout << Nombre << endl;
        cout << Pais << endl;
        cout << Longitud << endl;
        cout << Latitud << endl;
        cout << Id << endl;
        cout << "Destination:" << endl;
        for (auto i = Destinos->begin(); i != Destinos->end(); i++) {
            cout << "   " << *i << endl;
        }
    }
    int get_Id(){
        return Id;
    }
    vector <int>* get_destinos(){
        return Destinos;
    }
};



#endif //UNTITLED7_AIRPORTS_H
