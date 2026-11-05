#pragma once
#include <raylib.h>
#include <vector>
#include <string>

/*Tengo que sacar gameScreen del botón y hacerlo genérico*/

using namespace std;

class UIElement
{
protected:
    Rectangle area;

public:
    UIElement(float x, float y, float width, float height);
    virtual ~UIElement() = default;
    bool IsInside(Vector2);
    virtual void SetOut() = 0;
    virtual void Draw() = 0;
    virtual void UpdateScreen(Vector2) = 0;
    virtual void UpdateKeyboard(KeyboardKey) = 0;
};

class UI
{ // Canvas
    vector<UIElement *> elements;

public:
    UI();
    ~UI()
    {
        for (int i = 0; i < elements.size(); i++)
            delete elements[i];
    };
    //Add types of UI objects
    void AddButton(float x, float y, float width, float height, int fontsize, const char *s, Color c, void (*Func)(void *), void *miptr);
    void AddImageButton(float x, float y, float width, float height, const char *imagePath, void (*Func)(void *), void *miptrs);
    void AddTextBox(float x, float y, float width, float height, string &reftxt);
    void AddPlainText(float x, float y, float width, float height, int size, string texto, int *numref = nullptr);

    //TODO: Read and write to a json

    //Control functions
    void Draw();
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey);
};

class CallBack
{
    void *ptr;
    void (*ClickFunk)(void *);

public:
    CallBack(void (*Func)(void *), void *miptrs);
    ~CallBack() = default;
    void Execute() { ClickFunk(ptr); }
};

class Button : public UIElement
{
    const char *texto;
    Color color;
    CallBack callback;
    int fontsize = 12;

public:
    Button(float x, float y, float width, float height, int fontsize, const char *s, Color c, void (*Func)(void *), void *miptrs);
    ~Button() = default;
    void Draw();
    void SetOut() {};
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey){};
};

class ImageButton : public UIElement
{
    const char *imagePath;
    Texture2D texture;
    CallBack callback;
    public:
    ImageButton(float x, float y, float width, float height, const char *imagePath, void (*Func)(void *), void *miptrs);
    ~ImageButton() = default;
    void Draw();
    void SetOut() {};
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey){};
};

class PlainText : public UIElement
{
    //char buffer[256];
    //const char *texto;
    string buffer;
    string texto;
    int *numero;
    int size;

public:
    PlainText(float x, float y, float width, float height, int size, string texto, int *numref);
    ~PlainText() = default;
    void Draw() override;
    void SetOut() override {};
    void UpdateScreen(Vector2) override{};
    void UpdateKeyboard(KeyboardKey) override{};
};

#define NO_SELECCIONADO ORANGE
#define SELECCIONADO GREEN
class TextBox : public UIElement
{
    string &texto;
    bool seleccionado;

public:
    TextBox(float x, float y, float width, float height, string &reftxt);
    ~TextBox() = default;
    void Draw() override;
    void SetOut() override { seleccionado = false; };
    void UpdateScreen(Vector2) override;
    void UpdateKeyboard(KeyboardKey) override;
};
