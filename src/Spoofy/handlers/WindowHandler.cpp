#include <iostream>

#include "handlers/WindowHandler.hpp"
#include "Spoofy.hpp"
#include "common/SpoofyEntity.hpp"
#include "common/SpoofyDefs.hpp"
#include "utils/MathUtils.hpp"
#include "handlers/LogicHandler.hpp"
#include "common/IApp.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "boost/filesystem.hpp"

std::string currentPath = __FILE__;
std::string imagesPath = currentPath.substr(0, currentPath.rfind("src")) + "/data/";

WindowHandler::WindowHandler(int a_width, int a_height, IApp* a_app)
: m_app(a_app), m_bulletTexture(nullptr), m_enemyTexture(nullptr), m_enemyBulletTexture(nullptr),
m_playerEntity(nullptr), m_mathUtilsObj(new MathUtils()), m_width(a_width), m_height(a_height), m_resetGameTimer(0),
m_bulletEntitysDeque({}), m_enemyBulletEntitysDeque({}), m_ennemyEntitysDeque({})
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
	SpoofyEntity* player = new SpoofyEntity();

	player->setEntityXPose(100);
	player->setEntityYPose(100);
	boost::filesystem::path currentWorkingDirectory = boost::filesystem::current_path();
	std::string playerFilename = imagesPath + "player.png";
	player->setEntityTexture(LoadTexture(playerFilename));
	player->setEntityTextureWidth(player->getEntityTexture()->getSize().x);
	player->setEntityTextureHeight(player->getEntityTexture()->getSize().y);

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
    m_app->getWindowRenderer()->clear(sf::Color(32, 32, 32, 255));
}

void WindowHandler::PresentWindow()
{
    m_app->getWindowRenderer()->display();
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

void WindowHandler::Blit(SpoofyEntity* a_entity)
{
    sf::Sprite tempSprite;
	tempSprite.setTexture(*a_entity->getEntityTexture());
	tempSprite.setPosition(sf::Vector2f(a_entity->getEntityXPose(), a_entity->getEntityYPose()));
	
    m_app->getWindowRenderer()->draw(tempSprite);
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
	SpoofyEntity* bullet = new SpoofyEntity();

	bullet->setEntityXPose(m_playerEntity->getEntityXPose() + 5);
	bullet->setEntityYPose(m_playerEntity->getEntityYPose());
	bullet->setEntityDxVelocity(PLAYER_BULLET_SPEED);
	bullet->setEntityHealth(1);
	bullet->setEntityTexture(m_bulletTexture);

    sf::Vector2u bulletTextureSize = m_bulletTexture->getSize();
    bullet->setEntityTextureWidth(bulletTextureSize.x);
    bullet->setEntityTextureHeight(bulletTextureSize.y);

	m_bulletEntitysDeque.push_front(bullet);

	bullet->setEntityYPose(bullet->getEntityYPose() + (m_playerEntity->getEntityTextureHeight() / 2) - (bullet->getEntityTextureHeight() / 2));

	m_playerEntity->setEntityReload(8);
}

void WindowHandler::FireEnemyBullet(SpoofyEntity* a_enemyEntity)
{
	SpoofyEntity* enemyBullet = new SpoofyEntity();

	enemyBullet->setEntityXPose(a_enemyEntity->getEntityXPose());
	enemyBullet->setEntityYPose(a_enemyEntity->getEntityYPose());
	enemyBullet->setEntityHealth(1);
	enemyBullet->setEntityTexture(m_enemyBulletTexture);
	enemyBullet->setEntitySide(a_enemyEntity->getEntitySide());

	m_enemyBulletEntitysDeque.push_front(enemyBullet);

    sf::Vector2u enemyBulletTextureSize = m_enemyBulletTexture->getSize();
    enemyBullet->setEntityTextureWidth(enemyBulletTextureSize.x);
    enemyBullet->setEntityTextureHeight(enemyBulletTextureSize.y);


	enemyBullet->setEntityXPose(enemyBullet->getEntityXPose() + 
							   ((a_enemyEntity->getEntityTextureWidth() / 2) - (enemyBullet->getEntityTextureWidth() / 2)));
	enemyBullet->setEntityYPose(enemyBullet->getEntityYPose() + 
							   ((a_enemyEntity->getEntityTextureHeight() / 2) - (enemyBullet->getEntityTextureHeight() / 2)));

	float dx = enemyBullet->getEntityDxVelocity();
	float dy = enemyBullet->getEntityDyVelocity();
	m_mathUtilsObj->CalcSlope((int)(m_playerEntity->getEntityXPose() + (m_playerEntity->getEntityTextureWidth() / 2)), 
							  (int)(m_playerEntity->getEntityYPose() + (m_playerEntity->getEntityTextureHeight() / 2)), 
							  (int)a_enemyEntity->getEntityXPose(), (int)a_enemyEntity->getEntityYPose(), 
							  &dx, &dy);
	enemyBullet->setEntityDxVelocity(dx * ALIEN_BULLET_SPEED);
	enemyBullet->setEntityDyVelocity(dy * ALIEN_BULLET_SPEED);

	enemyBullet->setEntitySide(SIDE_ALIEN);

	a_enemyEntity->setEntityReload((rand() % FPS * 2));
}

bool WindowHandler::BulletHitFighter(SpoofyEntity* a_bulletEntity)
{
	size_t i = 1;
	while (i <= m_ennemyEntitysDeque.size() && !m_ennemyEntitysDeque.empty())
	{
		//SpoofyEntity* tempEntity = m_ennemyEntitysDeque.at(m_ennemyEntitysDeque.size() - i);
		/*if (tempEntity->side != a_bulletEntity->side &&
			m_mathUtilsObj->Collision((int)a_bulletEntity->x, (int)a_bulletEntity->y, (int)a_bulletEntity->w,
									  (int)a_bulletEntity->h, (int)tempEntity->x, (int)tempEntity->y,
									  (int)tempEntity->w, (int)tempEntity->h))
		{
			a_bulletEntity->health = 0;
			tempEntity->health = 0;

			return true;
		}*/
		i++;
	}

	return false;
}

void WindowHandler::CreateEnemy()
{
	SpoofyEntity* enemy = new SpoofyEntity();

	enemy->setEntityXPose(SCREEN_WIDTH);
	enemy->setEntityYPose((float)(rand() % SCREEN_HEIGHT));
	enemy->setEntityHealth(1);
	enemy->setEntityTexture(m_enemyTexture);
	enemy->setEntityDxVelocity(-(float)(2 + (rand() % 4)));

	m_ennemyEntitysDeque.push_front(enemy);

    sf::Vector2u enemyTextureSize = m_enemyBulletTexture->getSize();
    enemy->setEntityTextureWidth(enemyTextureSize.x);
    enemy->setEntityTextureHeight(enemyTextureSize.y);

	enemy->setEntityReload(FPS * (1 + (rand() % 3)));
}

std::deque<SpoofyEntity*>* WindowHandler::GetBulletDeque()
{
	return &m_bulletEntitysDeque;
}

std::deque<SpoofyEntity*>* WindowHandler::GetEnemyBulletDeque()
{
	return &m_enemyBulletEntitysDeque;
}

std::deque<SpoofyEntity*>* WindowHandler::GetEnemyDeque()
{
	return &m_ennemyEntitysDeque;
}

SpoofyEntity* WindowHandler::GetPlayerEntity()
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