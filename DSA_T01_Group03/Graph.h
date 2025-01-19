// Graph.h
#pragma once
#include <vector>
#include <string>

class Graph {
private:
    static const int MAX_VERTICES = 1000;

    struct Edge {
        int actorId;
        int movieId;
        Edge* next;
    };

    struct Vertex {
        int id;
        bool isActor;
        Edge* edges;
        Vertex* next;
    };

    Vertex* vertices[MAX_VERTICES];
    int numVertices;
    int hash(int key);
    Vertex* findVertex(int id, bool isActor);

public:
    Graph();
    ~Graph();
    bool addVertex(int id, bool isActor);
    bool addEdge(int actorId, int movieId);
    bool removeEdge(int actorId, int movieId);
    void getMoviesForActor(int actorId, std::vector<int>& movieList);
    void getActorsForMovie(int movieId, std::vector<int>& actorList);
    void getActorNetwork(int actorId, std::vector<int>& connectedActors);
    void print() const;
    bool isEmpty() const;
    int getSize() const;
};
