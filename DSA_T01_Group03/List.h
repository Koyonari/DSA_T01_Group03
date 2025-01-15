// List.h
#include <iostream>
#include <string>
using namespace std;

// Declare structs
struct Movie; 
struct Actor;

// Separate node types for the lists
struct ActorListNode {
    Actor* actor;
    ActorListNode* next;
};

struct MovieListNode {
    Movie* movie;
    MovieListNode* next;
};

class List {
private:
    union {
        ActorListNode* firstActorNode;
        MovieListNode* firstMovieNode;
    };
    int size;
    bool isActorList;

public:
    List(bool isActor);
    ~List();
    bool add(Movie* movie);
    bool add(Actor* actor);
    void remove(int id);
    bool contains(int id);
    Movie* getMovie(int index);
    Actor* getActor(int index);
    bool isEmpty();
    int getLength();
    void print();
};
