// Dictionary.cpp
#include "Dictionary.h"
#include "List.h"

Dictionary::Dictionary(bool isActor) : size(0), isActorDict(isActor) {
    // Initialize pointers to nullptr
    if (isActor) {
        for (int i = 0; i < MAX_SIZE; i++) {
            actorItems[i] = nullptr;
        }
    }
    else {
        for (int i = 0; i < MAX_SIZE; i++) {
            movieItems[i] = nullptr;
        }
    }
}

Dictionary::~Dictionary() {
    if (isActorDict) {
        for (int i = 0; i < MAX_SIZE; i++) {
            ActorNode* current = actorItems[i];
            while (current != nullptr) {
                ActorNode* next = current->next;
                delete current->actor->movies;
                delete current->actor;
                delete current;
                current = next;
            }
        }
    }
    else {
        for (int i = 0; i < MAX_SIZE; i++) {
            MovieNode* current = movieItems[i];
            while (current != nullptr) {
                MovieNode* next = current->next;
                delete current->movie->cast;
                delete current->movie;
                delete current;
                current = next;
            }
        }
    }
}

// Hash function
int Dictionary::hash(int key) {
    return key % MAX_SIZE; 
}

// Add actor or movie to HT
bool Dictionary::add(int key, string name, int value) {
    int index = hash(key);

    if (isActorDict) {
        // Check if key exists in actor chain
        ActorNode* current = actorItems[index];
        while (current != nullptr) {
            if (current->key == key) return false;
            current = current->next;
        }

        // Create new actor node
        ActorNode* newNode = new ActorNode;
        newNode->key = key;

        Actor* newActor = new Actor;
        newActor->id = key;
        newActor->name = name;
        newActor->birthYear = value;
        newActor->movies = new List(false);  // Create movie list

        newNode->actor = newActor;
        newNode->next = actorItems[index];
        actorItems[index] = newNode;
    }
    else {
        // Check if key exists in movie chain
        MovieNode* current = movieItems[index];
        while (current != nullptr) {
            if (current->key == key) return false;
            current = current->next;
        }

        // Create new movie node
        MovieNode* newNode = new MovieNode;
        newNode->key = key;

        Movie* newMovie = new Movie;
        newMovie->id = key;
        newMovie->title = name;
        newMovie->year = value;
        newMovie->cast = new List(true);  // Create actor list

        newNode->movie = newMovie;
        newNode->next = movieItems[index];
        movieItems[index] = newNode;
    }

    size++;
    return true;
}
