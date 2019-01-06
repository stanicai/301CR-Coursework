#pragma once

#include <map> // to store all the textures that will be used
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class AssetManager
{
public:
	AssetManager() {};
	~AssetManager() {};

	//method for loading the textures
	void LoadTexture(string textureName, string fileName);
	Texture &getTexture(string textureName);

	//method for loading the fonts
	void LoadFont(string fontName, string fileName);
	Font &getFont(string fontName);

private:
	//the first is the name and the second is the texture itself
	map<string, Texture> _textures;
	map<string, Font> _fonts;
};

