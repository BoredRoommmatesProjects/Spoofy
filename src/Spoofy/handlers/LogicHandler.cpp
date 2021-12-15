#include <deque>
#include <string>

#include "handlers/LogicHandler.hpp"
#include "handlers/WindowHandler.hpp"
#include "Spoofy.hpp"
#include "common/SpoofyDefs.hpp"
#include "common/SpoofyEntity.hpp"
#include "common/IApp.hpp"

#include <SFML/Window/Keyboard.hpp>

LogicHandler::LogicHandler(IApp* a_app)
: m_app(a_app), m_enemySpawnTimer(0)
{}

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
	SpoofyEntity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	if (player != nullptr)
	{
		player->setEntityDxVelocity(0);
		player->setEntityDyVelocity(0);

		if (player->getEntityReload() > 0)
		{
			player->setEntityReload(player->getEntityReload()-1);
		}

		if (m_app->getKeyboardMatrix()[sf::Keyboard::Key::Up])
		{
			player->setEntityDyVelocity(-PLAYER_SPEED);
		}

		if (m_app->getKeyboardMatrix()[sf::Keyboard::Key::Down])
		{
			player->setEntityDyVelocity(PLAYER_SPEED);
		}

		if (m_app->getKeyboardMatrix()[sf::Keyboard::Key::Left])
		{
			player->setEntityDxVelocity(-PLAYER_SPEED);
		}

		if (m_app->getKeyboardMatrix()[sf::Keyboard::Key::Right])
		{
			player->setEntityDxVelocity(PLAYER_SPEED);
		}

		if (m_app->getKeyboardMatrix()[sf::Keyboard::Key::LControl] && player->getEntityReload() == 0)
		{
			IGame::Instance()->GetWindowHandler()->FireBullet();
		}

		player->setEntityXPose(player->getEntityXPose() + player->getEntityDxVelocity());
		player->setEntityYPose(player->getEntityYPose() + player->getEntityDyVelocity());
	}
}

void LogicHandler::DoEnemies()
{
	std::deque<SpoofyEntity*>* enemyDeque = IGame::Instance()->GetWindowHandler()->GetEnemyDeque();
	SpoofyEntity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	size_t i = 1;
	while (i <= enemyDeque->size() && !enemyDeque->empty())
	{
		SpoofyEntity* tempEntity = enemyDeque->at(enemyDeque->size() - i);
		tempEntity->setEntityXPose(tempEntity->getEntityXPose() + tempEntity->getEntityDxVelocity());
		tempEntity->setEntityYPose(tempEntity->getEntityYPose() + tempEntity->getEntityDyVelocity());

		if (tempEntity->getEntityXPose() < -tempEntity->getEntityTextureWidth() || tempEntity == player) // TODO: player versus enemy colision
		{
			tempEntity->setEntityHealth(0);
		}

		if (tempEntity->getEntityHealth() == 0)
		{
			if (tempEntity == player) // TODO: player versus enemy colision
			{
				player = nullptr;
			}
			tempEntity = nullptr;
			std::deque<SpoofyEntity*>::iterator it = enemyDeque->end() - i;
			enemyDeque->erase(it);
		}
		i++;
	}
}

void LogicHandler::DoEnemyBullet()
{
	std::deque<SpoofyEntity*>* enemyDeque = IGame::Instance()->GetWindowHandler()->GetEnemyDeque();
	SpoofyEntity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	size_t i = 1;
	while (i <= enemyDeque->size() && !enemyDeque->empty())
	{
		SpoofyEntity* tempEntity = enemyDeque->at(enemyDeque->size() - i);

		tempEntity->setEntityReload(tempEntity->getEntityReload() - 1);
		if (tempEntity != player && player != nullptr && tempEntity->getEntityReload() <= 0)
		{
			IGame::Instance()->GetWindowHandler()->FireEnemyBullet(tempEntity);
		}
		i++;
	}

	std::deque<SpoofyEntity*>* enemyBulletDeque = IGame::Instance()->GetWindowHandler()->GetEnemyBulletDeque();
	size_t j = 1;
	std::deque<SpoofyEntity*>::iterator it = enemyBulletDeque->end() - 1;
	while (j <= enemyBulletDeque->size() && !enemyBulletDeque->empty())
	{
		SpoofyEntity* tempEnemyBulletEntity = enemyBulletDeque->at(enemyBulletDeque->size() - j);
		tempEnemyBulletEntity->setEntityXPose(tempEnemyBulletEntity->getEntityXPose() + tempEnemyBulletEntity->getEntityDxVelocity());
		tempEnemyBulletEntity->setEntityYPose(tempEnemyBulletEntity->getEntityYPose() + tempEnemyBulletEntity->getEntityDyVelocity());

		if (tempEnemyBulletEntity->getEntityXPose() < -tempEnemyBulletEntity->getEntityTextureWidth() || 
			tempEnemyBulletEntity->getEntityYPose() < -tempEnemyBulletEntity->getEntityTextureHeight() ||
			tempEnemyBulletEntity->getEntityXPose() > SCREEN_WIDTH || 
			tempEnemyBulletEntity->getEntityYPose() > SCREEN_HEIGHT)
		{
			std::cout << "In DoEnemyBullet() function pop_back condition" << std::endl;
			tempEnemyBulletEntity = nullptr;
			enemyBulletDeque->erase(it);
		}
		j++;
		it--;
	}
}

void LogicHandler::DoBullets()
{
	std::deque<SpoofyEntity*>* bulletDeque = IGame::Instance()->GetWindowHandler()->GetBulletDeque();

	size_t i = 1;
	while (i <= bulletDeque->size() && !bulletDeque->empty())
	{
		SpoofyEntity* tempEntity = bulletDeque->at(bulletDeque->size() - i);
		tempEntity->setEntityXPose(tempEntity->getEntityXPose() + tempEntity->getEntityDxVelocity());
		tempEntity->setEntityYPose(tempEntity->getEntityYPose() + tempEntity->getEntityDyVelocity());

		if (/*IGame::Instance()->GetWindowHandler()->BulletHitFighter(tempEntity) ||*/
			tempEntity->getEntityXPose() < -tempEntity->getEntityTextureWidth() || 
			tempEntity->getEntityYPose() < -tempEntity->getEntityTextureHeight() || 
			tempEntity->getEntityXPose() > SCREEN_WIDTH || 
			tempEntity->getEntityYPose() > SCREEN_HEIGHT)
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
	SpoofyEntity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	if (player != nullptr)
	{
		if (player->getEntityXPose() < 0)
		{
			player->setEntityXPose(0);
		}

		if (player->getEntityYPose() < 0)
		{
			player->setEntityYPose(0);
		}

		if (player->getEntityXPose() > SCREEN_WIDTH / 2.0)
		{
			player->setEntityXPose(SCREEN_WIDTH / 2.0);
		}

		if (player->getEntityYPose() > (float)(SCREEN_HEIGHT - player->getEntityTextureHeight()))
		{
			player->setEntityYPose((float)(SCREEN_HEIGHT - player->getEntityTextureHeight()));
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