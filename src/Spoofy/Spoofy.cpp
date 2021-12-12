#include "Spoofy.hpp"
#include "handlers/WindowHandler.hpp"
#include "handlers/LogicHandler.hpp"
#include "handlers/InputHandler.hpp"

#include <SFML/Window.hpp>

#include <cstring>

IGame* IGame::m_game = new Spoofy();

Spoofy::Spoofy() : AbstractGame()
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

    m_app = new App();
	memset(m_app, 0, sizeof(App));

    m_windowHandler = new WindowHandler(SCREEN_WIDTH, SCREEN_HEIGHT, m_app);
	m_logicHandler = new LogicHandler(m_app);

	InitSDLObject();
	m_windowHandler->InitializeTexture();

	m_inputHandler = new InputHandler(m_app);
}

void Spoofy::InitSDLObject()
{
	//int rendererFlags, windowFlags;

	//rendererFlags = SDL_RENDERER_ACCELERATED;

	//windowFlags = 0;

	/*if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}*/
	//m_app->window = SDL_CreateWindow("Spoofy_game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	m_app->windowRenderer = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Spoofy");

	if (!m_app->windowRenderer)
	{
		printf("Failed to open %d x %d window\n", SCREEN_WIDTH, SCREEN_HEIGHT);
		exit(1); // TODO: Create exception class to throw handled exceptions
	}

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	//m_app->renderer = SDL_CreateRenderer(m_app->window, -1, rendererFlags);
	m_app->textureRenderer = new sf::RenderTexture();

	if (!m_app->textureRenderer)
	{
		printf("Failed to create renderer\n");
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
	m_app->textureRenderer->create(SCREEN_WIDTH, SCREEN_HEIGHT);
}

App* Spoofy::GetApp()
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