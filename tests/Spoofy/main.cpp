
#include <chrono>
#include <thread>

#include "Spoofy.hpp"
#include "handlers/WindowHandler.hpp"
#include "handlers/LogicHandler.hpp"
#include "handlers/InputHandler.hpp"

static void capFrameRate(sf::Time* then, sf::Time* remainder, sf::Clock* clock)
{
	sf::Time wait, frameTime;

	wait = sf::milliseconds(16 + remainder->asMilliseconds());
	*remainder -= sf::milliseconds(remainder->asMilliseconds());
	frameTime = sf::milliseconds(clock->getElapsedTime().asMilliseconds()) - sf::milliseconds(then->asMilliseconds());
	wait -= sf::milliseconds(frameTime.asMilliseconds());

	if (wait < sf::milliseconds(1))
	{
		wait = sf::milliseconds(1);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(wait.asMilliseconds()));

	*remainder += sf::milliseconds(0.667);
	*then = sf::milliseconds(clock->getElapsedTime().asMilliseconds());
}

static void cleanup()
{
	std::cout << "static void cleanup()" << std::endl;
}

int main()
{
	sf::Time then;
	sf::Time remainder;

    sf::Clock clock; // starts the clock

    IGame::Instance()->Initialize();

	atexit(cleanup);

	then = clock.getElapsedTime();

	remainder = sf::Time::Zero;

	while (1)
	{
		IGame::Instance()->GetWindowHandler()->PrepareWindow();

		IGame::Instance()->GetInputHandler()->DoInput();

		IGame::Instance()->GetLogicHandler()->Logic();

		IGame::Instance()->GetWindowHandler()->Draw();

		IGame::Instance()->GetWindowHandler()->PresentWindow();

		capFrameRate(&then, &remainder, &clock);
	}

	return 0;
}