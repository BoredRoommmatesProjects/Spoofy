#ifndef _SPOOFY_HANDLERS_LOGICHANDLER_H_
#define _SPOOFY_HANDLERS_LOGICHANDLER_H_


struct IApp;

class LogicHandler
{
public:
	LogicHandler(IApp* a_app);
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

	IApp* m_app;

	int m_enemySpawnTimer;
};

#endif // !_SPOOFY_HANDLERS_LOGICHANDLER_H_