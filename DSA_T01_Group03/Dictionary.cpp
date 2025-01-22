#include "Dictionary.h"
#include <iostream>
#include "Graph.h"
Dictionary::Dictionary(bool isActor, Graph* graph)
    : size(0), isActorDict(isActor), relationshipGraph(graph) {
    if (isActorDict) {
        for (int i = 0; i < MAX_SIZE; i++) {
            actorItems[i] = nullptr;  // Properly initialize all elements
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
    // Initialize empty vector for movie relationships
    newActor->movieIds = vector<int>();

    newNode->actor = newActor;
    newNode->next = actorItems[index];
    actorItems[index] = newNode;

    size++;
    return true;
}

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
    // Initialize empty vector for actor relationships
    newMovie->actorIds = vector<int>();

    newNode->movie = newMovie;
    newNode->next = movieItems[index];
    movieItems[index] = newNode;

    size++;
    return true;
}

bool Dictionary::addRelationship(int actorId, int movieId) {
    Actor* actor = getActor(actorId);
    Movie* movie = nullptr;
    if (isActorDict) {
        movie = relationshipGraph->findMovie(movieId);
        if (!movie) cout << "Movie ID " << movieId << " not found in the graph." << endl;
    }
    else {
        movie = getMovie(movieId);
        if (!movie) cout << "Movie ID " << movieId << " not found in dictionary." << endl;
    }

    if (!actor || !movie) return false;

    // Check if relationship already exists
    if (find(actor->movieIds.begin(), actor->movieIds.end(), movieId) != actor->movieIds.end()) {
        cout << "Relationship already exists for Actor ID " << actorId << " and Movie ID " << movieId << endl;
        return false;
    }

    // Add relationship
    actor->movieIds.push_back(movieId);
    movie->actorIds.push_back(actorId);
    //cout << "Successfully added relationship: Actor " << actorId << " -> Movie " << movieId << endl;

    return true;
}


vector<int> Dictionary::getActorMovies(int actorId) {
    Actor* actor = getActor(actorId);
    if (actor) {
        return actor->movieIds;
    }
    return vector<int>();
}

vector<int> Dictionary::getMovieActors(int movieId) {
    Movie* movie = getMovie(movieId);
    if (movie) {
        return movie->actorIds;
    }
    return vector<int>();
}

vector<Actor*> Dictionary::getAllActors() {
    if (!isActorDict) return vector<Actor*>();

    vector<Actor*> actors;
    for (int i = 0; i < MAX_SIZE; i++) {
        ActorNode* current = actorItems[i];
        while (current != nullptr) {
            actors.push_back(current->actor);
            current = current->next;
        }
    }
    return actors;
}

vector<Movie*> Dictionary::getAllMovies() {
    if (isActorDict) return vector<Movie*>();

    vector<Movie*> movies;
    for (int i = 0; i < MAX_SIZE; i++) {
        MovieNode* current = movieItems[i];
        while (current != nullptr) {
            movies.push_back(current->movie);
            current = current->next;
        }
    }
    return movies;
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

bool Dictionary::updateActor(int key, string name, int birthYear) {
    if (!isActorDict) return false;

    Actor* actor = getActor(key);
    if (actor) {
        actor->name = name;
        actor->birthYear = birthYear;
        return true;
    }
    return false;
}

bool Dictionary::updateMovie(int key, string title, int year, string plot) {
    if (isActorDict) return false;

    Movie* movie = getMovie(key);
    if (movie) {
        movie->title = title;
        movie->year = year;
        movie->plot = plot;
        return true;
    }
    return false;
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
                    << ", Birth Year: " << current->actor->birthYear
                    << ", Number of Movies: " << current->actor->movieIds.size() << "\n";
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
                    << ", Year: " << current->movie->year
                    << ", Number of Actors: " << current->movie->actorIds.size() << "\n";
                current = current->next;
            }
        }
    }
}