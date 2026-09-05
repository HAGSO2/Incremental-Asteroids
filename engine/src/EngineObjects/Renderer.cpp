#include "EngineObjects/Renderer.h"

#pragma region Shape2D
// Constructor for Regular Polygon (e.g., TRIANGLE)
Shape2D::Shape2D(ShapeForm form, Color c) : form(form), color(c), vertices({}) {}; //, Tvertices({}) {};

// Constructor for TRIANGLE
Shape2D::Shape2D(Vector2 p1, Vector2 p2, Vector2 p3, Color c) : form(TRIANGLE), color(c), vertices({p1, p2, p3}) {}; //, Tvertices({p1, p2, p3}) {};

// Constructor for SQUARE
Shape2D::Shape2D(Color c) : form(SQUARE), color(c), vertices({}) {}; //, Tvertices({}) {};

// Constructor for CUSTOM shape
Shape2D::Shape2D(vector<Vector2> v, Color c) : form(CUSTOM), color(c), vertices(v) {}; //, Tvertices(v) {};

void Shape2D::DrawObject(Transform2D *object)
{
    switch (form)
    {
    case R_TRIANGLE:
        DrawPoly(object->position, 3, object->scale.x, object->rotation, color);
        break;
    case TRIANGLE:

        DrawTriangle(vertices[0], vertices[1], vertices[2], color);
        break;
    case R_SQUARE:
        DrawPoly(object->position, 4, object->scale.x, object->rotation, color);
        break;
    case SQUARE:
        DrawRectangleV(object->position, object->scale, color);
        break;
    case CIRCLE:
        DrawCircleV(object->position, object->scale.x, color);
        break;
    case CUSTOM:
        // Custom shape drawing logic can be implemented here
        DrawLineStrip(vertices.data(), vertices.size(), color);
    default:
        break;
    }
}

void Shape2D::UpdateObject(Transform2D *object)
{
    // Update logic for the shape can be implemented here if needed
    Vector2 center = object->position;
    for (size_t i = 0; i < vertices.size(); i += 1)
    {
        float x = vertices[i].x - center.x;
        float y = vertices[i].y - center.y;
        float newX = x * cos(object->rotation * (PI / 180.0f)) - y * sin(object->rotation * (PI / 180.0f));
        float newY = x * sin(object->rotation * (PI / 180.0f)) + y * cos(object->rotation * (PI / 180.0f));
        vertices[i] = {newX * object->scale.x + center.x, newY * object->scale.y + center.y};
        // Tvertices[i] = {newX * object->scale.x + center.x, newY * object->scale.y + center.y};
    }
}
#pragma endregion

#pragma region Shape2DLined
Shape2DLined::Shape2DLined(ShapeForm form, Color c, Color linec, float linel) : Shape2D(form, c), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(Vector2 p1, Vector2 p2, Vector2 p3, Color c, Color linec, float linel) : Shape2D(p1, p2, p3, c), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(Color c, Color linec, float linel) : Shape2D(c), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(vector<Vector2> v, Color c, Color linec, float linel) : Shape2D(v, c), lineColor(linec), lineSize(linel) {};

void Shape2DLined::DrawObject(Transform2D *object)
{
    Shape2D::DrawObject(object);
    switch (form)
    {
    case TRIANGLE:
        DrawLineV(vertices[0], vertices[1], lineColor);
        DrawLineV(vertices[1], vertices[2], lineColor);
        DrawLineV(vertices[2], vertices[0], lineColor);
        break;
    case SQUARE:
        DrawLineV(vertices[0], vertices[1], lineColor);
        DrawLineV(vertices[1], vertices[2], lineColor);
        DrawLineV(vertices[2], vertices[3], lineColor);
        DrawLineV(vertices[3], vertices[0], lineColor);
        break;
    default:
        DrawCircleV(object->position, object->scale.x, lineColor);
        break;
    };
}
#pragma endregion

#pragma region TextShape
    TextShape::TextShape(ShapeForm form, Color c, string & txt, int fSize, Color tColor) : Shape2D(form, c), text(txt), fontSize(fSize), color(tColor) {};
    TextShape::TextShape(Vector2 p1, Vector2 p2, Vector2 p3, Color c, string & txt, int fSize, Color tColor) : Shape2D(p1, p2, p3, c), text(txt), fontSize(fSize), color(tColor) {};
    TextShape::TextShape(Color c, string & txt, int fSize, Color tColor) : Shape2D(c), text(txt), fontSize(fSize), color(tColor) {};
    TextShape::TextShape(vector<Vector2> v, Color c, string & txt, int fSize, Color tColor) : Shape2D(v, c), text(txt), fontSize(fSize), color(tColor) {};

    void TextShape::DrawObject(Transform2D * object)
    {
        Shape2D::DrawObject(object);
        DrawText(text.c_str(), object->position.x, object->position.y, fontSize, color);
    }
#pragma endregion
    // TextShape::TextShape(float x, float y, float width, float height, string txt, Color col) : area{Rectangle{x, y, width, height}}, color{col}, text{txt} {}

    // void TextShape::DrawObject()
    // {
    //     DrawRectangleRec(area, color);
    //     DrawText(text.c_str(), area.x, area.y, 10, BLACK);
    // };

    // void TextShape::ChangeColor(Color c) { color = c; }

    // void TextShape::ChangeText(string newText) { text = newText; }