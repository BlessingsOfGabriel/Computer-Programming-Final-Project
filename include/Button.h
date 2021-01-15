#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
#include "Obj.h"

std::string typeToString(ButtonType _type);
class Button : public Obj {
    private:
        ButtonType _buttonType;
        bool triggered;
    public:
        Button(ButtonType);
        ~Button();
        void handleEvent(SDL_Event *event);
        void setTriggered(bool);
        bool getTriggered();
};
#endif
