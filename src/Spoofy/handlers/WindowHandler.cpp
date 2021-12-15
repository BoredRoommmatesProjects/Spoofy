#include <iostream>

#include "handlers/WindowHandler.hpp"
#include "Spoofy.hpp"
#include "common/SpoofyDefs.hpp"
#include "utils/MathUtils.hpp"
#include "handlers/LogicHandler.hpp"

#include "boost/filesystem.hpp"

std::string currentPath = __FILE__;
std::string imagesPath = currentPath.substr(0, currentPath.rfind("src")) + "/data/";

WindowHandler::WindowHandler(int a_width, int a_height, App* a_app)
: m_app(a_app), m_bulletTexture(nullptr), m_enemyTexture(nullptr), m_enemyBulletTexture(nullptr),
m_playerEntity(nullptr), m_mathUtilsObj(new MathUtils()), m_width(a_width), m_height(a_height), m_resetGameTimer(0)
{}

WindowHandler::~WindowHandler()
{

	if (m_mathUtilsObj != nullptr)
	{
		delete m_mathUtilsObj;
		m_mathUtilsObj = nullptr;
	}

	if (m_bulletTexture != nullptr)
	{
		m_bulletTexture = nullptr;
	}

	if (m_enemyBulletTexture != nullptr)
	{
		m_enemyBulletTexture = nullptr;
	}

	if (m_enemyTexture != nullptr)
	{
		m_enemyTexture = nullptr;
	}

	if (m_playerEntity != nullptr)
	{
		delete m_playerEntity;
		m_playerEntity = nullptr;
	}

	while (!m_bulletEntitysDeque.empty())
	{
		m_bulletEntitysDeque.pop_back();
	}

	while (!m_ennemyEntitysDeque.empty())
	{
		m_ennemyEntitysDeque.pop_back();
	}

	while (!m_enemyBulletEntitysDeque.empty())
	{
		m_enemyBulletEntitysDeque.pop_back();
	}
}

void WindowHandler::InitializeTexture()
{
	ResetGame();
	InitEnemy();
	InitBullet();
	InitEnemyBullet();
}

void WindowHandler::ResetGame()
{
	if (m_playerEntity != nullptr)
	{
		delete m_playerEntity;
		m_playerEntity = nullptr;
	}

	while (!m_bulletEntitysDeque.empty())
	{
		m_bulletEntitysDeque.pop_back();
	}

	InitPlayer();

	IGame::Instance()->GetLogicHandler()->SetEnemySpawntimer(0);

	m_resetGameTimer = FPS * 2;
}

void WindowHandler::InitPlayer()
{
	Entity* player = new Entity();
	memset(player, 0, sizeof(Entity));

	player->x = 100;
	player->y = 100;
	boost::filesystem::path currentWorkingDirectory = boost::filesystem::current_path();
	std::string playerFilename = imagesPath + "player.png";
	player->texture = LoadTexture(playerFilename);
	player->w = player->texture->getSize().x;
	player->h = player->texture->getSize().y;

	m_playerEntity = player;
}

void WindowHandler::InitEnemy()
{
	std::string enemyFilename = imagesPath + "enemy.png";
	m_enemyTexture = LoadTexture(enemyFilename);
}

void WindowHandler::InitBullet()
{
	std::string bulletFilename = imagesPath + "playerBullet.png";
	m_bulletTexture = LoadTexture(bulletFilename);
}

void WindowHandler::InitEnemyBullet()
{
	std::string enemyBulletFilename = imagesPath + "alienBullet.png";
	m_enemyBulletTexture = LoadTexture(enemyBulletFilename);
}

void WindowHandler::PrepareWindow()
{
    m_app->windowRenderer->clear(sf::Color(32, 32, 32, 255));
}

void WindowHandler::PresentWindow()
{
    m_app->windowRenderer->display();
}

sf::Texture* WindowHandler::LoadTexture(std::string& a_filename)
{
	sf::Texture* texture = new sf::Texture();
    
	if (!texture->loadFromFile(a_filename))
	{
		std::cout << "WindowHandler::loadTexture()::texture pointer is null" << std::endl;
	}
	return texture;
}

void WindowHandler::Blit(Entity* a_entity)
{
    sf::Sprite tempSprite;
	tempSprite.setTexture(*a_entity->texture);
	tempSprite.setPosition(sf::Vector2f((int)a_entity->x, (int)a_entity->y));
	
    m_app->windowRenderer->draw(tempSprite);
}

void WindowHandler::Draw()
{
	DrawPlayer();
	DrawFighters();
	DrawBullets();
	DrawEnemyBullets();
}

void WindowHandler::DrawPlayer()
{
	Blit(m_playerEntity);
}

void WindowHandler::DrawFighters()
{
	size_t i = 1;
	while (i <= m_ennemyEntitysDeque.size() && !m_ennemyEntitysDeque.empty())
	{
		Blit(m_ennemyEntitysDeque.at(m_ennemyEntitysDeque.size() - i));
		i++;
	}
}

void WindowHandler::DrawBullets()
{
	size_t i = 1;
	while (i <= m_bulletEntitysDeque.size() && !m_bulletEntitysDeque.empty())
	{
		Blit(m_bulletEntitysDeque.at(m_bulletEntitysDeque.size() - i));
		i++;
	}
}

void WindowHandler::DrawEnemyBullets()
{
	size_t i = 1;
	while (i <= m_enemyBulletEntitysDeque.size() && !m_enemyBulletEntitysDeque.empty())
	{
		Blit(m_enemyBulletEntitysDeque.at(m_enemyBulletEntitysDeque.size() - i));
		i++;
	}
}

void WindowHandler::FireBullet()
{
	Entity* bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));

	bullet->x = m_playerEntity->x + 5;
	bullet->y = m_playerEntity->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = m_bulletTexture;

    sf::Vector2u bulletTextureSize = m_bulletTexture->getSize();
    bullet->w = bulletTextureSize.x;
    bullet->h = bulletTextureSize.y;

	m_bulletEntitysDeque.push_front(bullet);

	bullet->y += (m_playerEntity->h / 2) - (bullet->h / 2);

	m_playerEntity->reload = 8;
}

void WindowHandler::FireEnemyBullet(Entity* a_enemyEntity)
{
	Entity* enemyBullet = new Entity();
	memset(enemyBullet, 0, sizeof(Entity));

	enemyBullet->x = a_enemyEntity->x;
	enemyBullet->y = a_enemyEntity->y;
	enemyBullet->health = 1;
	enemyBullet->texture = m_enemyBulletTexture;
	enemyBullet->side = a_enemyEntity->side;

	m_enemyBulletEntitysDeque.push_front(enemyBullet);

    sf::Vector2u enemyBulletTextureSize = m_enemyBulletTexture->getSize();
    enemyBullet->w = enemyBulletTextureSize.x;
    enemyBullet->h = enemyBulletTextureSize.y;


	enemyBullet->x += (a_enemyEntity->w / 2) - (enemyBullet->w / 2);
	enemyBullet->y += (a_enemyEntity->h / 2) - (enemyBullet->h / 2);

	m_mathUtilsObj->CalcSlope((int)(m_playerEntity->x + (m_playerEntity->w / 2)), (int)(m_playerEntity->y + (m_playerEntity->h / 2)),
							  (int)a_enemyEntity->x, (int)a_enemyEntity->y, &enemyBullet->dx, &enemyBullet->dy);
	enemyBullet->dx *= ALIEN_BULLET_SPEED;
	enemyBullet->dy *= ALIEN_BULLET_SPEED;

	enemyBullet->side = SIDE_ALIEN;

	a_enemyEntity->reload = (rand() % FPS * 2);
}

bool WindowHandler::BulletHitFighter(Entity* a_bulletEntity)
{
	size_t i = 1;
	while (i <= m_ennemyEntitysDeque.size() && !m_ennemyEntitysDeque.empty())
	{
		Entity* tempEntity = m_ennemyEntitysDeque.at(m_ennemyEntitysDeque.size() - i);
		if (tempEntity->side != a_bulletEntity->side &&
			m_mathUtilsObj->Collision((int)a_bulletEntity->x, (int)a_bulletEntity->y, (int)a_bulletEntity->w,
									  (int)a_bulletEntity->h, (int)tempEntity->x, (int)tempEntity->y,
									  (int)tempEntity->w, (int)tempEntity->h))
		{
			a_bulletEntity->health = 0;
			tempEntity->health = 0;

			return true;
		}
		i++;
	}

	return false;
}

void WindowHandler::CreateEnemy()
{
	Entity* enemy = new Entity();
	memset(enemy, 0, sizeof(Entity));

	enemy->x = SCREEN_WIDTH;
	enemy->y = (float)(rand() % SCREEN_HEIGHT);
	enemy->health = 1;
	enemy->texture = m_enemyTexture;
	enemy->dx = -(float)(2 + (rand() % 4));

	m_ennemyEntitysDeque.push_front(enemy);

    sf::Vector2u enemyTextureSize = m_enemyBulletTexture->getSize();
    enemy->w = enemyTextureSize.x;
    enemy->h = enemyTextureSize.y;

	enemy->reload = FPS * (1 + (rand() % 3));
}

std::deque<Entity*>* WindowHandler::GetBulletDeque()
{
	return &m_bulletEntitysDeque;
}

std::deque<Entity*>* WindowHandler::GetEnemyBulletDeque()
{
	return &m_enemyBulletEntitysDeque;
}

std::deque<Entity*>* WindowHandler::GetEnemyDeque()
{
	return &m_ennemyEntitysDeque;
}

Entity* WindowHandler::GetPlayerEntity()
{
	return m_playerEntity;
}

int WindowHandler::GetGameResetTimer()
{
	return m_resetGameTimer;
}

void WindowHandler::SetGameResetTimer(int a_timer)
{
	m_resetGameTimer = a_timer;
}