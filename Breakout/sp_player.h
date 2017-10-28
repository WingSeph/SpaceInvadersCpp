#ifndef __SP_PLAYER_H__
#define __SP_PLAYER_H__

class CPlayer
{
public:
	void P_Move();
	void P_Shoot();

private:
	int p_lives;
};

#endif //__SP_PLAYER_H__