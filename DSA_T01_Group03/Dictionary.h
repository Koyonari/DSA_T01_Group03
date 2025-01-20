#pragma once

#include <string>

#include "Graph.h"

using namespace std;



// Actor and Movie structures

struct Actor {

    int id;

    string name;

    int birthYear;

};



struct Movie {

    int id;

    string title;

    int year;

};



// Actor and movie nodes for dictionary

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

    Graph* relationshipGraph;  // Pointer to the graph managing relationships

    int hash(int key);



public:

    Dictionary(bool isActor, Graph* graph);

    ~Dictionary();

    bool add(int key, string name, int value);

    bool update(int key, string name, int value);

    void remove(int key);

    Actor* getActor(int key);

    Movie* getMovie(int key);

    bool isEmpty();

    int getLength();

    void print();

};