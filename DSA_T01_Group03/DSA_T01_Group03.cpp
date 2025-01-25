#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.h"
#include "Dictionary.h"

using namespace std;

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
                    << "6 - Rate an actor\n"
                    << "7 - Rate a movie\n"
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
                    movieGraph.displayRecentMovies();
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
            }
        }
    }
    return 0;
}

void rateActor(const string& filename, Graph& graph, int id, double rating) {
    auto actor = graph.findActor(id);
    if (actor) {
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

void rateMovie(const string& filename, Graph& graph, int id, double rating) {
    auto movie = graph.findMovie(id);
    if (movie) {
        graph.updateMovieRating(id, rating);

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
            string idStr, title, plot, year, oldRating, oldRatingCount;

            getline(ss, idStr, ',');
            getline(ss, title, ',');

            // Properly extract the plot, handling quotes
            if (line.find('"') != string::npos) {
                // Find first and last quotes to get full plot text
                size_t firstQuote = line.find('"');
                size_t lastQuote = line.find('"', firstQuote + 1);
                plot = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                // Adjust stream position to skip past the plot field
                ss.ignore(lastQuote + 2 - (firstQuote + 1));
            }
            else {
                getline(ss, plot, ',');
            }

            getline(ss, year, ',');
            getline(ss, oldRating, ',');
            getline(ss, oldRatingCount);

            try {
                int currentId = stoi(idStr);
                if (currentId == id) {
                    string updatedLine = idStr + "," +
                        title + "," +
                        "\"" + plot + "\"," +  // Ensure quotes around plot
                        year + "," +
                        to_string(movie->rating) + "," +
                        to_string(movie->ratingCount);
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
            cout << "Movie with ID " << id << " not found in " << filename << ".\n";
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
        cout << "Movie rating updated successfully in " << filename << " and graph.\n";
    }
    else {
        cout << "Movie with ID " << id << " not found in the graph.\n";
    }
}


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
        int id = 0, year = 0, ratingcnt = 0;
        double rating = 0.0;
        string title, plot;

        size_t pos = 0;
        bool inQuotes = false;
        string currentField;
        int fieldCount = 0;

        // Parse the line character by character to handle quoted fields correctly
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;  // Toggle inside/outside quotes
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
                    if (!currentField.empty() && currentField.front() == '"' && currentField.back() == '"') {
                        currentField = currentField.substr(1, currentField.length() - 2);
                    }
                    title = currentField;
                    break;
                case 2: // Plot
                    if (!currentField.empty() && currentField.front() == '"' && currentField.back() == '"') {
                        currentField = currentField.substr(1, currentField.length() - 2);
                    }
                    plot = currentField;
                    break;
                case 3: // Year
                    try {
                        year = stoi(currentField);
                    }
                    catch (...) {
                        cout << "Invalid year in line: " << line << endl;
                        goto nextLine;
                    }
                    break;
                case 4: // Rating (optional)
                    try {
                        rating = currentField.empty() ? 0.0 : stod(currentField);
                    }
                    catch (...) {
                        rating = 0.0;
                    }
                    break;
                }
                currentField.clear();
                fieldCount++;
            }
            else {
                currentField += c;
            }
        }

        // Process the last field (rating count, optional)
        try {
            ratingcnt = currentField.empty() ? 0 : stoi(currentField);
        }
        catch (...) {
            ratingcnt = 0;
        }

        // Add to graph (false indicates it's a movie, not an actor)
        if (graph.addMovie(id, title, year, plot, rating, ratingcnt)) {
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