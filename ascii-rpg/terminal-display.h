#ifndef TERMINAL_DISPLAY
#define TERMINAL_DISPLAY

#include "creatures.h"
using namespace CreaturesFeatures;

namespace TerminalDisplayFeatures {
    
enum class SceneState {
    kMenu,
    kWorldMap,
    kBattleRewards,
    kSkills,
    kStatus,
    kInventory
};

enum class BattleMenuOptions {
    kMenu,
    kSkills,
    kItems
};

class TerminalDisplay{
    public:
        TerminalDisplay();

        void ClearTerminal();

        void PrintMainMenu();

        void PrintWorldMap();
        
        void PrintBattleResults(const Player player, const Enemy enemy, bool playerWon);

        void PrintBattle(const Player player, const Enemy enemy, const BattleMenuOptions battleMenuOption);

        void PrintInventoryMenu(const Player player);

        void PrintStatusMenu(const Player player);

        std::string LoadSceneFromFile(std::string filepath);
    
    private:
        SceneState m_sceneState;
        
};

}
#endif