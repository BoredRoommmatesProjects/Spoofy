
#ifndef _SPOOFY_COMMON_IGAME_HPP_
#define _SPOOFY_COMMON_IGAME_HPP_

#include <iostream>

#include "common/GameDefs.hpp"

class WindowHandler;
class LogicHandler;
class InputHandler;

class IGame
{
public:
	static IGame* Instance()
	{
		return m_game;
	}

	virtual void Initialize() = 0;
	virtual WindowHandler* GetWindowHandler() = 0;
	virtual LogicHandler* GetLogicHandler() = 0;
	virtual InputHandler* GetInputHandler() = 0;

	virtual ~IGame() {};

protected:
	IGame() { std::cout << "- IGame::IGame() -" << std::endl; };

private:
	IGame(const IGame& a_toCopy);
	IGame& operator = (const IGame& a_toAssign);

	static IGame* m_game;
};

class AbstractGame : public IGame
{
public:
	virtual void Initialize() override;
	virtual WindowHandler* GetWindowHandler() override;
	virtual LogicHandler* GetLogicHandler() override;
	virtual InputHandler* GetInputHandler() override;

	virtual ~AbstractGame() {};

protected:
	AbstractGame();

private:
	AbstractGame(const AbstractGame& a_toCopy);
	AbstractGame& operator = (const AbstractGame& a_toAssign);
};

#endif // !_SPOOFY_COMMON_IGAME_HPP_