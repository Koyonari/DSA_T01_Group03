#pragma once
#include <string>
#include <vector>
using namespace std;

class Graph;
struct Movie;
struct Actor;


struct Actor {
    int id;
    string name;
    int birthYear;
    vector<Movie*> movieIds;
    double rating;  //add rating
    int ratingCount;
};

struct Movie {
    int id;
    string title;
    string plot;
    int year;
    vector<Actor*> actorIds;
    double rating;  //add rating
    int ratingCount;
};

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