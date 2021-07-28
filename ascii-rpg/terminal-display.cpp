#include <iostream>
#include <fstream>

#include "terminal-display.h"

using namespace TerminalDisplayFeatures;

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
        case SceneState::kBattle:
            std::cout << LoadSceneFromFile("terminal-display/creaturesimage/monstersample.txt");
            std::cout << LoadSceneFromFile("terminal-display/creaturesimage/playersample.txt");
            std::cout << LoadSceneFromFile("terminal-display/scenes/battlemenu.txt");
            break;
        default:
            break;
    }
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
