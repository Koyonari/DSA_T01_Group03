#include "Dictionary.h"
#include <iostream>
#include "Graph.h"

// Constructor with bool and Graph parameters
// bool is to find out if the dictionary is for actors or movies, so it can be populated correctly
// Graph is passed in so that the relationships can be modelled in it later (relationshipGraph is an attribute of the class)
Dictionary::Dictionary(bool isActor, Graph* graph)
    : size(0), isActorDict(isActor), relationshipGraph(graph) { // To initialise the items in the class
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

// The destructor, to properly delete a Dictionary without leaving any unhandled memory
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

// Function to hash a key by the MAX_SIZE and return the hashed value
// MAX_SIZE is 101 and hence it is used to hash the key as it is not only a balanced size, but is a prime number that will distribute hash values more evenly
int Dictionary::hash(int key) {
    return key % MAX_SIZE;
}

// addActor method adds a new Actor to the dictionary, creating a new Actor using all the parameters
// returns a boolean based on if the addition was successful or not
bool Dictionary::addActor(int key, string name, int birthYear, double rating, int ratingCount) {
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
    newActor->rating = rating;
    newActor->ratingCount = ratingCount;
    // Initialize empty vector for movie relationships
    newActor->movies = vector<Movie*>();

    newNode->actor = newActor;
    newNode->next = actorItems[index];
    actorItems[index] = newNode;

    size++;
    return true;
}

// addMovie method adds a new Movie to the dictionary, creating a new Movie using all the parameters
// returns a boolean based on if the addition was successful or not
bool Dictionary::addMovie(int key, string title, int year, string plot, double rating, int ratingCount) {
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
    newMovie->rating = rating;
    newMovie->ratingCount = ratingCount;
    // Initialize empty vector for actor relationships
    newMovie->actors = vector<Actor*>();

    newNode->movie = newMovie;
    newNode->next = movieItems[index];
    movieItems[index] = newNode;

    size++;
    return true;
}

// addRelationship adds a relationship between an Actor and a Movie, found by their respective IDs given as parameters (e.g. if actor starred in certain movie)
// returns a boolean based on if the addition was successful or not
bool Dictionary::addRelationship(int actorId, int movieId) {
    Actor* actor = getActor(actorId);
    Movie* movie = nullptr;
    if (isActorDict) {
        movie = relationshipGraph->findMovie(movieId);
        //if (!movie) cout << "Movie ID " << movieId << " not found in the graph." << endl;
    }
    else {
        movie = getMovie(movieId);
        if (!movie) cout << "Movie ID " << movieId << " not found in dictionary." << endl;
    }

    if (!actor || !movie) return false;

    if (find(actor->movies.begin(), actor->movies.end(), movie) != actor->movies.end()) {
        cout << "Relationship already exists for Actor ID " << actorId << " and Movie ID " << movieId << endl;
        return false;
    }


    // Add relationship
    actor->movies.push_back(movie);
    movie->actors.push_back(actor);
    //cout << "Successfully added relationship: Actor " << actorId << " -> Movie " << movieId << endl;

    return true;
}

// getActorMovies returns all Movies an Actor acted in (their vector of Movie pointers)
// returns the vector of Movie pointers to the Movies they acted in
vector<Movie*> Dictionary::getActorMovies(int actorId) {
    Actor* actor = getActor(actorId);
    if (actor) {
        return actor->movies;
    }
    return vector<Movie*>();
}

vector<Actor*> Dictionary::getMovieActors(int movieId) {
    Movie* movie = getMovie(movieId);
    if (movie) {
        return movie->actors;
    }
    return vector<Actor*>();
}

// getAllActors gets all the Actors registered in the system
// returns a vector of Actor pointers
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

// getAllMovies gets all the Movies registered in the system
// returns a vector of Movie pointers
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

// getAllActors gets a specific Actor by their ID
// returns a pointer to the Actor object
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

// getAllMovies gets a specific Movie by their ID
// returns a pointer to the Movie object
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

// updateActor updates an Actor's attributes provided by the new attribute values in the parameters
// returns a boolean based on if the operation has succeeded
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

// updateMovie updates a Movie's attributes provided by the new attribute values in the parameters
// returns a boolean based on if the operation has succeeded
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

// isEmpty checks if the Dictionary has nothing inside it
// returns true if it is empty and false if it's not
bool Dictionary::isEmpty() {
    return size == 0;
}

// getLength returns the number of items inside the Dictionary
int Dictionary::getLength() {
    return size;
}

// remove removes an item from the Dictionary, found by its key provided as a parameter
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

// print prints all the contents of the Dictionary
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
                    << ", Number of Movies: " << current->actor->movies.size() << "\n";
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
                    << ", Number of Actors: " << current->movie->actors.size() << "\n";
                current = current->next;
            }
        }
    }
}

// updateActorRating updates the rating of an Actor found by their ID
// The rating is calculated by getting the average of all ratings including the new rating that was passed in as a parameter
// returns a boolean based on if the operation was successful or not
bool Dictionary::updateActorRating(int key, double rating) {
    if (!isActorDict) return false;
    Actor* actor = getActor(key);
    if (actor) {
     
        if (actor->ratingCount == 0) {
            actor->rating = rating;
        }
        else {
            actor->rating = ((actor->rating * actor->ratingCount) + rating) / (actor->ratingCount + 1);       
        }
        actor->ratingCount++;
        
        return true;
    }
    return false;
}

// updateMovieRating updates the rating of a Movie found by their ID
// The rating is calculated by getting the average of all ratings including the new rating that was passed in as a parameter
// returns a boolean based on if the operation was successful or not
bool Dictionary::updateMovieRating(int key, double rating) {
    if (isActorDict) return false;
    Movie* movie = getMovie(key);
    if (movie) {
        if (movie->ratingCount == 0) {
            movie->rating = rating;
            
        }
        else {
            
            movie->rating = ((movie->rating * movie->ratingCount) + rating) / (movie->ratingCount + 1);
            
        }
        movie->ratingCount++;
        return true;
    }
    return false;
}