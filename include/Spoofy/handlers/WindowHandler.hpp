#ifndef _SPOOFY_HANDLERS_WINDOWHANDLER_H_
#define _SPOOFY_HANDLERS_WINDOWHANDLER_H_

#include <string>
#include <deque>

struct App;
struct Stage;
struct Entity;
namespace sf
{
	class Texture;
};

class MathUtils;

class WindowHandler
{
public:
	WindowHandler(int a_width, int a_height, App* a_app);

	~WindowHandler();

	void InitializeTexture();
	void ResetGame();
	void PrepareWindow();
	void PresentWindow();
	void Draw();
	void FireBullet();
	void FireEnemyBullet(Entity* a_enemyEntity);
	void CreateEnemy();

	bool BulletHitFighter(Entity* a_bulletEntity);

	std::deque<Entity*>* GetBulletDeque();
	std::deque<Entity*>* GetEnemyBulletDeque();
	std::deque<Entity*>* GetEnemyDeque();
	Entity* GetPlayerEntity();
	int GetGameResetTimer();
	void SetGameResetTimer(int a_timer);

private:
	void InitPlayer();
	void InitEnemy();
	void InitBullet();
	void InitEnemyBullet();

	void DrawPlayer();
	void DrawFighters();
	void DrawBullets();
	void DrawEnemyBullets();

	void Blit(Entity* a_entity);
	sf::Texture* LoadTexture(std::string& a_filename);

	App* m_app;
	sf::Texture* m_bulletTexture;
	sf::Texture* m_enemyTexture;
	sf::Texture* m_enemyBulletTexture;
	Entity* m_playerEntity;

	MathUtils* m_mathUtilsObj;

	int m_width;
	int m_height;
	int m_resetGameTimer;

	std::deque<Entity*> m_bulletEntitysDeque;
	std::deque<Entity*> m_enemyBulletEntitysDeque;
	std::deque<Entity*> m_ennemyEntitysDeque;
};

#endif // !_SPOOFY_HANDLERS_WINDOWHANDLER_H_