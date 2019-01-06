#include "AssetManager.h"

using namespace std;
using namespace sf;

void AssetManager::LoadTexture(string textureName, string fileName)
{
	Texture texture;
	
	if (texture.loadFromFile(fileName))
	{
		this->_textures[textureName] = texture;
	}
}

Texture &AssetManager::getTexture(string textureName)
{
	return this->_textures.at(textureName); // returns a particular texture at the index specified 
}

void AssetManager::LoadFont(string fontName, string fileName)
{
	Font font;

	if (font.loadFromFile(fileName))
	{
		this->_fonts[fontName] = font;
	}
}

Font &AssetManager::getFont(string fontName)
{
	return this->_fonts.at(fontName); // returns a particular font at the index specified 
}