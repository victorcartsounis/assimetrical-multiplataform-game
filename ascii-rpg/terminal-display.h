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
    kStatus
};

class TerminalDisplay{
    public:
        TerminalDisplay();

        void ClearTerminal();

        void DisplayScene(SceneState screenState);

        void PrintBattle(const Player player, const Enemy enemy);

        std::string LoadSceneFromFile(std::string filepath);
    
    private:
        SceneState m_sceneState;
        
};

}
#endif