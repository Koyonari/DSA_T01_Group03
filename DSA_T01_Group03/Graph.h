// Graph.h
#pragma once
#include <string>
#include <vector>
using namespace std;

// MovieInfo structure should be in the header since it's used in both files
struct MovieInfo {
    string title;
    int year;
    string plot;

    MovieInfo(const string& t, int y, const string& p)
        : title(t), year(y), plot(p) {}
};

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

    // Sorting helper functions
    void mergeSort(vector<pair<string, int>>& arr, int left, int right);
    void merge(vector<pair<string, int>>& arr, int left, int mid, int right);
    void insertionSort(vector<string>& arr);
    void insertionSortMovies(vector<MovieInfo>& arr);

public:
    Graph();
    ~Graph();

    // Core graph operations
    Vertex* findVertex(int id, bool isActor);
    bool addVertex(int id, string name, int value, bool isActor, string plot = "");
    bool addEdge(int actorId, int movieId);

    // Query operations
    void displayActorsByAge(int startAge, int endAge);
    void displayRecentMovies(int currentYear);
    void displayActorMovies(int actorId);
    void displayMovieCast(int movieId);
    void displayActorNetwork(int actorId);
};
