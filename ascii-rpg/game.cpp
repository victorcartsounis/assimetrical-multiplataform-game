#include <iostream>

#include "terminal-display.h"
#include "creatures.h"

using namespace TerminalDisplayFeatures;
using namespace CreaturesFeatures;

TerminalDisplay terminalDisplay = TerminalDisplay();

void
Menu();

void
LoadFOO() {
    //Load Everything
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
Battle() {
    std::map<std::string, int> playerStats = ReadStatsFromFile("player");
    std::map<std::string, int> enemyStats = ReadStatsFromFile("monstername");

    Player player = Player(playerStats);
    Enemy enemy = Enemy(enemyStats);

    bool battleOver = false;
    while (!battleOver) {    
        //printing battle scene
        terminalDisplay.DisplayScene(SceneState::kBattle);
        
        //Reading player choice
        char choice;
        std::cin >> choice;

        switch (choice) {
            case '1':
                //Case Attack
                battleOver = player.Attack(enemy);
                battleOver = enemy.Attack(player);
                break;
            case '2':
                //Case Items
                battleOver = true;
                break;
            case '3':
                //Case Skills
                battleOver = true;
                break;
            case '4':
                //Case Exit
                battleOver = true;
                Menu();
                break;
            default:
                break;
        }

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
    LoadFOO();
    Menu();
    return 1;
}