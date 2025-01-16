#ifndef QUANTVERSO_SHAPE_H
#define QUANTVERSO_SHAPE_H

//--------------------------------------------------------------------------------------------------

#include "Transformable.h"
#include "Color.h"

class Rectangle;
class Point;
class Window;

//--------------------------------------------------------------------------------------------------

class Shape : public Transformable
{
public:
	Shape();
	virtual ~Shape() = default;

	void Color(::Color color);

	virtual bool CheckCollision(const Shape* other) const = 0;
	virtual bool CheckCollision(const Rectangle* other) const = 0;
	virtual bool CheckCollision(const Point* other) const = 0;

	bool CheckCollision(const Rectangle* rect, const Point* point) const;

protected:
	::Color color;

private:
	friend class Window;

	virtual void Draw(Window* window) const = 0;
};

//--------------------------------------------------------------------------------------------------

inline void Shape::Color(::Color color)
{
	this->color = color;
}

//--------------------------------------------------------------------------------------------------

#endif
