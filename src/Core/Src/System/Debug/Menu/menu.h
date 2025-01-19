#ifndef SYSTEM_DEBUG_MENU_H_
#define SYSTEM_DEBUG_MENU_H_

#include <memory>
#include <UsartInterface/usart_interface.h>

namespace Debug {
class Menu : public UsartInterface{
public:
    Menu();
    ~Menu();
    void init();
    void controller();

private:
    void showTitle();
    void showItems();
    void showMain();
    void processArrowKey(char received);
    void processEnterKey();

    bool isArrowKey(char received);
    bool isEnterKey(char received);
    bool isQuitKey(char received);
    void clearDisplay();

private:
    uint8_t currentMenuLevel;
    uint8_t currentSelection;
    int8_t menuIndex;
    int8_t menuSize;
    char menuItems[20][20];
};
};
#endif
