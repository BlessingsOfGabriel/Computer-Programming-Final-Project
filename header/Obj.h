#ifndef OBJ_H
#define OBJ_H
class Obj{
	public:
		Obj();
		~Obj();
		int getHeight();
		int getWidth();
		void loadTexture(std::string);
		virtual void resize(int newHeight, int newWidth);
		void free();
	protected:
		int _height, _width;
		double _xPos, _yPos;
		std::string _type;
		SDL_Texture *_texture;
};
#endif
