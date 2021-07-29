#include <iostream>
#include <fstream>

#include "terminal-display.h"
#include "creatures.h"

using namespace TerminalDisplayFeatures;
using namespace CreaturesFeatures;

TerminalDisplay terminalDisplay = TerminalDisplay();

void
Menu();

Player
LoadPlayer() {
    std::ifstream MyReadFile("data/player.txt");
    if (!MyReadFile.is_open()) {
        std::cerr << "Could not open the file - '"
             << "player.txt" << "'\n";
        EXIT_FAILURE;
    }

    std::map<std::string, int> playerStats;
    std::vector<std::string> playerStatsOrder {
     {"maxHealth"},
     {"maxSkillsPoints"},
     {"level"},
     {"totalExperience"}
    };

    int number;
    for (int i = 0; MyReadFile >> number; i++) {
        playerStats.emplace(playerStatsOrder[i], number);
    }

    MyReadFile.close();

    Player player = Player("Adolfo", playerStats);
    return player;
}

// Enemy


Enemy
LoadEnemy(std::string monsterName){
    std::ifstream MyReadFile("data/"+ monsterName +".txt");
    if (!MyReadFile.is_open()) {
        std::cerr << "Could not open the file - '"
             << "data/" << monsterName << ".txt" << "'\n";
        EXIT_FAILURE;
    }
    std::map<std::string, int> stats;
    std::vector<std::string> statsOrder {
     {"maxHealth"},
     {"maxSkillsPoints"},
     {"experience"}
    };

    int value;
    for (int i = 0; MyReadFile >> value; i++) {
        stats.emplace(statsOrder[i], value);
    }

    MyReadFile.close();

    Enemy enemy = Enemy(monsterName, stats);
    return enemy;
}

void
SavePlayer(const Player player) {

    std::ofstream myfile;
    myfile.open ("data/player.txt");
    myfile << player.GetMaxHealth() << "\n";
    myfile << "9999" << "\n";
    myfile << player.GetLevel() << "\n";
    myfile << player.GetExperience() << "\n";
    myfile.close();

}

std::map<std::string, int> 
ReadStatsFromFile(std::string creatureName) {
    std::map<std::string, int> creatureStats = {
        {"maxHealth", 100},
        {"maxSkillsPoints", 10}
    };
    return creatureStats;
}

void
SkillsMenuInBattle(const Player player, const Enemy enemy) {
    terminalDisplay.PrintBattle(player, enemy, BattleMenuOptions::kSkills);

    //Reading player choice
    char choice;
    std::cin >> choice;
}

void
ItemsMenuInBattle(const Player player, const Enemy enemy) {
    terminalDisplay.PrintBattle(player, enemy, BattleMenuOptions::kItems);

    //Reading player choice
    char choice;
    std::cin >> choice;
}

void
BattleResults(Player& player, const Enemy enemy, bool playerWon) {
    if (playerWon) {
        player.AddExperience(enemy.GetExperience());
        while (player.GetExperience() >= player.GetNextLevelExperience()) {
            player.AddLevel();
            std::cout << "!!LEVEL UP to level: " << player.GetLevel();
        }
    }
    SavePlayer(player);
    char choice;
    std::cin >> choice;
    Menu();
}

void
Battle() {
    std::map<std::string, int> playerStats = ReadStatsFromFile("player");
    std::map<std::string, int> enemyStats = ReadStatsFromFile("monstername");

    Player player = LoadPlayer();
    Enemy enemy = LoadEnemy("troll");

    // Previous loading version
    // Player player = Player("player", ReadStatsFromFile("player"));
    // Enemy enemy = Enemy("rat", ReadStatsFromFile("rat"));

    bool playerWon = false;
    bool enemyWon = false;
    bool battleOver = false;

    while (!playerWon && !enemyWon && !battleOver) {
        //printing battle scene
        terminalDisplay.PrintBattle(player, enemy, BattleMenuOptions::kMenu);
        
        //Reading player choice
        char choice;
        std::cin >> choice;

        switch (choice) {
            case '1':
                //Case Attack
                if (player.Attack(enemy)) {
                    playerWon = true;
                    break;
                }
                if (enemy.Attack(player)) {
                    enemyWon = true;
                    break;
                }
                break;
            case '2':
                //Case Items
                ItemsMenuInBattle(player, enemy);
                break;
            case '3':
                //Case Skills
                SkillsMenuInBattle(player, enemy);
                break;
            case '4':
                //Case Exit
                battleOver = true;
                break;
            default:
                break;
        }
    }

    if (battleOver) {
        Menu();
    } else {
        terminalDisplay.PrintBattleResults(player, enemy, playerWon);
        BattleResults(player, enemy, playerWon);
    }
}

void
WorldMap() {
    //printing world map
    terminalDisplay.DisplayScene(SceneState::kWorldMap);

    //Reading choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            Battle();
            break;

        default:
            break;
    }
}

void
Status() {
    //printing status
    terminalDisplay.DisplayScene(SceneState::kStatus);

    //Reading player choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        //There is no cases for now
        default:
            Menu();
            break;
    }
}

void
Menu() {
    //printing menu
    terminalDisplay.DisplayScene(SceneState::kMenu);

    //Reading player choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            terminalDisplay.DisplayScene(SceneState::kWorldMap);
            WorldMap();
            break;
        case '2':
            Status();
            terminalDisplay.DisplayScene(SceneState::kStatus);
        case '0':
            break;
        default:
            break;
    }
}

int
main() {
    Menu();
    return 1;
}