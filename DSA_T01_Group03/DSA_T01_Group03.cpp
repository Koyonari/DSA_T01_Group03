// DSA_T01_Group03 By An Yong Shyan and Brandon Koh
using namespace std;
#include <iostream>
#include "Dictionary.h"
#include "List.h"


int main()
{
	Dictionary actorDict(true);
	Dictionary movieDict(false);
	while (true) {
		cout << "----------------------MOVIE WIKI----------------------\n";
		cout << "Welcome to Movie Wiki! This program allows you to add, update, and track movies and actors.\n";
		cout << "1 - Administrator access \n2 - User access\n0 - Exit\nEnter access: ";
		int choice;
		cin >> choice;
		if (choice == 0) {
			break;
		}
		else if (choice == 1) {
			cout << "Enter admin password: ";
			string password;
			cin >> password;
			if (password == "admin123") {
				cout << "Access granted!\n------------------------------------------------------\n";
				while (true) {
					cout << "Operations\n1 - Add new actor\n2 - Add new movie\n3 - Add an actor to a movie\n4 - Update actor details\n5 - Update movie details\n0 - Exit\nEnter operation: ";
					int operation;
					cin >> operation;
					if (operation == 0) {
						break;
					}
					else if (operation == 1) {
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
						actorDict.add(id, name, birthYear);
						actorDict.print();
					}
					else if (operation == 2) {
						cout << "Enter movie ID: ";
						int id;
						cin >> id;
						cin.ignore();
						cout << "Enter movie title: ";
						string title;
						getline(cin, title);
						cout << "Enter movie year: ";
						int year;
						cin >> year;
						movieDict.add(id, title, year);
						movieDict.print();
					}
					else if (operation == 3) {
						cout << "Enter movie ID: ";
						int movieId;
						cin >> movieId;
						cout << "Enter actor ID: ";
						int actorId;
						cin >> actorId;
						cout << "Enter new movie title: ";
						string title;
						cin >> title;
						cout << "Enter new movie year: ";
						int year;
						cin >> year;
						// Add actor to movie in dictionary method
					}
					else if (operation == 4) {
						cout << "Enter actor ID: ";
						int id;
						cin >> id;
						cin.ignore();
						cout << "Enter new actor name: ";
						string name;
						getline(cin, name);
						cout << "Enter new actor birth year: ";
						int birthYear;
						cin >> birthYear;
						// Update actor in dictionary method
					}
					else if (operation == 5) {
						cout << "Enter movie ID: ";
						int id;
						cin >> id;
						cout << "Enter new movie title: ";
						string title;
						cin >> title;
						cout << "Enter new movie year: ";
						int year;
						cin >> year;
						// Update movie in dictionary method
					}
				}
			}
			else {
				cout << "Access denied!\n\n";
			}
		}
		else if (choice == 2) {
			while (true) {
				cout << "------------------------------------------------------\n";
				cout << "Operations\n1 - Display actors according to age\n2 - Display movies made within the past 3 years\n3 - Display all movies an actor starred in alphabetical order\n4 - Display all actors in a particular movie in alphabetical order\n5 - Display a list of all actors that a particular actor knows\n0 - Exit\nEnter operation: ";
				int operation;
				cin >> operation;
				if (operation == 0) {
					break;
				}
				else if (operation == 1) {
					cout << "Enter starting age (inclusive): ";
					int age1;
					cin >> age1;
					cout << "Enter ending age (inclusive): ";
					int age2;
					cin >> age2;
				}
				else if (operation == 2) {
					// Display movies made within the past 3 years method
				}
				else if (operation == 3) {
					cout << "Enter actor ID: ";
					int id;
					cin >> id;
				}
				else if (operation == 4) {
					cout << "Enter movie ID: ";
					int id;
					cin >> id;
				}
				else if (operation == 5) {
					cout << "Enter actor ID: ";
					int id;
					cin >> id;
				}
			}
		}
		else if (choice == 0) {
			return 1;
		}
	}

	return 0;
}