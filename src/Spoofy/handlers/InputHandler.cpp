#include "handlers/InputHandler.hpp"
#include "common/SpoofyDefs.hpp"


InputHandler::InputHandler(App* a_app) : m_app(a_app)
{

}

InputHandler::~InputHandler() {}

void InputHandler::DoInput()
{
	sf::Event event;

	while (m_app->windowRenderer->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			exit(0); // TODO: Create exception class to throw handled exceptions
			break;

		case sf::Event::KeyPressed:
			DoKeyDown(&event.key);
			break;

		case sf::Event::KeyReleased:
			DoKeyUp(&event.key);
			break;

		default:
			break;
		}
	}
}

void InputHandler::DoKeyDown(sf::Event::KeyEvent* event)
{
	if (event->code < sf::Keyboard::Key::KeyCount)
	{
		m_app->keyboard[event->code] = 1;
	}
}

void InputHandler::DoKeyUp(sf::Event::KeyEvent* event)
{
	if (event->code < sf::Keyboard::Key::KeyCount)
	{
		m_app->keyboard[event->code] = 0;
	}
}