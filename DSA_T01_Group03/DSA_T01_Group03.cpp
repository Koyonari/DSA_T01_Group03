#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
#include "Dictionary.h"

using namespace std;

void importActorCSV(const string& filename, Graph& graph);
void importMovieCSV(const string& filename, Graph& graph);
void importCastCSV(const string& filename, Graph& graph);
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

    cout << "Importing data..." << endl;
    importActorCSV("actors.csv", movieGraph);
    cout << "Actors imported successfully" << endl;
    importMovieCSV("movies.csv", movieGraph);
    cout << "Movies imported successfully" << endl;
    importCastCSV("cast.csv", movieGraph);
    cout << "Cast imported successfully" << endl;

    while (true) {
        cout << "\n----------------------MOVIE WIKI----------------------\n";
        cout << "Welcome to Movie Wiki! This program allows you to add, update, and track movies and actors.\n";
        cout << "1 - Administrator access \n2 - User access\n0 - Exit\nEnter access: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            cout << "Enter admin password: ";
            string password;
            cin >> password;

            if (password == "admin123") {
                cout << "Access granted!\n------------------------------------------------------\n";
                while (true) {
                    cout << "\nOperations\n1 - Add new actor\n2 - Add new movie\n"
                        << "3 - Add an actor to a movie\n4 - Update actor details\n"
                        << "5 - Update movie details\n0 - Exit\nEnter operation: ";
                    int operation;
                    cin >> operation;

                    if (operation == 0) break;

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
                    else if (operation == 3) {
                        cout << "Enter actor ID: ";
                        int actorId;
                        cin >> actorId;
                        cout << "Enter movie ID: ";
                        int movieId;
                        cin >> movieId;

                        appendCastToCSV("cast.csv", actorId, movieId, movieGraph);
                    }
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
            while (true) {
                cout << "\n------------------------------------------------------\n";
                cout << "Operations\n1 - Display actors according to age\n"
                    << "2 - Display movies made within the past 3 years\n"
                    << "3 - Display all movies an actor starred in alphabetical order\n"
                    << "4 - Display all actors in a particular movie in alphabetical order\n"
                    << "5 - Display a list of all actors that a particular actor knows\n"
                    << "0 - Exit\nEnter operation: ";
                int operation;
                cin >> operation;

                if (operation == 0) break;

                if (operation == 1) {
                    cout << "Enter starting age (inclusive): ";
                    int age1;
                    cin >> age1;
                    cout << "Enter ending age (inclusive): ";
                    int age2;
                    cin >> age2;
                    movieGraph.displayActorsByAge(age1, age2);
                }
                else if (operation == 2) {
                    movieGraph.displayRecentMovies(2024);
                }
                else if (operation == 3) {
                    cout << "Enter actor ID: ";
                    int actorId;
                    cin >> actorId;
                    movieGraph.displayActorMovies(actorId);
                }
                else if (operation == 4) {
                    cout << "Enter movie ID: ";
                    int movieId;
                    cin >> movieId;
                    movieGraph.displayMovieCast(movieId);
                }
                else if (operation == 5) {
                    cout << "Enter actor ID: ";
                    int actorId;
                    cin >> actorId;
                    movieGraph.displayActorNetwork(actorId);
                }
            }
        }
    }
    return 0;
}

void importActorCSV(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header
    int count = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, birthStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, birthStr, ',');

        if (!name.empty() && name[0] == '"' && name[name.size() - 1] == '"') {
            name = name.substr(1, name.size() - 2);
        }

        try {
            int id = stoi(idStr);
            int birth = stoi(birthStr);
            if (graph.addActor(id, name, birth)) {
                count++;
                if (count % 100 == 0) {
                    cout << "Processed " << count << " actors...\r";
                }
            }
        }
        catch (const invalid_argument& e) {
            cout << "Skipping invalid row: " << line << endl;
        }
    }
    cout << "Imported " << count << " actors successfully." << endl;
    file.close();
}
void importMovieCSV(const string& filename, Graph& graph) {
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
        // Variables to store parsed data
        int id, year;
        string title, plot;

        // State variables for parsing
        size_t pos = 0;
        bool inQuotes = false;
        string currentField;
        int fieldCount = 0;

        // Parse the line character by character
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            }
            else if (c == ',' && !inQuotes) {
                // Process the completed field
                switch (fieldCount) {
                case 0: // ID
                    try {
                        id = stoi(currentField);
                    }
                    catch (...) {
                        cout << "Invalid ID in line: " << line << endl;
                        goto nextLine;
                    }
                    break;
                case 1: // Title
                    // Remove quotes if present
                    if (currentField.front() == '"' && currentField.back() == '"') {
                        currentField = currentField.substr(1, currentField.length() - 2);
                    }
                    title = currentField;
                    break;
                case 2: // Plot
                    // Remove quotes if present
                    if (currentField.front() == '"' && currentField.back() == '"') {
                        currentField = currentField.substr(1, currentField.length() - 2);
                    }
                    plot = currentField;
                    break;
                }
                currentField.clear();
                fieldCount++;
            }
            else {
                currentField += c;
            }
        }

        // Process the last field (year)
        try {
            year = stoi(currentField);
        }
        catch (...) {
            cout << "Invalid year in line: " << line << endl;
            continue;
        }

        // Add to graph (false indicates it's a movie, not an actor)
        if (graph.addMovie(id, title, year, plot)) {
            count++;
            if (count % 100 == 0) {
                cout << "Processed " << count << " movies...\r";
            }
        }

    nextLine:
        continue;
    }

    cout << "Imported " << count << " movies successfully." << endl;
    file.close();
}

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

void appendActorToCSV(const string& filename, int id, const string& name, int birthYear, Graph& graph) {
    if (graph.addActor(id, name, birthYear)) { //add actor to the graph
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

void updateActorInCSV(const string& filename, int id, const string& newName, int newBirthYear, Graph& graph) {
    auto actor = graph.findActor(id);   //update the graph also
    if (actor) {
        actor->name = newName;
        actor->birthYear = newBirthYear;  

        ifstream inFile(filename);
        ofstream tempFile("temp.csv");

        if (!inFile.is_open() || !tempFile.is_open()) {
            cout << "Error: Could not open files" << endl;
            return;
        }

        string line;
        bool found = false;

        //header line
        getline(inFile, line);
        tempFile << line << "\n";

        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, name, birthStr;

            //get the id
            getline(ss, idStr, ',');

            try {
                int currentId = stoi(idStr);

                if (currentId == id) {
                    //updated info
                    tempFile << id << ",\"" << newName << "\"," << newBirthYear << "\n";
                    found = true;
                }
                else {
                    //write original line
                    tempFile << line << "\n";
                }
            }
            catch (const invalid_argument& e) {
                tempFile << line << "\n"; //continue if cannot
            }
        }

        inFile.close();
        tempFile.close();

        //replace original file with updated file
        if (found) {
            remove(filename.c_str());
            rename("temp.csv", filename.c_str());
            cout << "Actor updated in " << filename << " and graph successfully.\n";
        }
        else {
            remove("temp.csv");
            cout << "Actor with ID " << id << " not found in " << filename << ".\n";
        }
    }
    else {
        cout << "Actor with ID " << id << " not found in the graph.\n";
    }
}

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

void updateMovieInCSV(const string& filename, int id, const string& newTitle, int newYear, const string& newPlot, Graph& graph) {
    auto movie = graph.findMovie(id); // Update the graph also
    if (movie) {
        if (!newTitle.empty()) movie->title = newTitle;
        if (newYear != 0) movie->year = newYear;
        if (!newPlot.empty()) movie->plot = newPlot;

        ifstream inFile(filename);
        ofstream tempFile("temp.csv");

        if (!inFile.is_open() || !tempFile.is_open()) {
            cout << "Error: Could not open files" << endl;
            return;
        }

        string line;
        bool found = false;

        // Copy the header line
        getline(inFile, line);
        tempFile << line << "\n";

        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, title, plot, yearStr;

            // Extract fields
            getline(ss, idStr, ',');
            getline(ss, title, ',');
            getline(ss, plot, ',');
            getline(ss, yearStr, ',');

            try {
                int currentId = stoi(idStr);

                if (currentId == id) {
                    // Write updated movie details
                    tempFile << id << ",\"" << newTitle << "\",\"" << newPlot << "\"," << newYear << "\n";
                    found = true;
                }
                else {
                    // Write original line
                    tempFile << line << "\n";
                }
            }
            catch (const invalid_argument& e) {
                tempFile << line << "\n"; // Continue if unable to parse
            }
        }

        inFile.close();
        tempFile.close();

        // Replace original file with updated file
        if (found) {
            remove(filename.c_str());
            rename("temp.csv", filename.c_str());
            cout << "Movie updated in " << filename << " and graph successfully.\n";
        }
        else {
            remove("temp.csv");
            cout << "Movie with ID " << id << " not found in " << filename << ".\n";
        }
    }
    else {
        cout << "Movie with ID " << id << " not found in the graph.\n";
    }
}

void appendMovieToCSV(const string& filename, int id, const string& title, int year, const string& plot, Graph& graph) {
    if (graph.addMovie(id, title, year, plot)) { // Add movie to the graph
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
