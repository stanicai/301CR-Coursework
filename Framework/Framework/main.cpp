#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

void main()
{

	/*
	The RenderWindow is our game window - we've set it to 800x600 resolution, and named it Test Window. The
	sf::Event e is an arbitrary event populated whenever something happens which SFML considers an 'event' -
	e.g. a mouse click, a key press, and so on. More on that later.
	*/

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
	sf::Event e;


	/*
	We begin by creating a sun - a circle shape 100.0f in radius (this really means it's 200 pixels across).
	We set its colour to be Yellow - note that SFML has predefined Color properties we can use for this -
	try changing the colour of the sun yourself while you're experimenting.
	*/

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);

	/*
	Now we're going to create a square - with SFML, we do this with a RectangleShape. We setSize to be
	198px by 198px, and give it a thin magenta outline. While our Sun's position is just defaulted, we
	explicitly pick a position for our rectangle's top left corner to be rendered (600 across, 2 down).
	This is our anchor position for our square, and whatever we do to the position of our square acts on
	that anchor point.
	*/

	sf::RectangleShape texturedShape;
	texturedShape.setSize(sf::Vector2f(198.0f, 198.0f));
	texturedShape.setOutlineColor(sf::Color::Magenta);
	texturedShape.setOutlineThickness(2.0f);
	texturedShape.setPosition(600.0f, 2.0f);

	/*
	We want to texture our rectangle, so we create a texture called testTexture. After that, we populate
	testTexture from a read-in file - note the relative pathing used in the directory of the file. We can
	replace those relative paths with #DEFINEs if we want to. Remembering last week's lecture, we should
	realise that this texture is an ASSET, and that we should in some fashion manage it. In this case,
	SFML is handling the memory management of the asset for us, so our own asset management would involve
	keeping track of testTexture for reuse, making sure keyboardcat.jpg wasn't read in twice, etc.

	Also note our little error check here. We mentioned error checking and debugging last week - here's
	a practical example. If loadFromFile fails, we get a COUT telling us this has happened.
	*/

	sf::Texture testTexture;
	if (!testTexture.loadFromFile("../Textures/keyboardcat.jpg"))
	{
		cout << "Texture did not load!" << "\n";
	}

	/*
	Now we set the Texture of texturedShape to be a reference to testTexture. Be careful when reading
	API documentation - often functions have multiple overloaded versions of themselves which might
	ask for alternative parameters.
	*/

	texturedShape.setTexture(&testTexture);

	while (window.isOpen()) {

		/*
		This while loop is basically our simple game loop - more on that in future weeks. What it's
		doing is polling the Event e (as we mentioned earlier) and checking its type. First, if the
		event type is Event::Closed, this indicates the window's X button has been clicked, and
		we tell the window to close. Windows will often close on an X click anyway, but doing it
		this way ensures we're tidy about it.
		*/

		window.pollEvent(e);

		if (e.type == sf::Event::Closed) {
			window.close();

		}

		/*
		If the event isn't an Event::Closed, we check to see if it's an Event::KeyPressed. If so,
		we run through a check to see if an arrow key is being pressed. Dependent on the key(s) being
		pressed, our textured square moves in different directions. This approach has several issues
		as discussed in the lecture, so you'll want to abstract and refine this. Can you think of any
		problems which might occur when two keys are pressed simultaneously?

		Next, if the Escape key is pressed, we consider that to be a close instruction from the user
		and the window exits.
		*/

		if (e.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				texturedShape.move(sf::Vector2f(-0.5f, 0.0f));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				texturedShape.move(sf::Vector2f(0.5f, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				texturedShape.move(sf::Vector2f(0.0f, -0.5f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				texturedShape.move(sf::Vector2f(0.0f, 0.5f));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		/*
		Lastly, we draw everything. We set our window's clear colour to be blue. We then draw the
		textured square, followed by the yellow sun, before displaying the content of the window. How
		does the draw ordering affect the appearance of the environment?
		*/

		window.clear(sf::Color::Blue);
		window.draw(texturedShape);
		window.draw(shape);
		window.display();

	}
}