#include "menu.h"
#include "MasterDefine.h"
namespace Debug {
Menu::Menu():
    menuIndex(0)
{}

Menu::~Menu(){}

void Menu::init(){
    memset(menuItems, 0, sizeof(menuItems));
    strcpy(menuItems[0], "Battery Check");
    strcpy(menuItems[1], "DEBUG");
    strcpy(menuItems[2], "TEST");
    menuSize = 3;
}

void Menu::controller(){
    showMain();

    while(1){
        char received = receiveChar();
        if(isArrowKey(received)){
            processArrowKey(received);
        }
        showMain();

        if(isEnterKey(received)){
            processEnterKey();
            sendMessage("pushed Enter");
        }

        if(isQuitKey(received)){
            sendMessage("\r\nexit debug mode");
            HAL_Delay(1000);
            clearDisplay();
            return;
        }
        HAL_Delay(10);
    }
}

void Menu::showItems(){
    for(int i=0; i<menuSize; i++){
        if(i == menuIndex){
            sendMessage("--> ");
        }
        else{
            sendMessage("    ");
        }
        sendInt(i+1);
        sendMessage(". ");
        sendMessage(menuItems[i]);
        sendMessage("\r\n");
    }
}

void Menu::showTitle(){
    sendMessage("\r\n===== ");
    sendMessage(NAME);
    sendMessage(" ver.");
    sendMessage(VERSION);
    sendMessage(" =====\r\n");
}

void Menu::showMain(){
    clearDisplay();
    showTitle();
    showItems();
    sendMessage("\r\n w:↑  s:↓  q:exit  Enter:exec  \r\n\r\n");
}

void Menu::processArrowKey(char received){
    switch (received) {
        // ↑
        case 'w':
            if(menuIndex > 0){
                menuIndex--;
            }
            break;

        // ↓
        case 's':
            if(menuIndex < menuSize-1){
                menuIndex++;
            }
            break;
    }
}

void Menu::processEnterKey(){
    switch (menuIndex) {
        case '0':  break;
        case '1':  break;
        case '2':  break;
    }
}

bool Menu::isArrowKey(char received){
    return (received == 'w' || received == 's');
}

bool Menu::isEnterKey(char received){
    return received == '\r';
}

bool Menu::isQuitKey(char received){
    return received == 'q';
}

void Menu::clearDisplay(){
    sendMessage("\033[2J\033[H");
}

};
