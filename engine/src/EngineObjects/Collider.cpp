#include "EngineObjects/Collider.h"

Collider2D::~Collider2D()
{
    if (form == C_CUSTOM)
    {
        for (int i = 0; i < points.size(); i++)
        {
            delete points[i];
        }
    }
}

bool Collider2D::isColliding(Vector2 p)
{
    switch (form)
    {
    case C_RECTANGLE:
        return CheckCollisionPointRec(p, Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y});
    case C_CIRCLE:
        return CheckCollisionPointCircle(p, *points[0], points[1]->x);
    case C_CUSTOM:
        return CheckCollisionPointPoly(p, *points.data(), points.size());
    default:
        break;
    }
}

bool Collider2D::isColliding(Collider2D *other)
{
    vector<Vector2 *> otherPoints = other->points;
    switch (form)
    {
    case C_RECTANGLE:
        if (other->form == C_RECTANGLE)
            return CheckCollisionRecs(Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y},
                                      Rectangle{otherPoints[0]->x, otherPoints[0]->y, otherPoints[1]->x, otherPoints[1]->y});
        else if (other->form == C_CIRCLE)
            return CheckCollisionCircleRec(*otherPoints[0], otherPoints[1]->x,
                                           Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y});
    case C_CIRCLE:
        if (other->form == C_RECTANGLE)
            return CheckCollisionCircleRec(*points[0], points[1]->x,
                                           Rectangle{otherPoints[0]->x, otherPoints[0]->y, otherPoints[1]->x, otherPoints[1]->y});
        else if (other->form == C_CIRCLE)
            return CheckCollisionCircles(*points[0], points[1]->x, *otherPoints[0], otherPoints[1]->x);
    default:
        break;
    }
    return false;
}