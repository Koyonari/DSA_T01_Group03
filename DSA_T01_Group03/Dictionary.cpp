#include "Dictionary.h"

#include <iostream>



Dictionary::Dictionary(bool isActor, Graph* graph)

    : size(0), isActorDict(isActor), relationshipGraph(graph) {

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

                delete current->movie;

                delete current;

                current = next;

            }

        }

    }

}



int Dictionary::hash(int key) {

    return key % MAX_SIZE;

}



// For actors
bool Dictionary::addActor(int key, string name, int birthYear) {
    if (!isActorDict) return false;

    int index = hash(key);
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
    newActor->birthYear = birthYear;
    newNode->actor = newActor;
    newNode->next = actorItems[index];
    actorItems[index] = newNode;

    // Add to relationship graph
    relationshipGraph->addActor(key, name, birthYear);

    size++;
    return true;
}

// For movies
bool Dictionary::addMovie(int key, string title, int year, string plot) {
    if (isActorDict) return false;

    int index = hash(key);
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
    newMovie->title = title;
    newMovie->year = year;
    newMovie->plot = plot;
    newNode->movie = newMovie;
    newNode->next = movieItems[index];
    movieItems[index] = newNode;

    // Add to relationship graph
    relationshipGraph->addMovie(key, title, year, plot);

    size++;
    return true;
}

// Update functions
bool Dictionary::updateActor(int key, string name, int birthYear) {
    if (!isActorDict) return false;

    int index = hash(key);
    ActorNode* current = actorItems[index];
    while (current != nullptr) {
        if (current->key == key) {
            current->actor->name = name;
            current->actor->birthYear = birthYear;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool Dictionary::updateMovie(int key, string title, int year, string plot) {
    if (isActorDict) return false;

    int index = hash(key);
    MovieNode* current = movieItems[index];
    while (current != nullptr) {
        if (current->key == key) {
            current->movie->title = title;
            current->movie->year = year;
            current->movie->plot = plot;
            return true;
        }
        current = current->next;
    }
    return false;
}


Actor* Dictionary::getActor(int key) {

    if (!isActorDict) return nullptr;



    int index = hash(key);

    ActorNode* current = actorItems[index];

    while (current != nullptr) {

        if (current->key == key) {

            return current->actor;

        }

        current = current->next;

    }

    return nullptr;

}



Movie* Dictionary::getMovie(int key) {

    if (isActorDict) return nullptr;



    int index = hash(key);

    MovieNode* current = movieItems[index];

    while (current != nullptr) {

        if (current->key == key) {

            return current->movie;

        }

        current = current->next;

    }

    return nullptr;

}



bool Dictionary::isEmpty() {

    return size == 0;

}



int Dictionary::getLength() {

    return size;

}



void Dictionary::remove(int key) {

    int index = hash(key);

    if (isActorDict) {

        ActorNode* current = actorItems[index];

        ActorNode* prev = nullptr;

        while (current != nullptr) {

            if (current->key == key) {

                if (prev) {

                    prev->next = current->next;

                }

                else {

                    actorItems[index] = current->next;

                }

                delete current->actor;

                delete current;

                size--;

                return;

            }

            prev = current;

            current = current->next;

        }

    }

    else {

        MovieNode* current = movieItems[index];

        MovieNode* prev = nullptr;

        while (current != nullptr) {

            if (current->key == key) {

                if (prev) {

                    prev->next = current->next;

                }

                else {

                    movieItems[index] = current->next;

                }

                delete current->movie;

                delete current;

                size--;

                return;

            }

            prev = current;

            current = current->next;

        }

    }

}



void Dictionary::print() {

    std::cout << "Dictionary Contents:\n";

    if (isActorDict) {

        std::cout << "Actors:\n";

        for (int i = 0; i < MAX_SIZE; i++) {

            ActorNode* current = actorItems[i];

            while (current != nullptr) {

                std::cout << "ID: " << current->actor->id

                    << ", Name: " << current->actor->name

                    << ", Birth Year: " << current->actor->birthYear << "\n";

                current = current->next;

            }

        }

    }

    else {

        std::cout << "Movies:\n";

        for (int i = 0; i < MAX_SIZE; i++) {

            MovieNode* current = movieItems[i];

            while (current != nullptr) {

                std::cout << "ID: " << current->movie->id

                    << ", Title: " << current->movie->title

                    << ", Year: " << current->movie->year << "\n";

                current = current->next;

            }

        }

    }

}