#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void loadRecipes(map<string, string>& recipes) {
    ifstream infile("recipeDict.txt");
    if (infile) {
        string line;
        while (getline(infile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string recipe = line.substr(pos + 1);
                recipes[name] = recipe;
            }
        }
        infile.close();
    }
}

void saveRecipes(const map<string, string>& recipes) {
    ofstream outfile("recipeDict.txt");
    for (const auto& entry : recipes) {
        outfile << entry.first << ":" << entry.second << endl;
    }
    outfile.close();
}

void editData(map<string, string>& recipes) {
    string name;
    cout << "Enter a recipe name to update: ";
    cin >> name;

    if (recipes.find(name) != recipes.end()) {
        string newRecipe;
        cout << "Enter the new recipe details: ";
        cin.ignore();  // Clear newline from previous input
        getline(cin, newRecipe);
        recipes[name] = newRecipe;
        saveRecipes(recipes);  // Save changes to file
        cout << "Recipe for " << name << " updated." << endl;
    } else {
        cout << name << " not found in the recipe book." << endl;
    }
}

void deleteData(map<string, string>& recipes) {
    string name;
    cout << "Enter a recipe name to delete: ";
    cin >> name;

    if (recipes.find(name) != recipes.end()) {
        recipes.erase(name);
        saveRecipes(recipes);  // Save changes to file
        cout << name << " removed from the recipe book." << endl;
    } else {
        cout << name << " not found in the recipe book." << endl;
    }
}

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Look up recipe\n";
    cout << "2. Add new recipe\n";
    cout << "3. Edit existing recipe\n";
    cout << "4. Delete recipe\n";
    cout << "5. Exit\n";
}

int main() {
    map<string, string> recipes;
    loadRecipes(recipes);

    while (true) {
        displayMenu();
        string choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == "1") {
            string name;
            cout << "Enter recipe name: ";
            cin >> name;
            cout << "Recipe for " << name << ": " << recipes[name] << endl;
        } else if (choice == "2") {
            string name, recipe;
            cout << "Enter recipe name: ";
            cin >> name;
            cout << "Enter recipe details: ";
            cin.ignore();
            getline(cin, recipe);
            recipes[name] = recipe;
            saveRecipes(recipes);
            cout << name << " added to the recipe book." << endl;
        } else if (choice == "3") {
            editData(recipes);
        } else if (choice == "4") {
            deleteData(recipes);
        } else if (choice == "5") {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid choice. Select from 1-5." << endl;
        }
    }

    return 0;
}
