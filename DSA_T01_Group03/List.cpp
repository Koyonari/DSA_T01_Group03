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

bool Dictionary::update(int key, string name, int value) {
    int index = hash(key);

    if (isActorDict) {
        // Find the actor node
        ActorNode* current = actorItems[index];
        while (current != nullptr) {
            if (current->key == key) {
                // Update the actor's details
                current->actor->name = name;
                current->actor->birthYear = value;
                return true;  // Successfully updated
            }
            current = current->next;
        }
    }
    else {
        // Find the movie node
        MovieNode* current = movieItems[index];
        while (current != nullptr) {
            if (current->key == key) {
                // Update the movie's details
                current->movie->title = name;
                current->movie->year = value;
                return true;  // Successfully updated
            }
            current = current->next;
        }
    }

    // If no entry found, return false
    return false;
}

void List::print() {
    if (isActorList) {
        std::cout << "Actor List:\n";
        ActorListNode* current = firstActorNode;
        while (current != nullptr) {
            std::cout << "ID: " << current->actor->id
                << ", Name: " << current->actor->name
                << ", Birth Year: " << current->actor->birthYear
                << "\n";
            current = current->next;
        }
    }
    else {
        std::cout << "Movie List:\n";
        MovieListNode* current = firstMovieNode;
        while (current != nullptr) {
            std::cout << "ID: " << current->movie->id
                << ", Title: " << current->movie->title
                << ", Year: " << current->movie->year
                << "\n";
            current = current->next;
        }
    }
}