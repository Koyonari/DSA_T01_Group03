#pragma once
#include <string>
#include <vector>
using namespace std;

class Graph;

// Actor and Movie structures remain the same
struct Actor {
    int id;
    string name;
    int birthYear;
    vector<int> movieIds;  // Add this to track relationships
};

struct Movie {
    int id;
    string title;
    string plot;
    int year;
    vector<int> actorIds;  // Add this to track relationships
};

// Actor and movie nodes for dictionary remain the same
struct ActorNode {
    int key;
    Actor* actor;
    ActorNode* next;
};

struct MovieNode {
    int key;
    Movie* movie;
    MovieNode* next;
};

class Dictionary {
private:
    static const int MAX_SIZE = 101;
    union {
        ActorNode* actorItems[MAX_SIZE];
        MovieNode* movieItems[MAX_SIZE];
    };
    int size;
    bool isActorDict;
    Graph* relationshipGraph;
    int hash(int key);

public:
    Dictionary(bool isActor, Graph* graph);
    ~Dictionary();

    bool addActor(int key, string name, int birthYear);
    bool addMovie(int key, string title, int year, string plot);
    bool updateActor(int key, string name, int birthYear);
    bool updateMovie(int key, string title, int year, string plot);
    void remove(int key);
    Actor* getActor(int key);
    Movie* getMovie(int key);
    bool isEmpty();
    int getLength();
    void print();

    // New methods for relationship management
    bool addRelationship(int actorId, int movieId);
    vector<int> getActorMovies(int actorId);
    vector<int> getMovieActors(int movieId);
    vector<Actor*> getAllActors();
    vector<Movie*> getAllMovies();
};