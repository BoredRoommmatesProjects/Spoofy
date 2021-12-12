#ifndef _SPOOFY_HANDLERS_INPUTHANDLER_HPP_
#define _SPOOFY_HANDLERS_INPUTHANDLER_HPP_

#include <SFML/Window/Event.hpp>

struct App;

class InputHandler
{
public:
	InputHandler(App* a_app);
	~InputHandler();

	void DoInput();
	

private:
	App* m_app;

	void DoKeyUp(sf::Event::KeyEvent* event);
	void DoKeyDown(sf::Event::KeyEvent* event);
};

#endif // !_SPOOFY_HANDLERS_INPUTHANDLER_HPP_