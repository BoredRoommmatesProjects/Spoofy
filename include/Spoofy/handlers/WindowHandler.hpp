#ifndef _SPOOFY_HANDLERS_WINDOWHANDLER_H_
#define _SPOOFY_HANDLERS_WINDOWHANDLER_H_

#include <string>
#include <deque>

struct IApp;
struct SpoofyEntity;
namespace sf
{
	class Texture;
};

class MathUtils;

class WindowHandler
{
public:
	WindowHandler(int a_width, int a_height, IApp* a_app);

	~WindowHandler();

	void InitializeTexture();
	void ResetGame();
	void PrepareWindow();
	void PresentWindow();
	void Draw();
	void FireBullet();
	void FireEnemyBullet(SpoofyEntity* a_enemyEntity);
	void CreateEnemy();

	bool BulletHitFighter(SpoofyEntity* a_bulletEntity);

	std::deque<SpoofyEntity*>* GetBulletDeque();
	std::deque<SpoofyEntity*>* GetEnemyBulletDeque();
	std::deque<SpoofyEntity*>* GetEnemyDeque();
	SpoofyEntity* GetPlayerEntity();
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

	void Blit(SpoofyEntity* a_entity);
	sf::Texture* LoadTexture(std::string& a_filename);

	IApp* m_app;
	sf::Texture* m_bulletTexture;
	sf::Texture* m_enemyTexture;
	sf::Texture* m_enemyBulletTexture;
	SpoofyEntity* m_playerEntity;

	MathUtils* m_mathUtilsObj;

	int m_width;
	int m_height;
	int m_resetGameTimer;

	std::deque<SpoofyEntity*> m_bulletEntitysDeque;
	std::deque<SpoofyEntity*> m_enemyBulletEntitysDeque;
	std::deque<SpoofyEntity*> m_ennemyEntitysDeque;
};

#endif // !_SPOOFY_HANDLERS_WINDOWHANDLER_H_