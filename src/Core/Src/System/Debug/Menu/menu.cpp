#include "menu.h"

namespace Debug {
Menu::Menu():
    menuIndex(0)
{}

Menu::~Menu(){}

void Menu::showMain(){
    showTitle();

    while(1){
        char received = receiveChar();
        if(isEscKey(received)){
            processArrowKey();
        }

        if(isEnterKey(received)){

        }
    }
}

void Menu::showTitle(){
    sendMessage("\r\n===== STM32 =====\r\n");
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
