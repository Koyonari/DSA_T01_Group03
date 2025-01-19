// Graph.cpp
#include "Graph.h"
#include <iostream>
#include <algorithm>

Graph::Graph() : numVertices(0) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertex* currentVertex = vertices[i];
        while (currentVertex != nullptr) {
            Edge* currentEdge = currentVertex->edges;
            while (currentEdge != nullptr) {
                Edge* nextEdge = currentEdge->next;
                delete currentEdge;
                currentEdge = nextEdge;
            }
            Vertex* nextVertex = currentVertex->next;
            delete currentVertex;
            currentVertex = nextVertex;
        }
    }
}

int Graph::hash(int key) {
    return key % MAX_VERTICES;
}

Graph::Vertex* Graph::findVertex(int id, bool isActor) {
    int index = hash(id);
    Vertex* current = vertices[index];

    while (current != nullptr) {
        if (current->id == id && current->isActor == isActor) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool Graph::addVertex(int id, bool isActor) {
    if (findVertex(id, isActor) != nullptr) {
        return false;
    }

    int index = hash(id);
    Vertex* newVertex = new Vertex;
    newVertex->id = id;
    newVertex->isActor = isActor;
    newVertex->edges = nullptr;
    newVertex->next = vertices[index];
    vertices[index] = newVertex;
    numVertices++;
    return true;
}
