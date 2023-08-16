#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Player {
private:
    string name;
    int health;
    vector<string> inventory;

public:
    Player(string playerName) {
        name = playerName;
        health = 100; // Initial health
    }

    void addToInventory(string item) {
        inventory.push_back(item);
    }

    void displayInventory() {
        cout << "Inventory: ";
        for (int i = 0; i < inventory.size(); i++) {
            cout << inventory[i] << " ";
        }
        cout << endl;
    }

    void decreaseHealth(int amount) {
        health -= amount;
        if (health <= 0) {
            cout << "Game Over! Your health reached zero." << endl;
            exit(0);
        } else {
            cout << "Your health decreased by " << amount << ". Current health: " << health << endl;
        }
    }

    string getName() {
        return name;
    }
};

void saveGame(Player player, string currentRoom) {
    ofstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile << player.getName() << endl;
        saveFile << currentRoom << endl;
        saveFile.close();

        cout << "Game saved successfully!" << endl;
    } else {
        cout << "Unable to save the game." << endl;
    }
}

void loadGame(Player& player, string& currentRoom) {
    ifstream loadFile("save.txt");
    if (loadFile.is_open()) {
        string playerName;
        getline(loadFile, playerName);
        player = Player(playerName);

        getline(loadFile, currentRoom);

        loadFile.close();

        cout << "Game loaded successfully!" << endl;
    } else {
        cout << "No save file found." << endl;
    }
}

int main() {
    string playerName;
    string currentRoom;
    Player player("Player");

    cout << "---- Text-Based Adventure Game ----" << endl;

    // Check for saved game
    cout << "Do you want to load a saved game? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        loadGame(player, currentRoom);
    } else if (choice == 'n') {
        cout << "Enter your name: ";
        cin >> playerName;
        player = Player(playerName);
        currentRoom = "Entrance";
    } else {
        cout << "Invalid choice. Starting a new game." << endl;
        cout << "Enter your name: ";
        cin >> playerName;
        player = Player(playerName);
        currentRoom = "Entrance";
    }

    cout << "Welcome, " << player.getName() << "! You are in the " << currentRoom << "." << endl;

    // Game loop
    while (true) {
        cout << "What would you like to do? ";
        string action;
        cin >> action;

        if (action == "quit") {
            cout << "Quitting the game. Goodbye!" << endl;
            break;
        } else if (action == "look") {
            cout << "You are in the " << currentRoom << "." << endl;
        } else if (action == "inventory") {
            player.displayInventory();
        } else if (action == "save") {
            saveGame(player, currentRoom);
        } else {
            cout << "Invalid action." << endl;
        }
    }

    return 0;
}
