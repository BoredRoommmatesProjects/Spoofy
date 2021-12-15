#include "Spoofy.hpp"
#include "handlers/WindowHandler.hpp"
#include "handlers/LogicHandler.hpp"
#include "handlers/InputHandler.hpp"
#include "common/IApp.hpp"

#include <SFML/Window.hpp>

#include <cstring>

IGame* IGame::m_game = new Spoofy();

Spoofy::Spoofy()
: AbstractGame(), m_app(nullptr), m_windowHandler(nullptr), m_logicHandler(nullptr), m_inputHandler(nullptr)
{
    std::cout << "- Spoofy::Spoofy() -" << std::endl;
	m_app = nullptr;
	m_windowHandler = nullptr;
	m_logicHandler = nullptr;
	m_inputHandler = nullptr;
}

void Spoofy::Initialize()
{
    AbstractGame::Initialize();
    std::cout << "- Spoofy::Initialize() -" << std::endl;

    m_app = new IApp();

    m_windowHandler = new WindowHandler(SCREEN_WIDTH, SCREEN_HEIGHT, m_app);
	m_logicHandler = new LogicHandler(m_app);
	
	InitSDLObject();
	m_windowHandler->InitializeTexture();
	
	m_inputHandler = new InputHandler(m_app);
}

void Spoofy::InitSDLObject()
{
	m_app->setWindowRenderer(new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Spoofy"));

	if (!m_app->getWindowRenderer())
	{
		printf("Failed to open %d x %d window\n", SCREEN_WIDTH, SCREEN_HEIGHT);
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
}

IApp* Spoofy::GetApp()
{
    return m_app;
}

WindowHandler* Spoofy::GetWindowHandler()
{
    return m_windowHandler;
}

LogicHandler* Spoofy::GetLogicHandler()
{
	return m_logicHandler;
}

InputHandler* Spoofy::GetInputHandler()
{
	return m_inputHandler;
}

Spoofy::~Spoofy()
{
    if (m_app != nullptr)
    {
        delete m_app;
        m_app = nullptr;
    }

    if (m_windowHandler != nullptr)
    {
        delete m_windowHandler;
        m_windowHandler = nullptr;
    }

	if (m_logicHandler != nullptr)
	{
		delete m_logicHandler;
		m_logicHandler = nullptr;
	}

	if (m_inputHandler != nullptr)
	{
		delete m_inputHandler;
		m_inputHandler = nullptr;
	}
}