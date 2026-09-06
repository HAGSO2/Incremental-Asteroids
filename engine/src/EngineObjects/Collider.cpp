#include "EngineObjects/Collider.h"

bool Collider2D::isColliding(Vector2 p)
{
    switch (form)
    {
    case RECTANGLE:
        return CheckCollisionPointRec(p, Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y});
    case CIRCLE:
        return CheckCollisionPointCircle(p, *points[0], points[1]->x);
    case CUSTOM:
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
    case RECTANGLE:
        if (other->form == RECTANGLE)
            return CheckCollisionRecs(Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y},
                                      Rectangle{otherPoints[0]->x, otherPoints[0]->y, otherPoints[1]->x, otherPoints[1]->y});
        else if (other->form == CIRCLE)
            return CheckCollisionCircleRec(*otherPoints[0], otherPoints[1]->x,
                                           Rectangle{points[0]->x, points[0]->y, points[1]->x, points[1]->y});
    case CIRCLE:
        if (other->form == RECTANGLE)
            return CheckCollisionCircleRec(*points[0], points[1]->x,
                                           Rectangle{otherPoints[0]->x, otherPoints[0]->y, otherPoints[1]->x, otherPoints[1]->y});
        else if (other->form == CIRCLE)
            return CheckCollisionCircles(*points[0], points[1]->x, *otherPoints[0], otherPoints[1]->x);    
    default:
        break;
    }
}