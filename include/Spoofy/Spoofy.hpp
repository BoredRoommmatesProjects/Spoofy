#ifndef _SPOOFY_SPOOFY_HPP_
#define _SPOOFY_SPOOFY_HPP_

#include "common/IGame.hpp"
#include "common/SpoofyDefs.hpp"


class WindowHandler;
class LogicHandler;
class InputHandler;

class Spoofy : public AbstractGame
{
public:
	Spoofy();

	void Initialize() override;
	void InitSDLObject();

	App* GetApp();
	WindowHandler* GetWindowHandler() override;
	LogicHandler* GetLogicHandler() override;
	InputHandler* GetInputHandler() override;

private:
	App* m_app;
	WindowHandler* m_windowHandler;
	LogicHandler* m_logicHandler;
	InputHandler* m_inputHandler;

	Spoofy(const Spoofy& a_toCopy);
	Spoofy& operator = (const Spoofy& a_toAssign);

	virtual ~Spoofy();
};

#endif // !_SPOOFY_SPOOFY_HPP_