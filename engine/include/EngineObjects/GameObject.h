#pragma once
#include <raylib.h>
#include <string>

using namespace std;

class GameObject{
    Transform transform;
public:
    GameObject();
    Transform GetTransform() {return transform;};
    virtual void DrawObject() = 0;
};

enum SpriteFrom{
    TRIANGLE = 0,
    SQUARE = 1,
    CIRCLE = 2
};

class Sprite : public GameObject{
    Vector2 position;
    Vector2 size;
    Color color;
    SpriteFrom spriteType = SQUARE;
    float rotation = 0.0f;
public:
    Sprite(Vector2 position, Vector2 size, Color c);
    Sprite(Vector2 position, Vector2 size, Color c, SpriteFrom type);
    void ChangeColor(Color c);
    void Rotate(float angle) { rotation += angle; };
    void DrawObject();
};

class TextShape : public GameObject{
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