/* -------------------------------------------------------------------------------
DSA Assignment by Group 3
Brandon Koh Ziheng - S10255790
An Yong Shyan - S10258126B
----------------------------------------------------------------------------------
Basic Features Admin Access - Brandon Koh Ziheng
1. Add new actor
2. Add new movie
3. Add an actor to a movie
4. Update actor details
5. Update movie details

Basic Features User Access - An Yong Shyan
1. Display actors according to age
2. Display movies made within the past 3 years
3. Display all movies an actor starred in alphabetical order
4. Display all actors in a particular movie in alphabetical order
5. Display a list of all actors that a particular actor knows
----------------------------------------------------------------------------------
Additional Features (Under User Access) - Brandon Koh Ziheng
1. Rate an actor
2. Rate a movie
3. Display actors by rating
4. Display movies by rating

Additional Features - An Yong Shyan
Used Graph (bi-directional) data structure to improve time complexity by having 
1 to 2 relationships between Graph class and Dictionary class (Actor and Movie).
----------------------------------------------------------------------------------
Helper Functions -  Brandon Koh Ziheng
1. Import Actor CSV
2. Import Movie CSV
3. Import Cast CSV

Helper Functions - An Yong Shyan
1. Partition function
2. Quick Sort algorithm
3. Merge Sort algorithm
------------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.h"
#include "Dictionary.h"

using namespace std;

// Initialise functions
void importActorCSV(const string& filename, Graph& graph);
void importMovieCSV(const string& filename, Graph& graph);
void importCastCSV(const string& filename, Graph& graph);
void rateActor(const string& filename, Graph& graph, int id, double rating);
void rateMovie(const string& filename, Graph& graph, int id, double rating);
void appendActorToCSV(const string& filename, int id, const string& name, int birthYear, Graph& graph);
void updateActorInCSV(const string& filename, int id, const string& newName, int newBirthYear, Graph& graph);
void appendMovieToCSV(const string& filename, int id, const string& title, int year, const string& plot, Graph& graph);
void updateMovieInCSV(const string& filename, int id, const string& newTitle, int newYear, const string& newPlot, Graph& graph);
void appendCastToCSV(const string& filename, int actorid, int movieid, Graph& graph);
int main() {
    Graph movieGraph;

    // Check if files exist before starting import
    cout << "Checking data files..." << endl;
    if (!ifstream("actors.csv")) {
        cout << "Error: actors.csv not found" << endl;
        return 1;
    }
    if (!ifstream("movies.csv")) {
        cout << "Error: movies.csv not found" << endl;
        return 1;
    }
    if (!ifstream("cast.csv")) {
        cout << "Error: cast.csv not found" << endl;
        return 1;
    }


	// Import data from CSV files
    cout << "Importing data..." << endl;
    importActorCSV("actors.csv", movieGraph);
    cout << "Actors imported successfully" << endl;
    importMovieCSV("movies.csv", movieGraph);
    cout << "Movies imported successfully" << endl;
    importCastCSV("cast.csv", movieGraph);
    cout << "Cast imported successfully" << endl;


	// Main program loop
    while (true) {
        cout << "\n----------------------MOVIE WIKI----------------------\n";
        cout << "Welcome to Movie Wiki! This program allows you to add, update, and track movies and actors.\n";
        cout << "1 - Administrator access \n2 - User access\n0 - Exit\nEnter access: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            // Prompt user for admin password - admin123
            cout << "Enter admin password: ";
            string password;
            cin >> password;

            if (password == "admin123") {
                cout << "Access granted!\n------------------------------------------------------\n";

				// Admin main menu loop
                while (true) {
                    cout << "\nOperations\n1 - Add new actor\n2 - Add new movie\n"
                        << "3 - Add an actor to a movie\n4 - Update actor details\n"
                        << "5 - Update movie details\n0 - Exit\nEnter operation: ";
                    int operation;
                    cin >> operation;

                    // Option - 0
                    if (operation == 0) break;

                    // Option - 1
                    if (operation == 1) {
                        cout << "Enter actor ID: ";
                        int id;
                        cin >> id;
                        cin.ignore();
                        cout << "Enter actor name: ";
                        string name;
                        getline(cin, name);
                        cout << "Enter actor birth year: ";
                        int birthYear;
                        cin >> birthYear;

                     
                        appendActorToCSV("actors.csv", id, name, birthYear, movieGraph);
                    }

                    // Option - 2
                    else if (operation == 2) {
                        cout << "Enter movie ID: ";
                        int id;
                        cin >> id;
                        cin.ignore();
                        cout << "Enter movie title: ";
                        string title;
                        getline(cin, title);
                        cout << "Enter release year: ";
                        int year;
                        cin >> year;
                        cin.ignore();
                        cout << "Enter movie plot: ";
                        string plot;
                        getline(cin, plot);

                        appendMovieToCSV("movies.csv", id, title, year, plot, movieGraph);
                    }

                    // Option - 3
                    else if (operation == 3) {
                        cout << "Enter actor ID: ";
                        int actorId;
                        cin >> actorId;
                        cout << "Enter movie ID: ";
                        int movieId;
                        cin >> movieId;

                        appendCastToCSV("cast.csv", actorId, movieId, movieGraph);
                    }

					// Option - 4
                    else if (operation == 4) {
                        cout << "Enter actor ID to update: ";
                        int id;
                        cin >> id;
                        cin.ignore();
                        cout << "Enter new name (or press Enter to skip): ";
                        string name;
                        getline(cin, name);
                        cout << "Enter new birth year (or 0 to skip): ";
                        int birthYear;
                        cin >> birthYear;
                        updateActorInCSV("actors.csv", id, name, birthYear, movieGraph);
                    }

					// Option - 5
                    else if (operation == 5) {
                        cout << "Enter movie ID to update: ";
                        int id;
                        cin >> id;
                        cin.ignore();
                        cout << "Enter new title (or press Enter to skip): ";
                        string title;
                        getline(cin, title);
                        cout << "Enter new year (or 0 to skip): ";
                        int year;
                        cin >> year;
                        cin.ignore();
                        cout << "Enter new plot (or press Enter to skip): ";
                        string plot;
                        getline(cin, plot);

                        updateMovieInCSV("movies.csv", id, title, year, plot, movieGraph);
                    }
                }
            }
            else {
                cout << "Access denied!\n";
            }
        }

        else if (choice == 2) {

			// User main menu loop
            while (true) {
                cout << "\n------------------------------------------------------\n";
                cout << "Operations\n1 - Display actors according to age\n"
                    << "2 - Display movies made within the past 3 years\n"
                    << "3 - Display all movies an actor starred in alphabetical order\n"
                    << "4 - Display all actors in a particular movie in alphabetical order\n"
                    << "5 - Display a list of all actors that a particular actor knows\n"
                    << "6 - Rate an actor\n"
                    << "7 - Rate a movie\n"
                    << "8 - Display actors by rating\n"
                    << "9 - Display movies by rating\n"
                    << "0 - Exit\nEnter operation: ";
                int operation;
                cin >> operation;

                // Option - 0
                if (operation == 0) break;

				// Option - 1
                if (operation == 1) {
                    cout << "Enter starting age (inclusive): ";
                    int age1;
                    cin >> age1;
                    cout << "Enter ending age (inclusive): ";
                    int age2;
                    cin >> age2;
                    movieGraph.displayActorsByAge(age1, age2);
                }

				// Option - 2
                else if (operation == 2) {
                    movieGraph.displayRecentMovies();
                }

                // Option - 3
                else if (operation == 3) {
                    cout << "Enter actor ID: ";
                    int actorId;
                    cin >> actorId;
                    movieGraph.displayActorMovies(actorId);
                }

                // Option - 4
                else if (operation == 4) {
                    cout << "Enter movie ID: ";
                    int movieId;
                    cin >> movieId;
                    movieGraph.displayMovieCast(movieId);
                }

				// Option - 5
                else if (operation == 5) {
                    cout << "Enter actor ID: ";
                    int actorId;
                    cin >> actorId;
                    movieGraph.displayActorNetwork(actorId);
                }

                // Option - 6
                else if (operation == 6) {
                    cout << "Rate an Actor\n";
                    cout << "Enter actor ID: ";
                    int actorId;
                    cin >> actorId;
                    cout << "Enter rating (1-5): ";
                    double rating;
                    cin >> rating;
                    rateActor("actors.csv", movieGraph, actorId, rating);
                }

				// Option - 7
                else if (operation == 7) {
                    cout << "Rate a Movie\n";
                    cout << "Enter movie ID: ";
                    int movieId;
                    cin >> movieId;
                    cout << "Enter rating (1-5): ";
                    double rating;
                    cin >> rating;
                    rateMovie("movies.csv", movieGraph, movieId, rating);
                }

                // Option - 8
                else if (operation == 8) {
                    movieGraph.displayActorsByRating();
                }

                // Option - 9
                else if (operation == 9) {
                    movieGraph.displayMoviesByRating();
                }
            }
        }
    }
    return 0;
}


// Updates the rating of an actor in the CSV file and the graph with the provided rating
// filename: The name of the CSV file to update
// graph: The graph object to update
// id: The ID of the actor to update
// rating: The new rating to set for the actor
void rateActor(const string& filename, Graph& graph, int id, double rating) {

	// Find the actor in the graph 
    auto actor = graph.findActor(id);
    if (actor) {

		// Update the actor's rating in the graph
        graph.updateActorRating(id, rating);
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file" << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool found = false;

        // Read the header and add it to the list
        if (getline(file, line)) {
            lines.push_back(line);  // Add header
        }

        // Read all lines and store them in memory
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, birthYear, oldRating, oldRatingCount;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, birthYear, ',');
            getline(ss, oldRating, ',');
            getline(ss, oldRatingCount);

            try {
                int currentId = stoi(idStr);
                if (currentId == id) {
                    string updatedLine = idStr + "," +
                        name + "," +
                        birthYear + "," +
                        to_string(actor->rating) + "," +
                        to_string(actor->ratingCount);
                    lines.push_back(updatedLine);  // Add updated line
                    found = true;
                }
                else {
                    lines.push_back(line);  // Keep the original line
                }
            }
            catch (const invalid_argument& e) {
                lines.push_back(line);  // Add invalid lines as they are
            }
        }
        file.close();

        if (!found) {
            cout << "Actor with ID " << id << " not found in " << filename << ".\n";
            return;
        }

        // Rewrite the entire CSV file with updated data
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Could not open file for writing" << endl;
            return;
        }

        for (const string& updatedLine : lines) {
            outFile << updatedLine << endl;
        }

        outFile.close();
        cout << "Actor rating updated successfully in " << filename << " and graph.\n";
    }
    else {
        cout << "Actor with ID " << id << " not found in the graph.\n";
    }
}


// Updates the rating of a movie in the CSV file and the graph with the provided rating
// filename: The name of the CSV file to update
// graph: The graph object to update
// id: The ID of the movie to update
// rating: The new rating to set for the movie
void rateMovie(const string& filename, Graph& graph, int id, double rating) {

	// Find the movie in the graph
    auto movie = graph.findMovie(id);
    if (!movie) {
        cout << "Movie with ID " << id << " not found in the graph.\n";
        return;
    }

	// Update the movie's rating in the graph
    graph.updateMovieRating(id, rating);
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    if (getline(file, line)) {
        lines.push_back(line);
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, plot, yearStr, oldRating, oldRatingCount;

        getline(ss, idStr, ',');
        getline(ss, title, ',');

        string plotPart;
        getline(ss, plotPart, ',');
        while (plotPart.front() == '"' && plotPart.back() != '"') {
            string nextPart;
            getline(ss, nextPart, ',');
            plotPart += "," + nextPart;
        }
        plot = plotPart;

        // Read remaining fields separately
        string remainder;
        getline(ss, remainder);
        stringstream remSS(remainder);
        getline(remSS, yearStr, ',');
        getline(remSS, oldRating, ',');
        getline(remSS, oldRatingCount);

        try {
            int currentId = stoi(idStr);
            if (currentId == id) {
                if (plot.front() != '"') plot = "\"" + plot;
                if (plot.back() != '"') plot = plot + "\"";

                string updatedLine = idStr + "," +
                    title + "," +
                    plot + "," +
                    yearStr + "," +
                    to_string(movie->rating) + "," +
                    to_string(movie->ratingCount);
                lines.push_back(updatedLine);
                found = true;
            }
            else {
                lines.push_back(line);
            }
        }
        catch (const invalid_argument& e) {
            lines.push_back(line);
        }
    }
    file.close();

    if (!found) {
        cout << "Movie with ID " << id << " not found in " << filename << ".\n";
        return;
    }

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing" << endl;
        return;
    }

    for (const string& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();
    cout << "Movie rating updated successfully in " << filename << " and graph.\n";
}


// importActorCSV imports Actor objects from the filename, and populates the Graph with these Actor objects (both provided as parameters)
void importActorCSV(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    vector<string> updatedLines;
    string line;

    // Read and store the header
    if (getline(file, line)) {
        updatedLines.push_back(line);  // Keep the header line
        cout << "Skipping header: " << line << endl;
    }

    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, birthStr, ratingStr, ratingCountStr;

        // Extract fields from the CSV line
        getline(ss, idStr, ',');    // Actor ID
        getline(ss, name, ',');     // Actor Name
        getline(ss, birthStr, ','); // Birth Year

        // Remove quotes if present in the name
        if (!name.empty() && name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.length() - 2);
        }

        // Check for rating and ratingCount columns, if missing assign defaults
        if (!getline(ss, ratingStr, ',')) {
            ratingStr = "0";  // Default rating
        }
        if (!getline(ss, ratingCountStr, ',')) {
            ratingCountStr = "0";  // Default rating count
        }

        try {
            int id = stoi(idStr);
            int birthYear = stoi(birthStr);
            double rating = stod(ratingStr);
            int ratingCount = stoi(ratingCountStr);
      
            // Add actor to the graph
            if (graph.addActor(id, name, birthYear, rating, ratingCount)) {
               
                
                count++;
                if (count % 100 == 0) {
                    cout << "Processed " << count << " actors...\r";
                }
            }

            // Store the corrected line to be written back to the file
            updatedLines.push_back(idStr + "," + name + "," + birthStr + "," + ratingStr + "," + ratingCountStr);
        }
        catch (const invalid_argument&) {
            cout << "Skipping invalid row: " << line << endl;
        }
    }

    file.close();

    // Rewrite the same file with updated data
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing" << endl;
        return;
    }

    for (const auto& updatedLine : updatedLines) {
        outFile << updatedLine << "\n";
    }

    outFile.close();

    cout << "Imported " << count << " actors successfully." << endl;
}

// importMovieCSV imports Movie objects from the filename, and populates the Graph with these Movie objects (both provided as parameters)
void importMovieCSV(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    string line;
    if (getline(file, line)) {
        cout << "Skipping header: " << line << endl;
    }
    int count = 0;
    while (getline(file, line)) {
        int id = 0, year = 0, ratingcnt = 0;
        double rating = 0.0;
        string title, plot;
        bool inQuotes = false;
        string currentField;
        int fieldCount = 0;
        vector<string> fields;

        // First pass: split into fields while respecting quotes
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            }
            else if (c == ',' && !inQuotes) {
                fields.push_back(currentField);
                currentField.clear();
            }
            else {
                currentField += c;
            }
        }
        fields.push_back(currentField); // Add last field

        // Process fields based on count
        try {
            id = stoi(fields[0]);

            title = fields[1];
            if (!title.empty() && title.front() == '"' && title.back() == '"') {
                title = title.substr(1, title.length() - 2);
            }

            plot = fields[2];
            if (!plot.empty() && plot.front() == '"' && plot.back() == '"') {
                plot = plot.substr(1, plot.length() - 2);
            }

            // If we have 5 or 6 fields, year is in position 3
            // If we have 4 fields, year is in the last position
            if (fields.size() >= 5) {
                year = stoi(fields[3]);
                rating = fields[4].empty() ? 0.0 : stod(fields[4]);
                ratingcnt = (fields.size() > 5) ? (fields[5].empty() ? 0 : stoi(fields[5])) : 0;
            }
            else if (fields.size() == 4) {
                year = stoi(fields[3]);
            }
        }
        catch (...) {
            cout << "Invalid data in line: " << line << endl;
            continue;
        }

        if (graph.addMovie(id, title, year, plot, rating, ratingcnt)) {
            count++;
            if (count % 100 == 0) {
                cout << "Processed " << count << " movies...\r";
            }
        }
    }
    cout << "Imported " << count << " movies successfully." << endl;
    file.close();
}

// importCastCSV imports Actor and Movie relationships from the filename, and populates the Graph with these relationships (both provided as parameters)
void importCastCSV(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    // Skip the header line
    if (getline(file, line)) {
        cout << "Skipping header: " << line << endl;
    }

    int count = 0;
    while (getline(file, line)) {
        // State variables for parsing
        size_t pos = 0;
        string currentField;
        int fieldCount = 0;
        int actorId, movieId;

        // Parse the line character by character
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == ',') {
                // Process the completed field
                try {
                    if (fieldCount == 0) {
                        actorId = stoi(currentField);
                    }
                    else if (fieldCount == 1) {
                        movieId = stoi(currentField);
                    }
                }
                catch (...) {
                    cout << "Invalid ID in line: " << line << endl;
                    goto nextLine;
                }
                currentField.clear();
                fieldCount++;
            }
            else {
                currentField += c;
            }
        }

        // Process the last field
        try {
            movieId = stoi(currentField);
        }
        catch (...) {
            cout << "Invalid movie ID in line: " << line << endl;
            continue;
        }

        // Add edge to graph
        if (graph.addEdge(actorId, movieId)) {
            count++;
            if (count % 100 == 0) {
               cout << "Processed " << count << " cast relationships...\r";
            }
        }

    nextLine:
        continue;
    }

    cout << "Imported " << count << " cast relationships successfully." << endl;
    file.close();
}

// appendActorToCSV adds a new created Actor to the Graph, as well as the CSV file, so that it can be saved even after the program restarts
void appendActorToCSV(const string& filename, int id, const string& name, int birthYear, Graph& graph) {
    if (graph.addActor(id, name, birthYear, 0, 0)) { //add actor to the graph
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            cout << "Actor was not able to be added successfully.\n";
            return;
        }

        file << id << ",\"" << name << "\"," << birthYear << "\n";
        file.close();
        cout << "Actor successfully added to the graph and " << filename << endl;
    }
    else {
        cout << "Failed to add actor. ID may already exist in the graph.\n";
    }
}

// updateActorInCSV updates an Actor with updated attributes in the Graph, as well as the CSV file, so that changes can be saved even after the program restarts
void updateActorInCSV(const string& filename, int id, const string& newName, int newBirthYear, Graph& graph) {
    auto actor = graph.findActor(id);
    if (actor) {
        if (!newName.empty()) {
            actor->name = newName;
        }
        if (newBirthYear != 0) {
            actor->birthYear = newBirthYear;
        }

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file" << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool found = false;

        // Read the header and add it to the list
        if (getline(file, line)) {
            lines.push_back(line);  // Add header
        }

        // Read all lines and store them in memory
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, existingName, existingBirthYear;
            getline(ss, idStr, ',');
            getline(ss, existingName, ',');
            getline(ss, existingBirthYear);

            try {
                int currentId = stoi(idStr);
                if (currentId == id) {
                    string updatedLine = idStr + ",";

                    updatedLine += (!newName.empty() ? newName : existingName);
                    updatedLine += ",";
                    updatedLine += (newBirthYear != 0 ? to_string(newBirthYear) : existingBirthYear);

                    lines.push_back(updatedLine);  // Add updated line
                    found = true;
                }
                else {
                    lines.push_back(line);  // Keep the original line
                }
            }
            catch (const invalid_argument& e) {
                lines.push_back(line);  // Add invalid lines as they are
            }
        }

        file.close();

        if (!found) {
            cout << "Actor with ID " << id << " not found in " << filename << ".\n";
            return;
        }

        // Rewrite the entire CSV file with updated data
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Could not open file for writing" << endl;
            return;
        }

        for (const string& updatedLine : lines) {
            outFile << updatedLine << endl;
        }

        outFile.close();
        cout << "Actor updated successfully in " << filename << " and graph.\n";
    }
    else {
        cout << "Actor with ID " << id << " not found in the graph.\n";
    }
}

// updateMovieInCSV updates a Movie with updated attributes in the Graph, as well as the CSV file, so that changes can be saved even after the program restarts
void updateMovieInCSV(const string& filename, int id, const string& newTitle, int newYear, const string& newPlot, Graph& graph) {
    auto movie = graph.findMovie(id);
    if (movie) {
        if (!newTitle.empty()) movie->title = newTitle;
        if (newYear != 0) movie->year = newYear;
        if (!newPlot.empty()) movie->plot = newPlot;

        fstream file(filename, ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Error: Could not open file" << endl;
            return;
        }

        string line, header;
        vector<string> lines;
        bool found = false;

        // Read header
        getline(file, header);

        // Read and process lines
        while (getline(file, line)) {
            // Parse line with custom CSV parsing
            size_t idEnd = line.find(',');
            int currentId = stoi(line.substr(0, idEnd));

            if (currentId == id) {
                // Reconstruct the line with updated values
                string updatedLine = to_string(id) + ",";

                // Title
                updatedLine += (!newTitle.empty() ? newTitle :
                    line.substr(idEnd + 1, line.find(',', idEnd + 1) - (idEnd + 1))) + ",";

                // Plot
                size_t plotStart = line.find('"', idEnd);
                size_t plotEnd = line.find('"', plotStart + 1);
                string existingPlot = line.substr(plotStart + 1, plotEnd - (plotStart + 1));
                updatedLine += "\"" + (!newPlot.empty() ? newPlot : existingPlot) + "\",";

                // Year
                updatedLine += (newYear != 0 ? to_string(newYear) :
                    line.substr(line.rfind(',') + 1));

                lines.push_back(updatedLine);
                found = true;
            }
            else {
                lines.push_back(line);
            }
        }

        // Rewrite the file
        file.close();
        ofstream outFile(filename);
        outFile << header << "\n";
        for (const auto& updatedLine : lines) {
            outFile << updatedLine << "\n";
        }
        outFile.close();

        if (found) {
            cout << "Movie updated in " << filename << " and graph successfully.\n";
        }
        else {
            cout << "Movie with ID " << id << " not found in " << filename << ".\n";
        }
    }
    else {
        cout << "Movie with ID " << id << " not found in the graph.\n";
    }
}

// appendActorToCSV adds a new created Movie to the Graph, as well as the CSV file, so that it can be saved even after the program restarts
void appendMovieToCSV(const string& filename, int id, const string& title, int year, const string& plot, Graph& graph) {
    if (graph.addMovie(id, title, year, plot, 0, 0)) { // Add movie to the graph
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            cout << "Movie was not able to be added successfully.\n";
            return;
        }

        file << id << ",\"" << title << "\",\"" << plot << "\"," << year << "\n";
        file.close();
        cout << "Movie successfully added to the graph and " << filename << endl;
    }
    else {
        cout << "Failed to add movie. ID may already exist in the graph.\n";
    }
}

// appendActorToCSV adds a new created Actor and Movie relationship to the Graph, as well as the CSV file, so that it can be saved even after the program restarts
void appendCastToCSV(const string& filename, int actorid, int movieid, Graph& graph) {
    if (graph.addEdge(actorid, movieid)) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            cout << "Actor was not able to be added successfully.\n";
            return;
        }

        file << actorid << "," << movieid << "\n";
        file.close();
        cout << "Actor added to movie successfully!\n";
    }
    else {
        cout << "Failed to add actor to movie.\n";
    }

}