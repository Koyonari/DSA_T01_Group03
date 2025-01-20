#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <vector>

Graph::Graph() : numVertices(0) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertex* currentVertex = vertices[i];
        while (currentVertex != nullptr) {
            Edge* currentEdge = currentVertex->edges;
            while (currentEdge != nullptr) {
                Edge* nextEdge = currentEdge->next;
                delete currentEdge;
                currentEdge = nextEdge;
            }
            Vertex* nextVertex = currentVertex->next;
            delete currentVertex;
            currentVertex = nextVertex;
        }
    }
}

int Graph::hash(int key) {
    return key % MAX_VERTICES;
}

Graph::Vertex* Graph::findVertex(int id, bool isActor) {
    int index = hash(id);
    Vertex* current = vertices[index];
    while (current != nullptr) {
        if (current->id == id && current->isActor == isActor) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool Graph::addVertex(int id, string name, int value, bool isActor, string plot) {
    if (findVertex(id, isActor) != nullptr) {
        return false;  // Vertex already exists
    }

    int index = hash(id);
    Vertex* newVertex = new Vertex;
    newVertex->id = id;
    newVertex->isActor = isActor;
    newVertex->name = name;
    newVertex->value = value;
    newVertex->plot = plot;
    newVertex->edges = nullptr;
    newVertex->next = vertices[index];
    vertices[index] = newVertex;
    numVertices++;
    return true;
}

bool Graph::addEdge(int actorId, int movieId) {
    Vertex* actor = findVertex(actorId, true);
    Vertex* movie = findVertex(movieId, false);

    if (!actor || !movie) {
        return false;
    }

    // Check if edge already exists
    Edge* current = actor->edges;
    while (current != nullptr) {
        if (current->destId == movieId) {
            return false;  // Edge already exists
        }
        current = current->next;
    }

    // Add movie to actor's edge list
    Edge* newEdge1 = new Edge;
    newEdge1->destId = movieId;
    newEdge1->next = actor->edges;
    actor->edges = newEdge1;

    // Add actor to movie's edge list
    Edge* newEdge2 = new Edge;
    newEdge2->destId = actorId;
    newEdge2->next = movie->edges;
    movie->edges = newEdge2;

    return true;
}

// Quick sort implementation for actors by age
void Graph::quickSort(vector<pair<string, int>>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);
        if (pivot > 0) quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

size_t Graph::partition(vector<pair<string, int>>& arr, size_t low, size_t high) {
    int pivot = arr[high].second;
    size_t i = low - 1;

    for (size_t j = low; j <= high - 1; j++) {
        if (arr[j].second <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick sort for strings
void Graph::quickSort(vector<string>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);
        if (pivot > 0) quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

size_t Graph::partition(vector<string>& arr, size_t low, size_t high) {
    string pivot = arr[high];
    size_t i = low - 1;

    for (size_t j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Merge sort for movies by year
void Graph::mergeSort(vector<MovieInfo>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void Graph::merge(vector<MovieInfo>& arr, size_t left, size_t mid, size_t right) {
    vector<MovieInfo> temp(right - left + 1);
    size_t i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].year <= arr[j].year) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
}

void Graph::displayActorsByAge(int startAge, int endAge) {
    int currentYear = 2024;
    vector<pair<string, int>> matchingActors;

    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertex* current = vertices[i];
        while (current != nullptr) {
            if (current->isActor) {
                int age = currentYear - current->value;
                if (age >= startAge && age <= endAge) {
                    matchingActors.push_back(make_pair(current->name, age));
                }
            }
            current = current->next;
        }
    }

    if (matchingActors.empty()) {
        cout << "No actors found in the specified age range." << endl;
        return;
    }

    // Sort using quick sort
    if (matchingActors.size() > 1) {
        quickSort(matchingActors, 0, matchingActors.size() - 1);
    }

    cout << "\nActors between " << startAge << " and " << endAge << " years old:" << endl;
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < matchingActors.size(); i++) {
        cout << (i + 1) << ". " << left << setw(30) << matchingActors[i].first
            << "Age: " << matchingActors[i].second << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Total actors found: " << matchingActors.size() << endl;
}

void Graph::displayRecentMovies(int currentYear) {
    vector<MovieInfo> recentMovies;

    // Collect recent movies from all buckets
    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertex* current = vertices[i];
        while (current != nullptr) {
            if (!current->isActor && (currentYear - current->value) <= 3) {
                recentMovies.emplace_back(current->name, current->value, current->plot);
            }
            current = current->next;
        }
    }

    if (recentMovies.empty()) {
        cout << "No recent movies found." << endl;
        return;
    }

    // Sort using merge sort for stable sorting by year
    if (recentMovies.size() > 1) {
        mergeSort(recentMovies, 0, recentMovies.size() - 1);
    }

    cout << "\nMovies from the past 3 years:" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& movie : recentMovies) {
        cout << movie.title << " (" << movie.year << ")" << endl;
        cout << "Plot: " << movie.plot << endl << endl;
    }
}

void Graph::displayActorMovies(int actorId) {
    Vertex* actor = findVertex(actorId, true);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    vector<string> movies;
    Edge* current = actor->edges;

    // Collect all movies the actor has starred in
    while (current != nullptr) {
        Vertex* movie = findVertex(current->destId, false);
        if (movie) {
            movies.push_back(movie->name);
        }
        current = current->next;
    }

    if (movies.empty()) {
        cout << "No movies found for " << actor->name << ".\n";
        return;
    }

    // Sort alphabetically using quicksort
    if (movies.size() > 1) {
        quickSort(movies, 0, movies.size() - 1);
    }

    cout << "\nMovies starring " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& movie : movies) {
        cout << "- " << movie << "\n";
    }
}

void Graph::displayMovieCast(int movieId) {
    Vertex* movie = findVertex(movieId, false);
    if (!movie) {
        cout << "Movie not found.\n";
        return;
    }

    vector<string> actors;
    Edge* current = movie->edges;

    // Collect all actors in the movie
    while (current != nullptr) {
        Vertex* actor = findVertex(current->destId, true);
        if (actor) {
            actors.push_back(actor->name);
        }
        current = current->next;
    }

    if (actors.empty()) {
        cout << "No cast found for " << movie->name << ".\n";
        return;
    }

    // Sort alphabetically using quicksort
    if (actors.size() > 1) {
        quickSort(actors, 0, actors.size() - 1);
    }

    cout << "\nCast of " << movie->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& actor : actors) {
        cout << "- " << actor << "\n";
    }
}

void Graph::displayActorNetwork(int actorId) {
    Vertex* actor = findVertex(actorId, true);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    vector<string> coActors;
    Edge* movieEdge = actor->edges;

    // For each movie the actor was in
    while (movieEdge != nullptr) {
        Vertex* movie = findVertex(movieEdge->destId, false);
        if (movie) {
            Edge* castEdge = movie->edges;
            // For each actor in that movie
            while (castEdge != nullptr) {
                if (castEdge->destId != actorId) {  // Don't include the original actor
                    Vertex* coActor = findVertex(castEdge->destId, true);
                    if (coActor) {
                        // Only add if not already in the list
                        if (find(coActors.begin(), coActors.end(), coActor->name) == coActors.end()) {
                            coActors.push_back(coActor->name);
                        }
                    }
                }
                castEdge = castEdge->next;
            }
        }
        movieEdge = movieEdge->next;
    }

    if (coActors.empty()) {
        cout << actor->name << " has not worked with any other actors.\n";
        return;
    }

    // Sort alphabetically using quicksort
    if (coActors.size() > 1) {
        quickSort(coActors, 0, coActors.size() - 1);
    }

    cout << "\nActors who have worked with " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& coActor : coActors) {
        cout << "- " << coActor << "\n";
    }
}