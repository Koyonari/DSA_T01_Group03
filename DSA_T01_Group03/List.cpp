// List.cpp
#include "List.h"
#include "Dictionary.h"

List::List(bool isActor) : size(0), isActorList(isActor) {
    if (isActor) {
        firstActorNode = nullptr;
    }
    else {
        firstMovieNode = nullptr;
    }
}

List::~List() {
    if (isActorList) {
        while (firstActorNode != nullptr) {
            ActorListNode* temp = firstActorNode;
            firstActorNode = firstActorNode->next;
            delete temp;
        }
    }
    else {
        while (firstMovieNode != nullptr) {
            MovieListNode* temp = firstMovieNode;
            firstMovieNode = firstMovieNode->next;
            delete temp;
        }
    }
}

// Add Actor to LL
bool List::add(Actor* actor) {
    if (!isActorList || !actor) return false;

    // Check for duplicates
    ActorListNode* current = firstActorNode;
    while (current != nullptr) {
        if (current->actor->id == actor->id) return false;
        current = current->next;
    }

    // Add new actor node
    ActorListNode* newNode = new ActorListNode;
    newNode->actor = actor;
    newNode->next = firstActorNode;
    firstActorNode = newNode;
    size++;
    return true;
}

// Add Movie to LL
bool List::add(Movie* movie) {
    if (isActorList || !movie) return false;

    // Check for duplicates
    MovieListNode* current = firstMovieNode;
    while (current != nullptr) {
        if (current->movie->id == movie->id) return false;
        current = current->next;
    }

    // Add new movie node
    MovieListNode* newNode = new MovieListNode;
    newNode->movie = movie;
    newNode->next = firstMovieNode;
    firstMovieNode = newNode;
    size++;
    return true;
}