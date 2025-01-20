// Graph.cpp
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

// Sorting function implementations
void Graph::mergeSort(vector<pair<string, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void Graph::merge(vector<pair<string, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<string, int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].second <= R[j].second)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void Graph::insertionSort(vector<string>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        string key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void Graph::insertionSortMovies(vector<MovieInfo>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        MovieInfo key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].year > key.year) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
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

    // Use merge sort for age-based sorting
    mergeSort(matchingActors, 0, matchingActors.size() - 1);

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

    // Use insertion sort for movies by year
    insertionSortMovies(recentMovies);

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
    while (current != nullptr) {
        Vertex* movie = findVertex(current->destId, false);
        if (movie) {
            movies.push_back(movie->name);
        }
        current = current->next;
    }

    // Use insertion sort for alphabetical ordering
    insertionSort(movies);

    cout << "Movies starring " << actor->name << ":\n";
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
    while (current != nullptr) {
        Vertex* actor = findVertex(current->destId, true);
        if (actor) {
            actors.push_back(actor->name);
        }
        current = current->next;
    }

    // Use insertion sort for alphabetical ordering
    insertionSort(actors);

    cout << "Cast of " << movie->name << ":\n";
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

    while (movieEdge != nullptr) {
        Vertex* movie = findVertex(movieEdge->destId, false);
        if (movie) {
            Edge* castEdge = movie->edges;
            while (castEdge != nullptr) {
                if (castEdge->destId != actorId) {
                    Vertex* coActor = findVertex(castEdge->destId, true);
                    if (coActor && find(coActors.begin(), coActors.end(), coActor->name) == coActors.end()) {
                        coActors.push_back(coActor->name);
                    }
                }
                castEdge = castEdge->next;
            }
        }
        movieEdge = movieEdge->next;
    }

    // Use insertion sort for alphabetical ordering
    insertionSort(coActors);

    cout << "Actors who have worked with " << actor->name << ":\n";
    for (const string& coActor : coActors) {
        cout << "- " << coActor << "\n";
    }
}