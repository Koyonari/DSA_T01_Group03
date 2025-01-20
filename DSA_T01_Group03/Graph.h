#pragma once
#include <string>
using namespace std;

class Graph {
private:
    static const int MAX_VERTICES = 150;  // Adjust size as needed

    struct Edge {
        int destId;
        Edge* next;
    };

    struct Vertex {
        int id;
        bool isActor;  // true for actor, false for movie
        string name;   // actor name or movie title
        int value;     // birth year for actors, release year for movies
        string plot;   // movie plot (empty for actors)
        Edge* edges;   // linked list of connections
        Vertex* next;  // for hash table chaining
    };

    Vertex* vertices[MAX_VERTICES];
    int numVertices;
    int hash(int key);

public:
    Graph();
    ~Graph();

    // Core graph operations
    Vertex* findVertex(int id, bool isActor);
    bool addVertex(int id, string name, int value, bool isActor, string plot = "");
    bool addEdge(int actorId, int movieId);
    bool removeEdge(int actorId, int movieId);

    // Query operations
    void displayActorsByAge(int startAge, int endAge);
    void displayRecentMovies(int currentYear);
    void displayActorMovies(int actorId);
    void displayMovieCast(int movieId);
    void displayActorNetwork(int actorId);
};