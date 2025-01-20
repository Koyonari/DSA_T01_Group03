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

    // Add a default constructor
    MovieInfo() : title(""), year(0), plot("") {}

    // Keep the existing parameterized constructor
    MovieInfo(const string& t, int y, const string& p)
        : title(t), year(y), plot(p) {
    }
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
    // Quick sort for actors by age
    void quickSort(vector<pair<string, int>>& arr, size_t low, size_t high);
    size_t partition(vector<pair<string, int>>& arr, size_t low, size_t high);

    // Quick sort for strings (names)
    void quickSort(vector<string>& arr, size_t low, size_t high);
    size_t partition(vector<string>& arr, size_t low, size_t high);

    // Merge sort for movies by year (stable sort)
    void mergeSort(vector<MovieInfo>& arr, size_t left, size_t right);
    void merge(vector<MovieInfo>& arr, size_t left, size_t mid, size_t right);

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
