#include <iostream>
#include <fstream>

#include "terminal-display.h"

using namespace TerminalDisplayFeatures;


//screen sizes
const int height = 64;
const int width = 128;

void
ClearTerminal() {
    std::cout << "\x1B[2J\x1B[H";
}

std::string
LoadSceneFromFile(std::string filepath)
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

void
LoadWorldMap() {
    ClearTerminal();
    std::cout << LoadSceneFromFile("scenes/worldmap.txt");
}

void
LoadBattleScene() {
    ClearTerminal();
    std::cout << LoadSceneFromFile("creaturesimage/monstersample.txt");
    std::cout << LoadSceneFromFile("creaturesimage/playersample.txt");
    std::cout << LoadSceneFromFile("scenes/battlemenu.txt");
}





void
TerminalDisplay::ChangeScreen(ScreenState screenState) {
    ClearTerminal();
    
    switch (screenState) {
        case ScreenState::Menu:
            std::cout << "Hello player, what do you want?\n";
            std::cout << "1- Visit world map\n";
            std::cout << "2- Open skills menu\n";
            std::cout << "3- Open status menu\n";
            std::cout << "4- Open store\n";
            char choice;
            std::cin >> choice;
            switch (choice) {
                case '1':
                    LoadWorldMap();
                    break;
                case '2':
                    LoadBattleScene();
                    break;
                default:
                    break;
            }
            break;

    }
}

int
main() {
    TerminalDisplay display;

    return 1;
}