#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <vector>

// Constructor for the Graph class to initialize the Dictionaries for Actors and Movies to map a 1 to 2 relationship
Graph::Graph() {
    actorDict = new Dictionary(true, this);
    movieDict = new Dictionary(false, this);
}


// Destructor for the Graph class to delete the Dictionaries for Actors and Movies
Graph::~Graph() {
    delete actorDict;
    delete movieDict;
}

// Update the rating of an actor by calling the updateActorRating method in the Dictionary class for actors and passing the key and rating as parameters to the method
bool Graph::updateActorRating(int key, double rating) {
    return actorDict->updateActorRating(key, rating);
}

// Update the rating of a movie by calling the updateMovieRating method in the Dictionary class for movies and passing the key and rating as parameters to the method
bool Graph::updateMovieRating(int key, double rating) {
    return movieDict->updateMovieRating(key, rating);
}

// Find an actor by calling the getActor method in the Dictionary class for actors and passing the id as a parameter to the method
Actor* Graph::findActor(int id) {
    return actorDict->getActor(id);
}

// Find a movie by calling the getMovie method in the Dictionary class for movies and passing the id as a parameter to the method
Movie* Graph::findMovie(int id) {
    return movieDict->getMovie(id);
}

// Add an actor by calling the addActor method in the Dictionary class for actors and passing the id, name, birthYear, rating, and ratingCount as parameters to the method
bool Graph::addActor(int id, string name, int birthYear, double rating, int ratingCount) {
    return actorDict->addActor(id, name, birthYear, rating, ratingCount);
}

// Add a movie by calling the addMovie method in the Dictionary class for movies and passing the id, title, year, plot, rating, and ratingCount as parameters to the method
bool Graph::addMovie(int id, string title, int year, string plot, double rating, int ratingCount) {
    return movieDict->addMovie(id, title, year, plot, rating, ratingCount);
}

/* Models the graph and its relationships by adding an edge between an actor and a movie
Add an edge between an actor and a movie by calling the addRelationship method in the Dictionary class for actors and passing the actorId and movieId as parameters to the method */ 
bool Graph::addEdge(int actorId, int movieId) {
    // Add relationship in both dictionaries (the addrelationship method will add in both so lets just call one)
    if (!actorDict->addRelationship(actorId, movieId)) {
        return false;
    }
    return true;
}

// Sorting helper functions

// Quick sort algorithm for sorting a vector of pairs of strings and integers by the integer value in ascending order - used by displayActorsByAge 
void Graph::quickSort(vector<pair<string, int>>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);
        if (pivot > 0) quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Quick sort algorithm for sorting a vector of pairs of strings and doubles by the double value in ascending order - used by displayActorsByRating and displayMoviesByRating
void Graph::quickSort(vector<pair<string, double>>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);
        if (pivot > 0) quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Quick sort algorithm for sorting a vector of pairs of strings and doubles in alphabetical order - used by displayActorMovies and displayMovieCast
size_t Graph::partition(vector<pair<string, double>>& arr, size_t low, size_t high) {
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

// Partition function for quick sort algorithm for sorting a vector of pairs of strings and integers by the integer value in ascending order - used by displayActorsByAge
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

// Quick sort algorithm for sorting a vector of strings in alphabetical order - used by displayActorNetwork
void Graph::quickSort(vector<string>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);
        if (pivot > 0) quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Partition function for quick sort algorithm for sorting a vector of strings in alphabetical order - used by displayActorNetwork
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

// Merge sort algorithm for sorting a vector of MovieInfo structs by year in ascending order - used by displayRecentMovies
void Graph::mergeSort(vector<MovieInfo>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge function for merge sort algorithm for sorting a vector of MovieInfo structs by year in ascending order - used by displayRecentMovies
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

// Display actors by age range by taking the start and end age as input and displaying the actors within that age range along with their ages
void Graph::displayActorsByAge(int startAge, int endAge) {
    // Prompt user for current year
    int currentYear;
    cout << "Enter the current year: ";
    cin >> currentYear;

	// Get all actors from the actor dictionary and store them in a vector
    vector<Actor*> allActors = actorDict->getAllActors();
    vector<pair<string, int>> matchingActors;

    // Filter actors by age
    for (Actor* actor : allActors) {
        int age = currentYear - actor->birthYear;
        if (age >= startAge && age <= endAge) {
            matchingActors.push_back(make_pair(actor->name, age));
        }
    }

	// Check if no actors were found
    if (matchingActors.empty()) {
        cout << "No actors found in the specified age range." << endl;
        return;
    }

    // Sort by age using quickSort
    if (matchingActors.size() > 1) {
        quickSort(matchingActors, 0, matchingActors.size() - 1);
    }

	// Display actors by age
    cout << "\nActors between " << startAge << " and " << endAge << " years old:" << endl;
    cout << "----------------------------------------" << endl;

	// Display actors and their ages in the specified age range along with the total number of actors found
    for (size_t i = 0; i < matchingActors.size(); i++) {
        cout << (i + 1) << ". " << left << setw(30) << matchingActors[i].first
            << "Age: " << matchingActors[i].second << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Total actors found: " << matchingActors.size() << endl;
}


// Display recent movies by displaying movies from the past 3 years along with their plots
void Graph::displayRecentMovies() {
	// Prompt user for current year
    int currentYear;
    cout << "Enter the current year: ";
    cin >> currentYear;


	// Get all movies from the movie dictionary and store them in a vector of MovieInfo structs to store the title, year, and plot of each movie
    vector<Movie*> allMovies = movieDict->getAllMovies();
    vector<MovieInfo> recentMovies;

	// Filter movies by the past 3 years
    for (Movie* movie : allMovies) {
        int yearDiff = currentYear - movie->year;
        if (yearDiff >= 0 && yearDiff <= 3) {
			recentMovies.emplace_back(movie->title, movie->year, movie->plot); // Add movie to vector of MovieInfo structs, emplace_back avoids creating a temporary object and moves the object directly into the vector
        }
    }

	// Check if no recent movies were found
    if (recentMovies.empty()) {
        cout << "No recent movies found." << endl;
        return;
    }

    // Sort by year using mergesort
    mergeSort(recentMovies, 0, recentMovies.size() - 1);

	// Display recent movies along with their plots
    cout << "\nMovies from the past 3 years:" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& movie : recentMovies) {
        cout << movie.title << " (" << movie.year << ")" << endl;
        cout << "Plot: " << movie.plot << endl << endl;
    }
}

// Display movies starring a specific actor by taking the actorId as input and displaying the movies that the actor has starred in
void Graph::displayActorMovies(int actorId) {
	// Find actor by actorId and store in actor variable if found
    Actor* actor = findActor(actorId);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

	// Get movies from the actor dictionary for the actorId and store them in a vector of Movie pointers to store the movies that the actor has starred in
    vector<Movie*> movies = actorDict->getActorMovies(actorId);
    vector<string> movieTitles;

    // Get movie titles
    for (Movie* movie : movies) {
        if (movie) {
			movieTitles.push_back(movie->title); // Add movie title to vector of movie titles if movie is not null
        }
    }

	// Check if no movies were found
    if (movieTitles.empty()) {
        cout << "No movies found for " << actor->name << ".\n";
        return;
    }

	// Sort alphabetically using quickSort
    if (movieTitles.size() > 1) {
        quickSort(movieTitles, 0, movieTitles.size() - 1);
    }

	// Display movies starring the actor along with the total number of movies found
    cout << "\nMovies starring " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& title : movieTitles) {
        cout << "- " << title << "\n";
    }
}


// Display the cast of a specific movie by taking the movieId as input and displaying the cast of that specific movie
void Graph::displayMovieCast(int movieId) {
	// Find movie by movieId and store in movie variable if found
    Movie* movie = findMovie(movieId);
    if (!movie) {
        cout << "Movie not found.\n";
        return;
    }

	// Get actors from the movie dictionary for the movieId and store them in a vector of Actor pointers to store the actors that starred in the movie
    vector<Actor*> actors = movieDict->getMovieActors(movieId);
    vector<string> actorNames;

    // Get actor names
    for (Actor* actor : actors) {
        if (actor) {
            actorNames.push_back(actor->name);
        }
    }

	// Check if no actors were found
    if (actorNames.empty()) {
        cout << "No cast found for " << movie->title << ".\n";
        return;
    }

	// Sort alphabetically using quickSort
    if (actorNames.size() > 1) {
        quickSort(actorNames, 0, actorNames.size() - 1);
    }

	// Display cast of the movie
    cout << "\nCast of " << movie->title << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& name : actorNames) {
        cout << "- " << name << "\n";
    }
}


// Display the network of actors that have worked with a specific actor by taking the actorId as input and displaying the actors that have worked with the specific actor
void Graph::displayActorNetwork(int actorId) {
	// Find actor by actorId and store in actor variable if found
    Actor* actor = findActor(actorId);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

	// Get all actors from the actor dictionary and store them in a vector of Actor pointers to store all actors
    vector<string> coActorNames;
    vector<Movie*> actorMovies = actorDict->getActorMovies(actorId);

	// Get all actors that have worked with the actor
    // For each movie the actor was in
    for (Movie* movie : actorMovies) {
        vector<Actor*> castActors = movieDict->getMovieActors(movie->id);

        // For each actor in that movie
        for (Actor* coActor : castActors) {
			// Check if the id is the actor itself
            if (coActor->id != actorId) {
				// Check if the actor is already in the list
                if (coActor) {
                    // If they are already in the list, don't add to the vector
                    bool alreadyExists = false;
                    for (const string& existingName : coActorNames) {
                        if (existingName == coActor->name) {
                            alreadyExists = true;
                            break;
                        }
                    }

					// If they are not in the list, add to the vector
                    if (!alreadyExists) {
                        coActorNames.push_back(coActor->name);
                    }
                }
            }
        }
    }

	// Check if no actors were found
    if (coActorNames.empty()) {
        cout << actor->name << " has not worked with any other actors.\n";
        return;
    }

	// Sort alphabetically using quickSort
    if (coActorNames.size() > 1) {
        quickSort(coActorNames, 0, coActorNames.size() - 1);
    }

	// Display actors that have worked with the specific actor
    cout << "\nActors who have worked with " << actor->name << ":\n";
    cout << "----------------------------------------" << endl;
    for (const string& coActor : coActorNames) {
        cout << "- " << coActor << "\n";
    }
}

// Display actors by rating by displaying actors along with their ratings in descending order
void Graph::displayActorsByRating() {
    cout << "\nActors displayed by rating :\n";
    cout << "----------------------------------------" << endl;

	// Get all actors from the actor dictionary and store them in a vector of Actor pointers to store all actors
    vector<Actor*> allActors = actorDict->getAllActors();
    vector<pair<string, double>> sortedActors;

	// Filter actors by rating count and add to sortedActors vector
    for (Actor* actor : allActors) {
        if (actor->ratingCount != 0) {
            sortedActors.push_back(make_pair(actor->name, actor->rating));
        }
    }

	// Check if no actors were found
    if (sortedActors.empty()) {
        cout << "No actors have ratings yet." << endl;
        return;
    }

	// Sort by rating using quickSort
    if (sortedActors.size() > 1) {
        quickSort(sortedActors, 0, sortedActors.size() - 1);
    }
    
	// Display actors by rating
    for (auto i = sortedActors.rbegin(); i != sortedActors.rend(); i++) {
        cout << (i - sortedActors.rbegin() + 1) << ". "
            << left << setw(30) << i->first
            << "Rating: " << fixed << setprecision(2) << i->second << "/5" << endl;
    }

}

// Display movies by rating by displaying movies along with their ratings in descending order
void Graph::displayMoviesByRating() {
    cout << "\nMovies displayed by rating :\n";
    cout << "----------------------------------------" << endl;

	// Get all movies from the movie dictionary and store them in a vector of Movie pointers to store all movies
    vector<Movie*> allMovies = movieDict->getAllMovies();
    vector<pair<string, double>> sortedMovies;

    // Filter movies by rating count and add to sortedMovies vector
    for (Movie* movie : allMovies) {
        if (movie->ratingCount != 0) {
            sortedMovies.push_back(make_pair(movie->title, movie->rating));
        }
    }

	// Check if no movies were found
    if (sortedMovies.empty()) {
        cout << "No movies have ratings yet." << endl;
        return;
    }

	// Sort by rating using quickSort
    if (sortedMovies.size() > 1) {
        quickSort(sortedMovies, 0, sortedMovies.size() - 1);
    }

	// Display movies by rating
    for (auto i = sortedMovies.rbegin(); i != sortedMovies.rend(); i++) {
        cout << (i - sortedMovies.rbegin() + 1) << ". "
            << left << setw(30) << i->first
            << "Rating: " << fixed << setprecision(2) << i->second << "/5" << endl;
    }
}
