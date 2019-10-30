//
// Created by saidchoquehuanca on 30/10/2019.
//

#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_DISJOINTSET_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_DISJOINTSET_H

#include <unordered_map>
#include "nodos.h"

template <typename T>
class DisjoinSet{
protected:
    std::unordered_map<T,T> disjoin;
public:
    DisjoinSet(){}

    T& operator[](T search){
        return disjoin[search];
    }

    T Find_Node(T node){
        if(disjoin[node] != node){
            disjoin[node]= Find_Node(disjoin[node]);
        }
        return disjoin[node];
    }

    void Union(T node , T node2){
        return Find_Node(node) == Find_Node(node2) ;
    }

    void makeset(Node<T>* node){
        disjoin[node] = node;
    }

   ~DisjoinSet();

};



#endif //GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_DISJOINTSET_H
