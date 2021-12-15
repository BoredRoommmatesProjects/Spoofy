#include <deque>
#include <string>

#include "handlers/LogicHandler.hpp"
#include "handlers/WindowHandler.hpp"
#include "Spoofy.hpp"

#include <SFML/Window/Keyboard.hpp>

LogicHandler::LogicHandler(App* a_app) : m_app(a_app)
{
	m_enemySpawnTimer = 0;
}

LogicHandler::~LogicHandler()
{}

void LogicHandler::Logic()
{
	DoPlayer();

	DoEnemies();

	DoBullets();

	DoEnemyBullet();

	SpawnEnemies();

	ClipPlayer();

	int resetGameTimer = IGame::Instance()->GetWindowHandler()->GetGameResetTimer();
	IGame::Instance()->GetWindowHandler()->SetGameResetTimer(--resetGameTimer);
	if (IGame::Instance()->GetWindowHandler()->GetPlayerEntity() == nullptr && IGame::Instance()->GetWindowHandler()->GetGameResetTimer() <= 0)
	{
		IGame::Instance()->GetWindowHandler()->ResetGame();
	}
}

void LogicHandler::DoPlayer()
{
	Entity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	if (player != nullptr)
	{
		player->dx = player->dy = 0;

		if (player->reload > 0)
		{
			player->reload--;
		}

		if (m_app->keyboard[sf::Keyboard::Key::Up])
		{
			player->dy = -PLAYER_SPEED;
		}

		if (m_app->keyboard[sf::Keyboard::Key::Down])
		{
			player->dy = PLAYER_SPEED;
		}

		if (m_app->keyboard[sf::Keyboard::Key::Left])
		{
			player->dx = -PLAYER_SPEED;
		}

		if (m_app->keyboard[sf::Keyboard::Key::Right])
		{
			player->dx = PLAYER_SPEED;
		}

		if (m_app->keyboard[sf::Keyboard::Key::LControl] && player->reload == 0)
		{
			IGame::Instance()->GetWindowHandler()->FireBullet();
		}

		player->x += player->dx;
		player->y += player->dy;
	}
}

void LogicHandler::DoEnemies()
{
	std::deque<Entity*>* enemyDeque = IGame::Instance()->GetWindowHandler()->GetEnemyDeque();
	Entity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	size_t i = 1;
	while (i <= enemyDeque->size() && !enemyDeque->empty())
	{
		Entity* tempEntity = enemyDeque->at(enemyDeque->size() - i);
		tempEntity->x += tempEntity->dx;
		tempEntity->y += tempEntity->dy;

		if (tempEntity->x < -tempEntity->w || tempEntity == player) // TODO: player versus enemy colision
		{
			tempEntity->health = 0;
		}

		if (tempEntity->health == 0)
		{
			if (tempEntity == player) // TODO: player versus enemy colision
			{
				player = nullptr;
			}
			tempEntity = nullptr;
			std::deque<Entity*>::iterator it = enemyDeque->end() - i;
			enemyDeque->erase(it);
		}
		i++;
	}
}

void LogicHandler::DoEnemyBullet()
{
	std::deque<Entity*>* enemyDeque = IGame::Instance()->GetWindowHandler()->GetEnemyDeque();
	Entity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	size_t i = 1;
	while (i <= enemyDeque->size() && !enemyDeque->empty())
	{
		Entity* tempEntity = enemyDeque->at(enemyDeque->size() - i);

		if (tempEntity != player && player != nullptr && --tempEntity->reload <= 0)
		{
			IGame::Instance()->GetWindowHandler()->FireEnemyBullet(tempEntity);
		}
		i++;
	}

	std::deque<Entity*>* enemyBulletDeque = IGame::Instance()->GetWindowHandler()->GetEnemyBulletDeque();
	size_t j = 1;
	while (j <= enemyBulletDeque->size() && !enemyBulletDeque->empty())
	{
		Entity* tempEnemyBulletEntity = enemyBulletDeque->at(enemyBulletDeque->size() - j);
		tempEnemyBulletEntity->x += tempEnemyBulletEntity->dx;
		tempEnemyBulletEntity->y += tempEnemyBulletEntity->dy;

		if (tempEnemyBulletEntity->x < -tempEnemyBulletEntity->w || tempEnemyBulletEntity->y < -tempEnemyBulletEntity->h ||
			tempEnemyBulletEntity->x > SCREEN_WIDTH || tempEnemyBulletEntity->y > SCREEN_HEIGHT)
		{
			std::cout << "In DoEnemyBullet() function pop_back condition" << std::endl;
			tempEnemyBulletEntity = nullptr;
			enemyBulletDeque->pop_back();
		}
		j++;
	}
	
}

void LogicHandler::DoBullets()
{
	std::deque<Entity*>* bulletDeque = IGame::Instance()->GetWindowHandler()->GetBulletDeque();

	size_t i = 1;
	while (i <= bulletDeque->size() && !bulletDeque->empty())
	{
		Entity* tempEntity = bulletDeque->at(bulletDeque->size() - i);
		tempEntity->x += tempEntity->dx;
		tempEntity->y += tempEntity->dy;

		if (/*IGame::Instance()->GetWindowHandler()->BulletHitFighter(tempEntity) ||*/
			tempEntity->x < -tempEntity->w || tempEntity->y < -tempEntity->h || 
			tempEntity->x > SCREEN_WIDTH || tempEntity->y > SCREEN_HEIGHT)
		{
			std::cout << "In DoBullets() function pop_back condition" << std::endl;
			tempEntity = nullptr;
			bulletDeque->pop_back();
		}
		i++;
	}
}

void LogicHandler::SpawnEnemies()
{
	if (--m_enemySpawnTimer <= 0)
	{
		IGame::Instance()->GetWindowHandler()->CreateEnemy();
		m_enemySpawnTimer = FPS / 2 + (rand() % FPS);
	}
}

void LogicHandler::ClipPlayer()
{
	Entity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	if (player != nullptr)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}

		if (player->y < 0)
		{
			player->y = 0;
		}

		if (player->x > SCREEN_WIDTH / 2.0)
		{
			player->x = SCREEN_WIDTH / 2.0;
		}

		if (player->y > (float)(SCREEN_HEIGHT - player->h))
		{
			player->y = (float)(SCREEN_HEIGHT - player->h);
		}
	}
}

int LogicHandler::GetEnemySpawntimer()
{
	return m_enemySpawnTimer;
}

void LogicHandler::SetEnemySpawntimer(int a_time)
{
	m_enemySpawnTimer = a_time;
}