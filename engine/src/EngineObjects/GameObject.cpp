#include "EngineObjects/GameObject.h"

void GameObject2D::AddCollider2D(ColliderType type,
                                 vector<Vector2 *> *otherPoints) {
  if (type != C_CUSTOM) {
    vector<Vector2 *> points = vector<Vector2 *>(2);
    points[0] = &transform->position;
    points[1] = &transform->scale;
    collider = new Collider2D(type, points);
    return;
  }
}
