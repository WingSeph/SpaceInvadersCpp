#include "score.h"

class Player
{
private:
	int Lives;
	Score p_Score;

public:
	Player()
	{
		Lives = 3;
		if (Lives <= 0)
		{
			//destroy player
			//create explosion
			//game over
			Lives = 0;//temporary line so no errors
		}

		//press A = move left
		//press D = move right

		//press space = fire bullet
	}
	~Player() {}
};