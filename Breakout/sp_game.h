#ifndef __SP_GAME_H__
#define __SP_GAME_H__

class CGame
{
public:
	CGame();
	~CGame();

	void CheckEnemy();
	void CheckPlayer();
	void NextLevel();

private:
	int m_score;
};

#endif //__SP_GAME_H__