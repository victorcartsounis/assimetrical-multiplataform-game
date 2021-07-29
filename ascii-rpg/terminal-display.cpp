#include <iostream>
#include <fstream>

#include "terminal-display.h"
#include "creatures.h"

using namespace TerminalDisplayFeatures;
using namespace CreaturesFeatures;

// file paths
const std::string creaturePath = "terminal-display/creaturesimage/";
const std::string scenesPath = "terminal-display/scenes/";

void
TerminalDisplay::ClearTerminal() {
    std::cout << "\x1B[2J\x1B[H";
}

void
TerminalDisplay::DisplayScene(SceneState sceneState) {
    ClearTerminal();
    
    switch (sceneState) {
        case SceneState::kMenu:
            //Printing menu
            std::cout << "Hello player, what do you want?\n";
            std::cout << "1- Visit world map\n";
            std::cout << "2- Open status menu\n";
            // std::cout << "3- Open skills menu\n";
            // std::cout << "4- Open store\n";
            std::cout << "0- To exit the game\n";
            break;
        case SceneState::kWorldMap:
            std::cout << LoadSceneFromFile("terminal-display/scenes/worldmap.txt");
            break;
        case SceneState::kStatus:
            std::cout << LoadSceneFromFile("terminal-display/scenes/statusmenu.txt");
            break;
        default:
            break;
    }
}

void
TerminalDisplay::PrintBattle(Player player, Enemy enemy) {
    //Printing enemy image
    std::cout << LoadSceneFromFile("terminal-display/creaturesimage/monstersample.txt");
    // std::cout << LoadSceneFromFile("terminal-display/creaturesimage/" + enemy.GetName() + "txt");
    
    //Printing player image
    std::cout << LoadSceneFromFile("terminal-display/creaturesimage/playersample.txt");
    // std::cout << LoadSceneFromFile("terminal-display/creaturesimage/" + player.GetName() + "txt");

    //Priting TEMPORARY VERSION of battle menu
    std::string battleMenu = "";
    //printing top border
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
    
    //printing player health
    
    std::string healthBar = "";
    healthBar = std::to_string(player.GetHealth()) + "/" + std::to_string(player.GetMaxHealth());
    int healthBarSize = 13 - healthBar.size();
    for (int i = 0; i < healthBarSize; i++) {
        healthBar += " ";
    }
    std::cout << "   HEALTH POINTS : " + healthBar;

    //printing player skill points

    std::cout << "  |  SKILL POINTS 9999/9999    |  ";

    //printing enemy health

    std::string enemyHealthBar = "";
    enemyHealthBar = std::to_string(enemy.GetHealth()) + "/" + std::to_string(enemy.GetMaxHealth());
    int enemyHealthBarSize = 13 - enemyHealthBar.size();
    for (int i = 0; i < enemyHealthBarSize; i++) {
        enemyHealthBar += " ";
    }
    std::cout << "Enemy health: " << enemyHealthBar << std::endl;

    //printing blank line
    std::cout << "                                                               |\n";

    //printing options

    std::cout << "      (1) Attack                               (2) Items       |\n";
    std::cout << "                                                               |\n";
    std::cout << "      (3) Skills                               (4) Exit        |\n";
    std::cout << "                                                               |\n";
    std::cout << "-----------------------------------------------------------------";
    std::cout << "---------------------------------------------------------------\n";

}

std::string
TerminalDisplay::LoadSceneFromFile(std::string filepath)
{
    std::string fileLine;
    std::string loadedString;

    std::ifstream MyReadFile(filepath);
    
    while (getline (MyReadFile, fileLine)) {
    // Output the text from the file
    loadedString += fileLine + "\n";
    }

    MyReadFile.close();
    
    return loadedString;
}


TerminalDisplay::TerminalDisplay() {

}
