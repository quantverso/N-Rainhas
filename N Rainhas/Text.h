#ifndef QUANTVERSO_TEXT_H
#define QUANTVERSO_TEXT_H

//--------------------------------------------------------------------------------------------------

#include "SDL_ttf.h"
#include "Color.h"
#include <string>

class Window;


//--------------------------------------------------------------------------------------------------

class Text
{
public:
	Text();
	~Text();
	void Load(const char* file, Uint32 size);
	void String(const std::string& string);
	void Position(int x, int y);
	void Size(int w, int h);
	void Color(::Color color);

	SDL_Rect Bounds();

private:
	friend class Window;

	std::string		  text;		 ///< Texto a ser renderizado
	Uint32			  size;		 ///< Tamanho da fonte
	::Color			  color;	 ///< Cor do texto
	TTF_Font*		  font;		 ///< Fonte carregada do arquivo .ttf
	SDL_Texture*	  texture;	 ///< Textura renderizada
	SDL_Surface*	  surface;	 ///< Superf�cie de renderiza��o
	SDL_Rect		  rect;		 ///< Rect de renderiza��o
	inline static int instances; ///< Contador de inst�ncias
};

//--------------------------------------------------------------------------------------------------

inline SDL_Rect Text::Bounds()
{
	return rect;
}

//--------------------------------------------------------------------------------------------------

#endif