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
    char choice;
    std::cin >> choice;
    Menu();
}

void
Battle() {
    std::map<std::string, int> playerStats = ReadStatsFromFile("player");
    std::map<std::string, int> enemyStats = ReadStatsFromFile("monstername");

    Player player = Player("playername", playerStats);
    Enemy enemy = Enemy("rat", enemyStats);

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
    LoadFOO();
    Menu();
    return 1;
}