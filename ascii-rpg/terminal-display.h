#ifndef TERMINAL_DISPLAY
#define TERMINAL_DISPLAY


namespace TerminalDisplayFeatures {

enum class SceneState {
    kMenu,
    kWorldMap,
    kBattle,
    kBattleRewards,
    kSkills,
    kStatus
};

class TerminalDisplay{
    public:
        TerminalDisplay();

        void ClearTerminal();

        void DisplayScene(SceneState screenState);

        std::string LoadSceneFromFile(std::string filepath);
    
    private:
        SceneState m_sceneState;
        
};

}
#endif