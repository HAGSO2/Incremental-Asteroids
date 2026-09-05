#pragma once
#include <raylib.h>
#include "EngineObjects/GameObject.h"

class Renderer
{
public:
    virtual void DrawObject(Transform2D *object) = 0;
    virtual void UpdateObject(Transform2D *object) = 0;
    virtual void UnloadObject() = 0;
};

enum ShapeForm
{
    R_TRIANGLE = 0,
    TRIANGLE = 1,
    R_SQUARE = 2,
    SQUARE = 3,
    CIRCLE = 4,
    CUSTOM = 5
};

class Shape2D : public Renderer
{
    Color color;

protected:
    ShapeForm form;
    vector<Vector2> vertices;
    // vector<Vector2> Tvertices;

public:
    Shape2D(ShapeForm form, Color c);                     // Constructor for Regular Polygon (e.g., TRIANGLE)
    Shape2D(Vector2 p1, Vector2 p2, Vector2 p3, Color c); // Constructor for TRIANGLE
    Shape2D(Color c);                                     // Constructor for SQUARE
    Shape2D(vector<Vector2> v, Color c);                  // Constructor for CUSTOM shape
    void DrawObject(Transform2D *object) override;
    void UpdateObject(Transform2D *object) override;
    void UnloadObject() override
    {
        // Implement unloading logic if needed
        vertices.clear();
        // Tvertices.clear();
    }
};

class Shape2DLined : public Shape2D
{
    Color lineColor;
    float lineSize;

public:
    Shape2DLined(ShapeForm form, Color c, Color linec, float linel);                     // Constructor for Regular Polygon (e.g., TRIANGLE)
    Shape2DLined(Vector2 p1, Vector2 p2, Vector2 p3, Color c, Color linec, float linel); // Constructor for TRIANGLE
    Shape2DLined(Color c, Color linec, float linel);                                     // Constructor for SQUARE
    Shape2DLined(vector<Vector2> v, Color c, Color linec, float linel);                  // Constructor for CUSTOM shape

    void DrawObject(Transform2D *object) override;
};

class TextShape : public Shape2D
{
    string &text;
    int fontSize;
    Color color;
    public:
    TextShape(ShapeForm form, Color c, string &txt, int fSize, Color tColor);                     // Constructor for Regular Polygon (e.g., TRIANGLE)
    TextShape(Vector2 p1, Vector2 p2, Vector2 p3, Color c, string &txt, int fSize, Color tColor); // Constructor for TRIANGLE
    TextShape(Color c, string &txt, int fSize, Color tColor);                                     // Constructor for SQUARE
    TextShape(vector<Vector2> v, Color c, string &txt, int fSize, Color tColor);                  // Constructor for CUSTOM shape

    void DrawObject(Transform2D *object) override;
};

// class TextShape : public GameObject
// {
//     Rectangle area;
//     string text;
//     int note;
//     Color color;

// public:
//     TextShape(float x, float y, float width, float height, string txt, Color col);
//     void ChangeColor(Color c);
//     void ChangeText(string newText);
//     void DrawObject();
// };