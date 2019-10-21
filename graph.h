#ifndef GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H
#define GRAPHS_LOS_LACAYOS_DE_ERNESTO_V_GRAPH_H

#include "Edge.h"
#include "nodos.h"


template <typename Tr>
class Graph {
public:
    typedef Graph<Tr> self;
    typedef Node<self> Node;
    typedef Edge<self> Edge;
    typedef vector<Node*> NodeSeq;
    typedef list<Edge*> EdgeSeq;

};








#endif 
