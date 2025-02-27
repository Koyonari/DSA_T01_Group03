#pragma once
#include <string>
#include <vector>
#include "Dictionary.h"
using namespace std;

class Dictionary;

// MovieInfo struct to store a Movie's information
struct MovieInfo {
    string title;
    int year;
    string plot;
    MovieInfo() : title(""), year(0), plot("") {}
    MovieInfo(const string& t, int y, const string& p)
        : title(t), year(y), plot(p) {
    }
};

// Graph class to store the relationship between Actors and Movies
class Graph {
private:
    Dictionary* actorDict;
    Dictionary* movieDict;

    // Sorting helper functions
	// size_t is an unsigned integer that must be positive and is used to store sizes of arrays, strings and memory allocations
    void quickSort(vector<pair<string, int>>& arr, size_t low, size_t high);
    size_t partition(vector<pair<string, int>>& arr, size_t low, size_t high);
    void quickSort(vector<pair<string, double>>& arr, size_t low, size_t high);
    size_t partition(vector<pair<string, double>>& arr, size_t low, size_t high);
    void quickSort(vector<string>& arr, size_t low, size_t high);
    size_t partition(vector<string>& arr, size_t low, size_t high);
    void mergeSort(vector<MovieInfo>& arr, size_t left, size_t right);
    void merge(vector<MovieInfo>& arr, size_t left, size_t mid, size_t right);

public:
    Graph();
    ~Graph();

	// Helper functions
    Actor* findActor(int id);
    Movie* findMovie(int id);
    bool addActor(int id, string name, int birthYear, double rating, int ratingCount);
    bool addMovie(int id, string title, int year, string plot, double rating, int ratingCount);
    bool addEdge(int actorId, int movieId);
    bool updateActorRating(int key, double rating);
    bool updateMovieRating(int key, double rating);

    // Query operations
    void displayActorsByAge(int startAge, int endAge);
    void displayRecentMovies();
    void displayActorMovies(int actorId);
    void displayMovieCast(int movieId);
    void displayActorNetwork(int actorId);
    void displayActorsByRating();
    void displayMoviesByRating();
};