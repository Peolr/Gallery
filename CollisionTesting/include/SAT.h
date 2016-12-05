#ifndef SAT_H
#define SAT_H

#include <Polygon.h>
#include <Vector2.h>
#include <vector>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <Entity.h>

double dot(Vector2 a, Vector2 b);
bool overlap (Vector2 a, Vector2 b);
double getOverlap(Vector2 a, Vector2 b, bool* flip);


MTV checkCollision(Entity* a, Entity* b);
MTV isColliding(Polygon a, Polygon b);
Vector2 projectPolygon(Polygon p, Vector2 axis);


#endif // SAT_H
