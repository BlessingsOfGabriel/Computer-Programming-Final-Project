#ifndef OBJ_H
#define OBJ_H
#include "global.h"
class Obj{
	public:
		Obj();
		~Obj();
		int getHeight();
		int getWidth();

		void loadTexture(std::string);
		virtual void resize(int newHeight, int newWidth);
		void free();
		void render(int posX, int posY);
	protected:
		int _height, _width;
		double _xPos, _yPos;
		std::string _type;
		SDL_Texture *_texture;
};
#endif
