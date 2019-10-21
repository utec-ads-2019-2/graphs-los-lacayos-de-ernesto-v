

#ifndef UNTITLED7_NODOS_H
#define UNTITLED7_NODOS_H

#include "string.h"

template <typename G>
class Node {
public:
    typedef typename G::N N;
    typedef typename G::Edge Edge;
    typedef typename G::EdgeSeq EdgeSeq;
    EdgeSeq edges;
private:
    N data;
};


#endif //UNTITLED7_NODOS_H
