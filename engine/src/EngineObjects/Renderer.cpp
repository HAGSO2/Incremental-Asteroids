#include "EngineObjects/Renderer.h"

#pragma region Shape2D
// Constructor for Regular Polygon (e.g., TRIANGLE)
Shape2D::Shape2D(ShapeForm form, Color c, float radius)
    : form(form), color(c), localVertices({{radius, radius}}), worldVertices({{radius, radius}}) {};

// Constructor for TRIANGLE
Shape2D::Shape2D(Vector2 p1, Vector2 p2, Vector2 p3, Color c)
    : form(S_TRIANGLE), color(c),
      localVertices({p1, p2, p3}), worldVertices({p1, p2, p3}) {};

// Constructor for SQUARE
Shape2D::Shape2D(Color c)
    : form(S_SQUARE), color(c), localVertices({}), worldVertices({}) {};

// TODO:Constructor for not regular square

// Constructor for CUSTOM shape
Shape2D::Shape2D(vector<Vector2> v, Color c)
    : form(S_CUSTOM), color(c), localVertices(v), worldVertices(v) {};

void Shape2D::DrawObject(Transform2D *object)
{
  switch (form)
  {
  case SR_TRIANGLE:
    DrawPoly(object->position, 3, localVertices[0].x, object->rotation, color);
    break;
  case S_TRIANGLE:
    DrawTriangle(worldVertices[0], worldVertices[1], worldVertices[2], color);
    break;
  case SR_SQUARE:
    DrawPoly(object->position, 4, localVertices[0].x, object->rotation, color);
    break;
  case S_SQUARE:
    DrawRectangleV(object->position, object->scale, color);
    break;
  case S_CIRCLE:
    DrawCircleV(object->position, localVertices[0].x, color);
    break;
  case S_CUSTOM:
    // Custom shape drawing logic can be implemented here
    DrawLineStrip(worldVertices.data(), worldVertices.size(), color);
  default:
    break;
  }
}

void Shape2D::UpdateObject(Transform2D *object)
{
  float rad = object->rotation * (PI / 180.0f);
  float cosR = cos(rad);
  float sinR = sin(rad);
  // Update logic for the shape can be implemented here if needed
  Vector2 center = object->position;
  for (size_t i = 0; i < localVertices.size(); i += 1)
  {
    float x = localVertices[i].x * object->scale.x;
    float y = localVertices[i].y * object->scale.y;

    float newX = x * cosR - y * sinR;
    float newY = x * sinR + y * cosR;

    worldVertices[i].x = newX + object->position.x;
    worldVertices[i].y = newY + object->position.y;
  }
}
#pragma endregion

#pragma region Shape2DLined
Shape2DLined::Shape2DLined(ShapeForm form, Color c, float radius, Color linec, float linel)
    : Shape2D(form, c, radius), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(Vector2 p1, Vector2 p2, Vector2 p3, Color c,
                           Color linec, float linel)
    : Shape2D(p1, p2, p3, c), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(Color c, Color linec, float linel)
    : Shape2D(c), lineColor(linec), lineSize(linel) {};
Shape2DLined::Shape2DLined(vector<Vector2> v, Color c, Color linec, float linel)
    : Shape2D(v, c), lineColor(linec), lineSize(linel) {};

void Shape2DLined::DrawObject(Transform2D *object)
{
  Shape2D::DrawObject(object);
  switch (form)
  {
  case S_TRIANGLE:
    DrawLineV(worldVertices[0], worldVertices[1], lineColor);
    DrawLineV(worldVertices[1], worldVertices[2], lineColor);
    DrawLineV(worldVertices[2], worldVertices[0], lineColor);
    break;
  case S_SQUARE:
    DrawLineV(worldVertices[0], worldVertices[1], lineColor);
    DrawLineV(worldVertices[1], worldVertices[2], lineColor);
    DrawLineV(worldVertices[2], worldVertices[3], lineColor);
    DrawLineV(worldVertices[3], worldVertices[0], lineColor);
    break;
  default:
    DrawCircleLinesV(object->position, object->scale.x, lineColor);
    // DrawCircleV();

    break;
  };
}
#pragma endregion

#pragma region TextShape
TextShape::TextShape(ShapeForm form, Color c, float radius, string &txt, int fSize,
                     Color tColor)
    : Shape2D(form, c, radius), text(txt), fontSize(fSize), color(tColor) {};
TextShape::TextShape(Vector2 p1, Vector2 p2, Vector2 p3, Color c, string &txt,
                     int fSize, Color tColor)
    : Shape2D(p1, p2, p3, c), text(txt), fontSize(fSize), color(tColor) {};
TextShape::TextShape(Color c, string &txt, int fSize, Color tColor)
    : Shape2D(c), text(txt), fontSize(fSize), color(tColor) {};
TextShape::TextShape(vector<Vector2> v, Color c, string &txt, int fSize,
                     Color tColor)
    : Shape2D(v, c), text(txt), fontSize(fSize), color(tColor) {};

void TextShape::DrawObject(Transform2D *object)
{
  Shape2D::DrawObject(object);
  DrawText(text.c_str(), object->position.x, object->position.y, fontSize,
           color);
}
#pragma endregion