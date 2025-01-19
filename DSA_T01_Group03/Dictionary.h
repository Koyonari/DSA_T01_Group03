// Dictionary.h
#include <string>
using namespace std;

// Declare structs
struct Movie;
struct Actor; 
class List; 

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

// Actor and Movie structures
struct Actor {
    int id;
    string name;
    int birthYear;
    List* movies;  // List of movies this actor has been in
};

struct Movie {
    int id;
    string title;
    int year;
    List* cast;    // List of actors in this movie
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

    int hash(int key);

public:
    Dictionary(bool isActor);
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