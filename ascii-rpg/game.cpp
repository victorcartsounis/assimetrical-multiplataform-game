#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "terminal-display.h"
#include "creatures.h"
#include "items.h"

using json = nlohmann::json;

using namespace TerminalDisplayFeatures;
using namespace CreaturesFeatures;
using namespace ItemsFeatures;

TerminalDisplay terminalDisplay = TerminalDisplay();

namespace {

class Game {
    public:
        Game() 
            : m_player(LoadPlayer())
            , m_enemies(LoadEnemies())
        {
        };

        void Menu();

        void PrintBattleMenu();

        void SkillsMenuInBattle(const Enemy enemy);

        void ItemsMenuInBattle(const Enemy enemy);

        void BattleResults(Player& player, const Enemy enemy, bool playerWon);
        
        void Battle(Enemy enemy);

        void WorldMap();

        void StatusMenu();

        void InventoryMenu();        

        Enemy LoadEnemy(std::string name);

        std::vector<Enemy> LoadEnemies();

        Player LoadPlayer();

        void SavePlayer();

    private:
        Player m_player;
        std::vector<Enemy> m_enemies;
};
    
}

Player
Game::LoadPlayer() {
    std::ifstream file("data/player.json");
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '"
            << "player.txt" << "'\n";
        EXIT_FAILURE;
    }

    json j;
    file >> j;

    file.close();

    Player player = Player(j);

    //   JUST TO TEST INVENTORY SYSTEM
    Weapon weapon = Weapon("TrollSlayer", "A magic sword to kill internet trolls",
        "data/items/magicsword.txt", 100, std::make_pair(PropertyName::kAttack, 100));
    player.AddItemToInventory(weapon);
    player.OnEquip(weapon);

    Helmet helmet = Helmet("Hunter's cap", "A helmet that never let you down",
        "data/items/magicsword.txt", 100, std::make_pair(PropertyName::kDefense, 100));
    player.AddItemToInventory(helmet);
    player.AddItemToInventory(helmet);
    player.OnEquip(helmet);

    return player;
}

std::vector<Enemy>
Game::LoadEnemies() {
    std::ifstream file("data/monsters/monsters.json");
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '"
             << "data/monsters/monsters.json" << "'\n";
        EXIT_FAILURE;
    }

    json js;
    file >> js;
    
    file.close();

    std::vector<Enemy> enemies;

    for (auto& j : js["monsters"]) {
        std::cout << "It works";
        enemies.emplace_back(Enemy(j));
    }
    std::cout << "It works 2";

    return enemies;
}

Enemy
Game::LoadEnemy(std::string monsterName) {
    std::ifstream file("data/monsters/monsters.json");
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '"
             << "data/monsters/monsters.json" << "'\n";
        EXIT_FAILURE;
    }

    json js;
    file >> js;
    
    file.close();

    for (auto& j : js["monsters"]) {
        if (j["name"].get<std::string>() == monsterName){
            return Enemy(j);
        }
    }

    return Enemy(js["monsters"]);
}

void
Game::SavePlayer() {
    std::ofstream file;
    file.open ("data/player.json");

    json j;
    j["id"] = m_player.GetId();
    j["name"] = m_player.GetName();
    j["level"] = m_player.GetLevel();
    j["experience"] = m_player.GetExperience();
    j["health"] = m_player.GetMaxHealth();
    j["skillPoints"] = m_player.GetMaxSkillPoints();
    j["attack"] = m_player.GetAttack();
    j["defense"] = m_player.GetDefense();

    file << j;

    file.close();
}

void
Game::SkillsMenuInBattle(const Enemy enemy) {
    terminalDisplay.PrintBattle(m_player, enemy, BattleMenuOptions::kSkills);

    //Reading player choice
    char choice;
    std::cin >> choice;
}

void
Game::ItemsMenuInBattle(const Enemy enemy) {
    terminalDisplay.PrintBattle(m_player, enemy, BattleMenuOptions::kItems);

    //Reading player choice
    char choice;
    std::cin >> choice;
}

void
Game::BattleResults(Player& player, const Enemy enemy, bool playerWon) {
    if (playerWon) {
        player.AddExperience(enemy.GetExperience());
        while (player.GetExperience() >= player.GetNextLevelExperience()) {
            player.AddLevel();
            std::cout << "!!LEVEL UP to level: " << player.GetLevel();
        }
    }
    SavePlayer();
    char choice;
    std::cin >> choice;
    Menu();
}

void
Game::Battle(Enemy enemy) {

    bool playerWon = false;
    bool enemyWon = false;
    bool battleOver = false;

    while (!playerWon && !enemyWon && !battleOver) {
        //printing battle scene
        terminalDisplay.PrintBattle(m_player, enemy, BattleMenuOptions::kMenu);
        
        //Reading player choice
        char choice;
        std::cin >> choice;

        switch (choice) {
            case '1':
                //Case Attack
                if (m_player.Attack(enemy)) {
                    playerWon = true;
                    break;
                }
                if (enemy.Attack(m_player)) {
                    enemyWon = true;
                    break;
                }
                break;
            case '2':
                //Case Items
                ItemsMenuInBattle(enemy);
                break;
            case '3':
                //Case Skills
                SkillsMenuInBattle(enemy);
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
        terminalDisplay.PrintBattleResults(m_player, enemy, playerWon);
        BattleResults(m_player, enemy, playerWon);
    }
}

void
Game::WorldMap() {
    //printing world map
    terminalDisplay.PrintWorldMap();

    //Reading choice
    char choice;
    std::cin >> choice;
    std::cout << (choice - '0') << std::endl;
    if ((choice - '0') <= m_enemies.size()) {
        Battle(m_enemies[(choice - '0') - 1]);
    } else {
        Battle(m_enemies[0]);
    }
}

void
Game::StatusMenu() {
    //printing status
    terminalDisplay.PrintStatusMenu(m_player);

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
Game::InventoryMenu() {

    //printing inventory
    terminalDisplay.PrintInventoryMenu(m_player);

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
Game::Menu() {
    //printing menu
    terminalDisplay.PrintMainMenu();

    //Reading player choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            WorldMap();
            break;
        case '2':
            StatusMenu();
        case '3':
            InventoryMenu();
        default:
            break;
    }
    
    terminalDisplay.ClearTerminal();
}

int
main() {
    Game game = Game();
    game.Menu();

    return 1;
}