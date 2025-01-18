#include "menu.h"
#include "MasterDefine.h"
namespace Debug {
Menu::Menu():
    menuIndex(0)
{
    init();
}

Menu::~Menu(){}

void Menu::init(){
    strcpy(menuItem[0], "LED");
    strcpy(menuItem[1], "DEBUG");
    strcpy(menuItem[2], "TEST");
    strcpy(menuItem[3], "Param");
    menuSize = 4;
}

void Menu::showMain(){
    showTitle();
    showItems();

    while(1){
        char received = receiveChar();
        if(isEscKey(received)){
            processArrowKey();
        }

        if(isEnterKey(received)){

        }
    }
}

void Menu::showItems(){
    for(int i=0; i<menuSize; i++){
        if(i == menuIndex){
            sendMessage("-->");
        }
        else{
            sendMessage("   ");
        }
        sendMessage(menuItem[i]);
    }
}

void Menu::showTitle(){
    sendMessage("\r\n===== ");
    sendMessage(NAME);
    sendMessage(" ver.");
    sendMessage(VERSION);
    sendMessage(" =====\r\n");
}

void Menu::processArrowKey(){
    char received = receiveChar();
    if (isEscKey(received)) {
        char seq1 = receiveChar();
        char seq2 = receiveChar();
        if (seq1 == '[') {
            switch (seq2) {
                // ↑
                case 'A':
                    if(menuIndex > 0){
                        menuIndex--;
                    }
                    break;

                // ↓
                case 'B':
                    if(menuIndex < 5){
                        menuIndex++;
                    }
                    break;
            }
        }
    }
}

bool Menu::isEscKey(char received){
    return received == '\x1B';
}

bool Menu::isEnterKey(char received){
    return received == '\r';
}

};
