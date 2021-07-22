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
            ChangeScreen(ScreenState::Menu);
        }

        void ChangeScreen(ScreenState screenState);
    
    private:
        ScreenState m_screenState;
        
};

}


#endif