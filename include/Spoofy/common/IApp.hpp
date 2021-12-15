#ifndef _SPOOFY_COMMON_IAPP_HPP_
#define _SPOOFY_COMMON_IAPP_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "common/GameDefs.hpp"


class IApp
{
public:
	IApp()
    : m_windowRenderer(nullptr)
    {}
    
    int* getKeyboardMatrix() { return m_keyboardMatrix; };
    sf::RenderWindow* getWindowRenderer() { return m_windowRenderer; };

    void setWindowRenderer(sf::RenderWindow* a_windowRenderer)
    {
        m_windowRenderer = a_windowRenderer;
    }

	virtual ~IApp() {};

private:

    int m_keyboardMatrix[sf::Keyboard::Key::KeyCount];
	sf::RenderWindow* m_windowRenderer;
};

#endif // !_SPOOFY_COMMON_IAPP_HPP_