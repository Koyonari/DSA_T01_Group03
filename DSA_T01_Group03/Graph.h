#pragma once
#include <string>
#include <vector>
using namespace std;

struct MovieInfo {
    string title;
    int year;
    string plot;
    MovieInfo() : title(""), year(0), plot("") {}
    MovieInfo(const string& t, int y, const string& p)
        : title(t), year(y), plot(p) {
    }
};

class Graph {
private:
    static const int MAX_VERTICES = 150;  // Size for each dictionary

    struct Edge {
        int destId;
        Edge* next;
    };

    struct Vertex {
        int id;
        string name;   // actor name or movie title
        int value;     // birth year for actors, release year for movies
        string plot;   // movie plot (empty for actors)
        Edge* edges;   // linked list of connections
        Vertex* next;  // for hash table chaining
    };

    // Separate hash tables for actors and movies
    Vertex* actorVertices[MAX_VERTICES];
    Vertex* movieVertices[MAX_VERTICES];
    int numActors;
    int numMovies;

    int hash(int key);

    // Sorting helper functions
    void quickSort(vector<pair<string, int>>& arr, size_t low, size_t high);
    size_t partition(vector<pair<string, int>>& arr, size_t low, size_t high);
    void quickSort(vector<string>& arr, size_t low, size_t high);
    size_t partition(vector<string>& arr, size_t low, size_t high);
    void mergeSort(vector<MovieInfo>& arr, size_t left, size_t right);
    void merge(vector<MovieInfo>& arr, size_t left, size_t mid, size_t right);

public:
    Graph();
    ~Graph();

    Vertex* findActor(int id);
    Vertex* findMovie(int id);
    bool addActor(int id, string name, int birthYear);
    bool addMovie(int id, string title, int year, string plot);
    bool addEdge(int actorId, int movieId);

    // Query operations
    void displayActorsByAge(int startAge, int endAge);
    void displayRecentMovies(int currentYear);
    void displayActorMovies(int actorId);
    void displayMovieCast(int movieId);
    void displayActorNetwork(int actorId);
};