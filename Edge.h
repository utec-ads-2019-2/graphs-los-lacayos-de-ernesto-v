
#ifndef UNTITLED7_EDGE_H
#define UNTITLED7_EDGE_H

#include "nodos.h"
#include <vector>
#include <list>
using namespace std;

template <typename G>
class Edge {
public:
    typedef typename G::E E;
    typedef typename G::Node Node;
    Node* nodes[2];
private:
    E data;
};





#endif //UNTITLED7_EDGE_H
