#include <iostream>

#include "terminal-display.h"

using namespace TerminalDisplayFeatures;

TerminalDisplay terminalDisplay = TerminalDisplay();

void
Menu();

void
LoadFOO() {

}

void
Battle() {
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
                battleOver = true;
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