#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class GameObject
{
public:
    GameObject();
    virtual void DrawObject() = 0;
};

enum TypeForm
{
    R_TRIANGLE = 0,
    TRIANGLE = 1,
    R_SQUARE = 2,
    SQUARE = 3,
    CIRCLE = 4
};

class SpriteFrom : public GameObject
{
    Color color;
    float rotation = 0.0f;

protected:
    TypeForm form;
    vector<float> vertices;

public:
    SpriteFrom(TypeForm form, Vector2 center, float size, Color c);          // Constructor for Regular Polygon (e.g., TRIANGLE)
    SpriteFrom(Vector2 p1, Vector2 p2, Vector2 p3, Color c, float rotation); // Constructor for TRIANGLE
    SpriteFrom(Vector2 position, Vector2 size, Color c);                     // Constructor for SQUARE
    Vector2 GetApex()
    {
        if (form == TRIANGLE)
            return {vertices[4], vertices[5]};
        else
            return {0, 0};
    };
    void ChangeColor(Color c) { color = c; }
    void Rotate(float angle);
    virtual void DrawObject();
    Vector2 GetPosition();
    Vector2 GetSize();
    float GetRotation() { return rotation; };
};

class SpriteFormLined : public SpriteFrom
{
    Color lineColor;
    float lineSize;

public:
    SpriteFormLined(TypeForm form, Vector2 center, float size, Color c, Color linec, float linel);          // Constructor for Regular Polygon (e.g., TRIANGLE)
    SpriteFormLined(Vector2 p1, Vector2 p2, Vector2 p3, Color c, float rotation, Color linec, float linel); // Constructor for TRIANGLE
    SpriteFormLined(Vector2 position, Vector2 size, Color c, Color linec, float linel);                     // Constructor for SQUARE
    void DrawObject() override;
};

class TextShape : public GameObject
{
    Rectangle area;
    string text;
    int note;
    Color color;

public:
    TextShape(float x, float y, float width, float height, string txt, Color col);
    void ChangeColor(Color c);
    void ChangeText(string newText);
    void DrawObject();
};