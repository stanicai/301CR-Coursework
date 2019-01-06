#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class InputManager
{
public:
	bool isSpriteClicked(Sprite object, Mouse::Button button, RenderWindow &window); //checking if a sprite is being clicked

	Vector2i getMousePosition(RenderWindow &window); //getting the mouse position
};

