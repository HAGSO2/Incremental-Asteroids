#include "EngineObjects/GameObject.h"

GameObject::GameObject() {};

Sprite::Sprite(Vector2 pos, Vector2 siz, Color c) : position{pos}, size{siz}, color{c} {}
Sprite::Sprite(Vector2 pos, Vector2 siz, Color c, SpriteFrom type) : position{pos}, size{siz}, color{c}, spriteType{type} {}

void Sprite::DrawObject()
{
    switch (spriteType)
    {
    case TRIANGLE:
        /* code */
        DrawPoly((Vector2){ position.x, position.y }, 3, size.x, rotation, color);
        break;
    case SQUARE:
        DrawRectangleV(position, size, color);
        break;
    case CIRCLE:
        DrawCircleV(position, size.x, color);
        break;
    default:
        break;
    };
}

void Sprite::ChangeColor(Color c) { color = c; }

TextShape::TextShape(float x, float y, float width, float height, string txt, Color col) : area{Rectangle{x, y, width, height}}, color{col}, text{txt} {}

void TextShape::DrawObject()
{
    DrawRectangleRec(area, color);
    DrawText(text.c_str(), area.x, area.y, 10, BLACK);
};

void TextShape::ChangeColor(Color c) { color = c; }

void TextShape::ChangeText(string newText) { text = newText; }