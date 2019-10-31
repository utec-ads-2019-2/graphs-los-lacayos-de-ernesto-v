#include <iostream>
#include <vector>
#include "nodos.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include "Funciones.cpp"

using namespace std;

using json = nlohmann::json;

int main(){
    
    auto grafo = new Graph<char>;
    auto A = new Node<char> ('A');
    auto B = new Node<char> ('B');
    auto C = new Node<char> ('C');
    auto D = new Node<char> ('D');
    auto E = new Node<char> ('E');
    auto F = new Node<char> ('F');
    auto G = new Node<char> ('G');
    auto H = new Node<char> ('H');
    auto I = new Node<char> ('I');
    auto J = new Node<char> ('J');
    A->setId(1);
    B->setId(2);
    C->setId(3);
    D->setId(4);
    E->setId(5);
    F->setId(6);
    G->setId(7);
    H->setId(8);
    I->setId(9);
    J->setId(10);

    grafo->insertNode(A);
    grafo->insertNode(B);
    grafo->insertNode(C);
    grafo->insertNode(D);
    grafo->insertNode(E);
    grafo->insertNode(F);
    grafo->insertNode(G);
    grafo->insertNode(H);
    grafo->insertNode(I);
    grafo->insertNode(J);

    grafo->insertEdge(A,C,4); grafo->insertEdge(C,A,4);
    grafo->insertEdge(A,D,13); grafo->insertEdge(D,A,13);
    grafo->insertEdge(A,H,5); grafo->insertEdge(H,A,5);
    grafo->insertEdge(H,D,5); grafo->insertEdge(D,H,5);
    grafo->insertEdge(D,C,39); grafo->insertEdge(C,D,39);
    grafo->insertEdge(C,I,37); grafo->insertEdge(I,C,37);
    grafo->insertEdge(I,F,7); grafo->insertEdge(F,I,7);
    grafo->insertEdge(C,F,9); grafo->insertEdge(F,C,9);
    grafo->insertEdge(I,A,11); grafo->insertEdge(A,I,11);
    grafo->insertEdge(I,E,26); grafo->insertEdge(E,I,26);
    grafo->insertEdge(I,G,39); grafo->insertEdge(G,I,39);
    grafo->insertEdge(A,E,13);grafo->insertEdge(E,A,13);
    grafo->insertEdge(E,G,2); grafo->insertEdge(G,E,2);
    grafo->insertEdge(G,B,2); grafo->insertEdge(B,G,2);
    grafo->insertEdge(B,E,24); grafo->insertEdge(E,B,24);
    grafo->insertEdge(E,H,19); grafo->insertEdge(H,E,19);
    grafo->insertEdge(B,H,29); grafo->insertEdge(H,B,29);
    grafo->insertEdge(H,J,15); grafo->insertEdge(J,H,15);
    grafo->insertEdge(B,J,15); grafo->insertEdge(J,B,15);
    grafo->insertEdge(D,J,15); grafo->insertEdge(J,D,15);
    grafo->getProperties();
    
}
