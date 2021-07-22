#ifndef TERMINAL_DISPLAY
#define TERMINAL_DISPLAY


namespace TerminalDisplayFeatures {

enum class ScreenState {
    Menu,
    Map,
    Battle,
    EndBattle,
    Skills,
    Storage,
    Status
};

class TerminalDisplay{
    public:
        TerminalDisplay() 
        : m_screenState(ScreenState::Menu) {
        }

        void ChangeScreen(ScreenState screenState);

        void LoadMainMenuScene();

        void LoadBattleScene();

        void LoadBattleScene(std::string playerVocation, std::string enemyName);
        
        void LoadWorldMapScene();
    
    private:
        ScreenState m_screenState;
        
};

}


#endif