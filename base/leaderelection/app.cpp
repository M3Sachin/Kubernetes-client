#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
public:
    string name;
    int health;
    vector<string> inventory;

    Player(string n) : name(n), health(100) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    void heal(int amount) {
        health += amount;
        if (health > 100) health = 100;
    }

    void addItem(string item) {
        inventory.push_back(item);
    }

    void showStatus() {
        cout << name << "'s Health: " << health << endl;
        cout << "Inventory: ";
        if (inventory.empty()) cout << "(empty)";
        for (string item : inventory) cout << item << ", ";
        cout << endl;
    }
};

class Enemy {
public:
    string name;
    int health;

    Enemy(string n, int h) : name(n), health(h) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() {
        return health > 0;
    }
};

void battle(Player& player, Enemy enemy) {
    cout << "A wild " << enemy.name << " appears!\n";

    while (player.health > 0 && enemy.health > 0) {
        int choice;
        cout << "1. Attack\n2. Run\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            int dmg = rand() % 20 + 5;
            enemy.takeDamage(dmg);
            cout << "You hit the " << enemy.name << " for " << dmg << " damage!\n";

            if (!enemy.isAlive()) {
                cout << "You defeated the " << enemy.name << "!\n";
                break;
            }

            int enemyDmg = rand() % 15 + 5;
            player.takeDamage(enemyDmg);
            cout << enemy.name << " hits you for " << enemyDmg << " damage!\n";
        } else {
            cout << "You run away safely.\n";
            break;
        }
    }
}

void exploreRoom(Player& player) {
    int event = rand() % 4;
    switch (event) {
        case 0:
            cout << "You found a healing potion!\n";
            player.heal(20);
            break;
        case 1:
            cout << "You found a mysterious key.\n";
            player.addItem("Mysterious Key");
            break;
        case 2:
            battle(player, Enemy("Goblin", 30));
            break;
        case 3:
            cout << "The room is empty. You move on.\n";
            break;
    }
}

int main() {
    srand(time(0));

    string playerName;
    cout << "Enter your name, adventurer: ";
    getline(cin, playerName);

    Player player(playerName);

    cout << "Welcome to the Cavern of Fate, " << player.name << "!\n";

    for (int i = 0; i < 5 && player.health > 0; ++i) {
        cout << "\n-- Room " << i + 1 << " --\n";
        exploreRoom(player);
        player.showStatus();
    }

    if (player.health > 0) {
        cout << "\nYou made it out of the cavern alive! Victory!\n";
    } else {
        cout << "\nYou have perished in the cavern...\n";
    }

    return 0;
}