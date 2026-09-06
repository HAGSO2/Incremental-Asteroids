#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <cmath>

#include "EngineObjects/Transform2D.h"

using namespace std;

class Renderer
{
public:
    virtual void DrawObject(Transform2D *object) = 0;
    virtual void UpdateObject(Transform2D *object) = 0;
    virtual void UnloadObject() = 0;
};

enum ShapeForm
{
    SR_TRIANGLE = 0,
    S_TRIANGLE = 1,
    SR_SQUARE = 2,
    S_SQUARE = 3,
    S_CIRCLE = 4,
    S_CUSTOM = 5
};

class Shape2D : public Renderer
{
    Color color;

protected:
    ShapeForm form;
    vector<Vector2> vertices;
    vector<Vector2> Tvertices;

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