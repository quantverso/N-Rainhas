#include "Shape.h"
#include "Rectangle.h"
#include "Point.h"

//--------------------------------------------------------------------------------------------------

Shape::Shape() :
    color(Color::White)
{
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Rectangle* rect, const Point* point) const
{
    if (point->position.x < rect->bounds.Left() || rect->bounds.Right() < point->position.x)
        return false;
    if (point->position.y < rect->bounds.Top() || rect->bounds.Bottom() < point->position.y)
        return false;
    return true;
}

//--------------------------------------------------------------------------------------------------
