#ifndef QUANTVERSO_COLOR_H
#define QUANTVERSO_COLOR_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>

//--------------------------------------------------------------------------------------------------

class Color : public SDL_Color
{
public:
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Magenta;
	static const Color Cyan;
	
	Color();
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	Color(const Color& other);

	Color& operator=(const Color& other);	
};

//--------------------------------------------------------------------------------------------------

#endif