#include <ScreenUI.h>


// View Class
View::View(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : x(x), y(y), w(w), h(h) {}

void View::checkDraw(){

    if (needsDrawing){
        draw();
        needsDrawing = false;
    }
}

void View::setNeedsDraw(){
    needsDrawing = true;
}


// Button Class
Button::Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : View(x, y, w, h) {}

void Button::setNeedsDraw(bool highlightOnly){
    needsDrawing = true;
    needsHighlightOnly = highlightOnly;
}

bool Button::isTouched(uint16_t tx, uint16_t ty, bool touchDown){
    bool in = inButton(tx, ty);
        if ((in && touchDown) != highlighted) {
        highlighted = in && touchDown;
        setNeedsDraw(true);
    }
    return in && !touchDown;
}

bool Button::inButton(uint16_t tx, uint16_t ty) {
    return (tx > x) && (tx < x + w) && (ty > y) && (ty < y + h);
}

void Button::setEnabled(bool isEnabled){
    if (enabled != isEnabled) {
        enabled = isEnabled;
        setNeedsDraw(true);
    }
}

bool Button::getEnabled(){
    return enabled;
}

// Circle Button Class
CircleButton::CircleButton(uint16_t cx, uint16_t cy, uint16_t r) : Button(cx - r, cy - r, r * 2, r * 2), cx(cx), cy(cy), r(r) {}

bool CircleButton::inButton(uint16_t tx, uint16_t ty){
    return distanceBetween(cx, tx, cy, ty) < r;
}

// Text Button Class
TextButton::TextButton(uint16_t cx, uint16_t cy, uint16_t r, char str, uint8_t textSize) : CircleButton(cx, cy, r), str(str), textSize(textSize) {
    int16_t tempX, tempY;
    TFT.setTextSize(textSize);
    TFT.getTextBounds(str, 0, 0, &tempX, &tempY, &textWidth, &textHeight);
}

void TextButton::draw(){
    TFT.drawCircle(cx, cy, r, highlighted ? HIGHLIGHT_COLOUR : FOREGROUND_COLOUR);
    TFT.setCursor(cx - textWidth / 2, cy - textHeight / 2);
    TFT.setTextSize(textSize);
    TFT.setTextColor(FOREGROUND_COLOUR);
    TFT.print(str);
}