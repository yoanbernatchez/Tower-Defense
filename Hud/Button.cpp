/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-03
 * Project: Tower Defense
 * File: Button.cpp
 *
 * Brief: This class implements a Button that can be interacted with. The
 *        button can contain texts.
 */

#include "Button.h"

Button::Button(int borderSize, SDL_Color borderColor,
               SDL_Color backgroundColor, int width, int height)
{
    src = {0, 0, 0, 0};
    dst = {0, 0, width, height};
    savedDst = {0, 0, 0, 0};

    isHovered = false;
    isHighlightable = true;
    isPressed = false;
    pressDepth = 8;
    isVisible = true;
    isPressable = true;
    opacity = 255;

    this->borderSize = borderSize;
    this->borderColor.r = borderColor.r;
    this->borderColor.g = borderColor.g;
    this->borderColor.b = borderColor.b;
    this->borderColor.a = borderColor.a;

    this->backgroundColor.r = backgroundColor.r;
    this->backgroundColor.g = backgroundColor.g;
    this->backgroundColor.b = backgroundColor.b;
    this->backgroundColor.a = backgroundColor.a;

    highlightColor.r = backgroundColor.r + 60;
    highlightColor.g = backgroundColor.g + 60;
    highlightColor.b = backgroundColor.b + 60;
    highlightColor.a = backgroundColor.a;
}

/*
 * Adds a text component to the button.
 */
void Button::AddText(SDL_Renderer *renderer, std::string text, int fontSize,
                     SDL_Color color, FONT fontName)
{
    label = text;
    std::shared_ptr<Text> tempText(new Text(renderer, text, fontSize, color,
                                            fontName));
    texts.push_back(std::move(tempText));
}

/*
 * Safely changes the press depth of the button.
 */
void Button::SetPressDepth(int depth)
{
    if(isPressed)
    {
        Release();
        pressDepth = depth;
        Press();
    }
    else
    {
        pressDepth = depth;
    }
}

/*
 * Sets a button to pressed.
 */
void Button::Press()
{
    if(!isPressed && isVisible && isPressable)
    {
        dst.y += pressDepth;
        isPressed = true;
    }
}

/*
 * Sets a button to not pressed.
 */
void Button::Release()
{
    if(isPressed)
    {
        dst.y -= pressDepth;
        isPressed = false;
    }
}

/*
 * Centers a button's text in the middle of the button.
 */
void Button::CenterTextById(int id)
{
    if(id < (signed) texts.size())
    {
        texts[id]->dst.x = dst.w/2 - texts[id]->dst.w/2;
        texts[id]->dst.y = dst.h/2 - texts[id]->dst.h/2;
    }
}

/*
 * Returns whether the mouse coordinates are in a button.
 */
bool Button::IsMouseOnButton(int mouseX, int mouseY, int x, int y)
{
    if(isPressable
       && mouseX > x && mouseX < dst.w + x && mouseY > y && mouseY < y + dst.h)
    {
        return true;
    }

    return false;
}

std::string Button::GetLabel() { return label; }
