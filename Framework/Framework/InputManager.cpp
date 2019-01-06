#include "InputManager.h"

using namespace sf;

bool InputManager::isSpriteClicked(Sprite object, Mouse::Button button, RenderWindow & window)
{
	if (Mouse::isButtonPressed(button))
	{
		IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (playButtonRect.contains(Mouse::getPosition(window)))
		{
			return true;
		}
	}

	return false; //means that this sprite isn't clicked
}

Vector2i InputManager::getMousePosition(RenderWindow & window)
{
	return Mouse::getPosition(window);
}
