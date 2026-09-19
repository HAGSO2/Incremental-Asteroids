#include "EngineObjects/GameObject.h"

void GameObject2D::AddCollider2D(ColliderType type,
                                 vector<Vector2 *>
                                     otherPoints)
{
  if (type != C_CUSTOM)
  {
    vector<Vector2 *> points = vector<Vector2 *>(2);
    points[0] = &transform->position;
    points[1] = &transform->scale;
    collider = new Collider2D(type, points);
    return;
  }
  collider = new Collider2D(type, otherPoints);
};

GameObject2D::~GameObject2D()
{
  TraceLog(LOG_DEBUG, "Deleting collider");
  if (collider != nullptr)
    delete collider;
  TraceLog(LOG_DEBUG, "Deleting renderer");
  if (renderer != nullptr)
    delete renderer;
  TraceLog(LOG_DEBUG, "Deleting transform");
  delete transform;
};

bool GameObject2D::IsColliding(GameObject2D *other)
{
  return collider->isColliding(other->collider);
};