#ifndef SCREENUI_H
#define SCREENUI_H

#include <Arduino.h>
#include <Common.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/Org_01.h>

// Global view class, handles basic drawing
class View {
    public:
        View() {}
        View() {uint16_t x, uint16_t y, uint16_t w, uint16_t h};

        void checkDraw();

        virtual void draw();
        virtual void setNeedsDraw();

        uint16_t x, y, w, h;

    protected:
        bool needsDrawing = false;
};

// Simple, clickable button
class Button : public View {

    public:
        Button() {}
        Button() {uint16_t x, uint16_t y, uint16_t w, uint16_t h};

        void setNeedsDraw(bool highlightOnly = false);

        void setEnabled(bool isEnabled);
        bool getEnabled();

        bool isTouched(uint16_t tx, uint16_t ty, bool touchDown);
        virtual bool inButton(uint16_t tx, uint16_t ty);

    protected:
        bool highlighted = false;
        bool enabled = false;
        bool needsHighlightOnly = false;
};

// Normal button, circle shaped
class CircleButton : public Button {

    public:
        CircleButton() {}
        CircleButton(uint16_t cx, uint16_t cy, uint16_t r);

        bool inButton(uint16_t tx, uint16_t ty);

    protected:
        uint16_t cx, cy, r;

};

// Circle button with text
class TextButton : public CircleButton {

    public:
        TextButton() {}
        TextButton(uint16_t cx, uint16_t cy, uint16_t r, char str, uint8_t textSize);

        void draw();

    protected:

        char str;
        uint8_t textSize;
        uint16_t textWidth, textHeight;

};




#endif