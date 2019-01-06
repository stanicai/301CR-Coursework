#pragma once

class State
{
public:
	std::string fontLua;
	std::string _pauseButtonLua;
	std::string _playerTexture;
	std::string _weaponTexture;
	std::string _enemyTexture;
	std::string _wallTexture;

	int level1AllBullets;
	int level1FinalPoints;
	int level1EnemyInitialSize;
	int level1EnemyFinalSize;
	int level1PointsForHittingAnEnemy;
	int level1HealthTakenByEnemy;

	int level2AllBullets;
	int level2FinalPoints;
	int level2EnemyInitialSize;
	int level2EnemyFinalSize;
	int level2PointsForHittingAnEnemy;
	int level2HealthTakenByEnemy;

	int level3AllBullets;
	int level3FinalPoints;
	int level3EnemyInitialSize;
	int level3EnemyFinalSize;
	int level3PointsForHittingAnEnemy;
	int level3HealthTakenByEnemy;

	virtual void Init() = 0;
	virtual void Input() = 0;
	virtual void Update(float delta) = 0;
	virtual void Draw(float delta) = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};