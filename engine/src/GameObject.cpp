#include <algorithm>
#include "EngineObjects/GameObject.h"

GameObject::GameObject() {};

SpriteFrom::SpriteFrom(TypeForm form, Vector2 center, float size, Color c) : color(c) // Constructor for Regular Polygon (e.g., TRIANGLE)
{
    this->form = form;
    vertices = {center.x, center.y, size};
    color = c;
}
SpriteFrom::SpriteFrom(Vector2 p1, Vector2 p2, Vector2 p3, Color c) : color(c) // Constructor for TRIANGLE
{
    form = TRIANGLE;
    vertices = {p1.x, p1.y, p2.x, p2.y, p3.x, p3.y};
    color = c;
}
SpriteFrom::SpriteFrom(Vector2 position, Vector2 size, Color c) : color(c) // Constructor for SQUARE
{
    form = SQUARE;
    vertices = {position.x, position.y, size.x, size.y};
    color = c;
}

void SpriteFrom::DrawObject()
{
    switch (form)
    {
    case R_TRIANGLE:
        DrawPoly((Vector2){vertices[0], vertices[1]}, 3, vertices[2], rotation, color);
        break;
    case TRIANGLE:
        DrawTriangle((Vector2){vertices[0], vertices[1]}, (Vector2){vertices[2], vertices[3]}, (Vector2){vertices[4], vertices[5]}, color);
        break;
    case R_SQUARE:
        DrawPoly((Vector2){vertices[0], vertices[1]}, 4, vertices[2], rotation, color);
        break;
    case SQUARE:
        DrawRectangleV((Vector2){vertices[0], vertices[1]}, (Vector2){vertices[2], vertices[3]}, color);
        break;
    case CIRCLE:
        DrawCircleV((Vector2){vertices[0], vertices[1]}, vertices[2], color);
        break;
    default:
        break;
    };
}

Vector2 SpriteFrom::GetPosition()
{
    switch (form)
    {
    case R_TRIANGLE:
    case R_SQUARE:
        return {vertices[0], vertices[1]};
    case TRIANGLE:
        return {(vertices[0] + vertices[2] + vertices[4]) / 3, (vertices[1] + vertices[3] + vertices[5]) / 3};
    case SQUARE:
        return {vertices[0], vertices[1]};
    case CIRCLE:
        return {vertices[0], vertices[1]};
    default:
        return {0, 0}; // Default position if form is unknown
    }
}

// Vector2 SpriteFrom::GetSize()
// {
//     switch (form)
//     {
//     case R_TRIANGLE:
//     case R_SQUARE:
//         return {vertices[2], vertices[2]}; // Assuming size is uniform for regular shapes
//     case TRIANGLE:
//         // Calculate bounding box size for triangle
//         float minX = std::min({vertices[0], vertices[2], vertices[4]});
//         float maxX = std::max({vertices[0], vertices[2], vertices[4]});
//         float minY = std::min({vertices[1], vertices[3], vertices[5]});
//         float maxY = std::max({vertices[1], vertices[3], vertices[5]});
//         return {maxX - minX, maxY - minY};
//     case SQUARE:
//         return {vertices[2], vertices[3]};
//     case CIRCLE:
//         return {vertices[2] * 2, vertices[2] * 2}; // Diameter as size
//     default:
//         return {0, 0}; // Default size if form is unknown
//     }
// }

void SpriteFrom::ChangeColor(Color c) { color = c; }

TextShape::TextShape(float x, float y, float width, float height, string txt, Color col) : area{Rectangle{x, y, width, height}}, color{col}, text{txt} {}

void TextShape::DrawObject()
{
    DrawRectangleRec(area, color);
    DrawText(text.c_str(), area.x, area.y, 10, BLACK);
};

void TextShape::ChangeColor(Color c) { color = c; }

void TextShape::ChangeText(string newText) { text = newText; }