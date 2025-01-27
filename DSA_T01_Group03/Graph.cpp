#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <vector>

Graph::Graph() {
    actorDict = new Dictionary(true, this);
    movieDict = new Dictionary(false, this);
}

Graph::~Graph() {
    delete actorDict;
    delete movieDict;
}

bool Graph::updateActorRating(int key, double rating) {
    return actorDict->updateActorRating(key, rating);
}

bool Graph::updateMovieRating(int key, double rating) {
    return movieDict->updateMovieRating(key, rating);
}

Actor* Graph::findActor(int id) {
    return actorDict->getActor(id);
}

Movie* Graph::findMovie(int id) {
    return movieDict->getMovie(id);
}

bool Graph::addActor(int id, string name, int birthYear, double rating, int ratingCount) {
    return actorDict->addActor(id, name, birthYear, rating, ratingCount);
}

bool Graph::addMovie(int id, string title, int year, string plot, double rating, int ratingCount) {
    return movieDict->addMovie(id, title, year, plot, rating, ratingCount);
}

bool Graph::addEdge(int actorId, int movieId) {
    // Add relationship in both dictionaries (the addrelationship method will add in both so lets just call one)
    if (!actorDict->addRelationship(actorId, movieId)) {
        return false;
    }
    return true;
}

// Sorting helper functions
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
    int currentYear;
    cout << "Enter the current year: ";
    cin >> currentYear;

    vector<Actor*> allActors = actorDict->getAllActors();
    vector<pair<string, int>> matchingActors;

    // Filter actors by age
    for (Actor* actor : allActors) {
        int age = currentYear - actor->birthYear;
        if (age >= startAge && age <= endAge) {
            matchingActors.push_back(make_pair(actor->name, age));
        }
    }

    if (matchingActors.empty()) {
        cout << "No actors found in the specified age range." << endl;
        return;
    }

    // Sort by age
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

void Graph::displayRecentMovies() {
    int currentYear;
    cout << "Enter the current year: ";
    cin >> currentYear;

    vector<Movie*> allMovies = movieDict->getAllMovies();
    vector<MovieInfo> recentMovies;

    for (Movie* movie : allMovies) {
        int yearDiff = currentYear - movie->year;
        if (yearDiff >= 0 && yearDiff <= 3) {
            recentMovies.emplace_back(movie->title, movie->year, movie->plot);
        }
    }

    if (recentMovies.empty()) {
        cout << "No recent movies found." << endl;
        return;
    }

    // Sort by year
    mergeSort(recentMovies, 0, recentMovies.size() - 1);

    cout << "\nMovies from the past 3 years:" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& movie : recentMovies) {
        cout << movie.title << " (" << movie.year << ")" << endl;
        cout << "Plot: " << movie.plot << endl << endl;
    }
}

void Graph::displayActorMovies(int actorId) {
    Actor* actor = findActor(actorId);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    vector<int> movieIds = actorDict->getActorMovies(actorId);
    vector<string> movieTitles;

    // Get movie titles
    for (int movieId : movieIds) {
        Movie* movie = findMovie(movieId);
        if (movie) {
            movieTitles.push_back(movie->title);
        }
    }

    if (movieTitles.empty()) {
        cout << "No movies found for " << actor->name << ".\n";
        return;
    }

    // Sort alphabetically
    if (movieTitles.size() > 1) {
        quickSort(movieTitles, 0, movieTitles.size() - 1);
    }

    cout << "\nMovies starring " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& title : movieTitles) {
        cout << "- " << title << "\n";
    }
}

void Graph::displayMovieCast(int movieId) {
    Movie* movie = findMovie(movieId);
    if (!movie) {
        cout << "Movie not found.\n";
        return;
    }

    vector<int> actorIds = movieDict->getMovieActors(movieId);
    vector<string> actorNames;

    // Get actor names
    for (int actorId : actorIds) {
        Actor* actor = findActor(actorId);
        if (actor) {
            actorNames.push_back(actor->name);
        }
    }

    if (actorNames.empty()) {
        cout << "No cast found for " << movie->title << ".\n";
        return;
    }

    // Sort alphabetically
    if (actorNames.size() > 1) {
        quickSort(actorNames, 0, actorNames.size() - 1);
    }

    cout << "\nCast of " << movie->title << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& name : actorNames) {
        cout << "- " << name << "\n";
    }
}

void Graph::displayActorNetwork(int actorId) {
    Actor* actor = findActor(actorId);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    vector<string> coActorNames;
    vector<int> actorMovies = actorDict->getActorMovies(actorId);

    //for each movie the actor was in
    for (int movieId : actorMovies) {
        vector<int> castIds = movieDict->getMovieActors(movieId);
        //for each actor in that movie
        for (int castId : castIds) {
            if (castId != actorId) {  
                Actor* coActor = findActor(castId);
                if (coActor) {
                    //if they already in the list, dont add to the vector
                    bool alreadyExists = false;
                    for (const string& existingName : coActorNames) {
                        if (existingName == coActor->name) {
                            alreadyExists = true;
                            break;
                        }
                    }
                    if (!alreadyExists) {
                        coActorNames.push_back(coActor->name);
                    }
                }
            }
        }
    }

    if (coActorNames.empty()) {
        cout << actor->name << " has not worked with any other actors.\n";
        return;
    }

    // Sort alphabetically
    if (coActorNames.size() > 1) {
        quickSort(coActorNames, 0, coActorNames.size() - 1);
    }

    cout << "\nActors who have worked with " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& coActor : coActorNames) {
        cout << "- " << coActor << "\n";
    }
}

void Graph::displayActorsByRating() {
    cout << "\nActors displayed by rating :\n";
    cout << "----------------------------------------" << endl;

    vector<Actor*> allActors = actorDict->getAllActors();
    vector<pair<string, int>> sortedActors;

    for (Actor* actor : allActors) {
        if (actor->ratingCount != 0) {
            sortedActors.push_back(make_pair(actor->name, actor->rating));
        }
        
    }
    if (sortedActors.empty()) {
        cout << "No actors have ratings yet." << endl;
        return;
    }
    if (sortedActors.size() > 1) {
        quickSort(sortedActors, 0, sortedActors.size() - 1);
    }
    for (auto i = sortedActors.rbegin(); i != sortedActors.rend(); i++) {
        cout << (sortedActors.rend() - i) << ". "
            << left << setw(30) << i->first
            << "Rating (/5): " << i->second << endl;
    }
}

void Graph::displayMoviesByRating() {
    cout << "\nMovies displayed by rating :\n";
    cout << "----------------------------------------" << endl;

    vector<Movie*> allMovies = movieDict->getAllMovies();
    vector<pair<string, int>> sortedMovies;

    for (Movie* movie : allMovies) {
        if (movie->ratingCount != 0) {
            sortedMovies.push_back(make_pair(movie->title, movie->rating));
        }
    }
    if (sortedMovies.empty()) {
        cout << "No movies have ratings yet." << endl;
        return;
    }
    if (sortedMovies.size() > 1) {
        quickSort(sortedMovies, 0, sortedMovies.size() - 1);
    }
    for (auto i = sortedMovies.rbegin(); i != sortedMovies.rend(); i++) {
        cout << (sortedMovies.rend() - i) << ". "
            << left << setw(30) << i->first
            << "Rating (/5): " << i->second << endl;
    }
}
