#include "common/IGame.hpp"

AbstractGame::AbstractGame() : IGame()
{
	std::cout << "- AbstractGame::AbstractGame() -" << std::endl;
}

void AbstractGame::Initialize()
{
	std::cout << "- AbstractGame::Initialize() -" << std::endl;
}

WindowHandler* AbstractGame::GetWindowHandler()
{
	return nullptr;
}

LogicHandler* AbstractGame::GetLogicHandler()
{
	return nullptr;
}

InputHandler* AbstractGame::GetInputHandler()
{
	return nullptr;
}