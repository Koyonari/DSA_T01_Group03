#pragma once
#include <string>
#include <vector>
using namespace std;

// Forward declaration to prevent circular dependency issues, since Movie references Actor and vice versa
class Graph;
struct Movie;
struct Actor;

// Actor struct to store an Actor's information
struct Actor {
    int id;
    string name;
    int birthYear;
    vector<Movie*> movies;
    double rating;  //add rating
    int ratingCount;
};

// Movie struct to store a Movie's information
struct Movie {
    int id;
    string title;
    string plot;
    int year;
    vector<Actor*> actors;
    double rating;  //add rating
    int ratingCount;
};

// ActorNode to store an Actor in the Dictionary
struct ActorNode {
    int key;
    Actor* actor;
    ActorNode* next;
};

// MovieNode to store a Movie in the Dictionary
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

    bool addActor(int key, string name, int birthYear, double rating, int ratingCount);
    bool addMovie(int key, string title, int year, string plot, double rating, int ratingCount);
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
    vector<Movie*> getActorMovies(int actorId);
    vector<Actor*> getMovieActors(int movieId);
    vector<Actor*> getAllActors();
    vector<Movie*> getAllMovies();

    //rating
    bool updateActorRating(int key, double rating);
    bool updateMovieRating(int key, double rating);
};