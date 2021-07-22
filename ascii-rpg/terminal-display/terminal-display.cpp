#include <iostream>
#include <fstream>

#include "terminal-display.h"

using namespace TerminalDisplayFeatures;


//Create a game.cpp object -> the game handle the itens, player, and monsters.

//screen sizes
// const int height = 64;
// const int width = 128;


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
TerminalDisplay::LoadWorldMapScene() {
    ClearTerminal();
    std::cout << LoadSceneFromFile("scenes/worldmap.txt");

    //Reading choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            LoadBattleScene();
            break;

        default:
            ClearTerminal();
            break;
    }
}

void
TerminalDisplay::LoadStatusMenuScene() {
    ClearTerminal();
    std::cout << LoadSceneFromFile("scenes/statusmenu.txt");

    //Reading choice
    char choice;
    std::cin >> choice;
    LoadMainMenuScene();
}

void
TerminalDisplay::LoadBattleScene() {
    ClearTerminal();
    std::cout << LoadSceneFromFile("creaturesimage/monstersample.txt");
    std::cout << LoadSceneFromFile("creaturesimage/playersample.txt");
    std::cout << LoadSceneFromFile("scenes/battlemenu.txt");

    //Reading player choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            LoadMainMenuScene();
            break;

        default:
            ClearTerminal();
            break;
    }
}

void
TerminalDisplay::LoadBattleScene(std::string playerVocation, std::string enemyName) {
    //Instantiate player Player player;

    //Instantiate enemy Enemy enemy = enemy(enemyName);

    //Instantiate battle Battle battle = Battle(player, enemy);

    ClearTerminal();
    std::cout << LoadSceneFromFile("creaturesimage/" + enemyName + ".txt");
    std::cout << LoadSceneFromFile("creaturesimage/" + playerVocation + ".txt");
    std::cout << LoadSceneFromFile("scenes/" + playerVocation +"menu.txt");

    //Reading player choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            LoadMainMenuScene();
            break;

        default:
            ClearTerminal();
            break;
    }
}

void
TerminalDisplay::LoadMainMenuScene() {
    ClearTerminal();
    //Printing menu
    std::cout << "Hello player, what do you want?\n";
    std::cout << "1- Visit world map\n";
    std::cout << "2- Open status menu\n";
    // std::cout << "3- Open skills menu\n";
    // std::cout << "4- Open store\n";
    std::cout << "0- To exit the game\n";

    //Reading choice
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            LoadWorldMapScene();
            break;
        case '2':
            LoadStatusMenuScene();
            break;

        default:
            ClearTerminal();
            break;
    }

}

void
TerminalDisplay::ChangeScreen(ScreenState screenState) {
    ClearTerminal();
    switch (screenState) {
        case ScreenState::Menu :
            LoadMainMenuScene();
            break;

        default:
            break;
    }
}

int
main() {
    TerminalDisplay display;
    display.ChangeScreen(ScreenState::Menu);

    return 1;
}