#ifndef _SPOOFY_HANDLERS_LOGICHANDLER_H_
#define _SPOOFY_HANDLERS_LOGICHANDLER_H_

struct Stage;
struct App;

class LogicHandler
{
public:
	LogicHandler(App* a_app);
	~LogicHandler();

	void Logic();
	int GetEnemySpawntimer();
	void SetEnemySpawntimer(int a_time);

private:
	void DoPlayer();
	void DoEnemies();
	void DoEnemyBullet();
	void DoBullets();
	void SpawnEnemies();
	void ClipPlayer();

	App* m_app;

	int m_enemySpawnTimer;
};

#endif // !_SPOOFY_HANDLERS_LOGICHANDLER_H_