#ifndef SYSTEM_DEBUG_MENU_H_
#define SYSTEM_DEBUG_MENU_H_

#include <memory>
#include <UsartInterface/usart_interface.h>

namespace Debug {
class Menu : public UsartInterface{
public:
    Menu();
    ~Menu();
    void showMain();

private:
    void init();
    void showTitle();
    void showItems();
    void processArrowKey();
    void processEnterKey();
    void processEscapeKey();

    bool isEscKey(char received);
    bool isEnterKey(char received);

private:
    uint8_t currentMenuLevel;
    uint8_t currentSelection;
    int8_t menuIndex;
    int8_t menuSize;
    char *menuItem[10];
};
};
#endif
